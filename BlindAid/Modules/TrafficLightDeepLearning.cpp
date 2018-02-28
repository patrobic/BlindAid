#include "TrafficLightDeepLearning.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace std::chrono;
using namespace cv::dnn;

/* const String keys =
"{help h    || Sample app for loading Inception TensorFlow model. "
"The model and class names list can be downloaded here: "
"https://storage.googleapis.com/download.tensorflow.org/models/inception5h.zip }"
"{model m   |tensorflow_inception_graph.pb| path to TensorFlow .pb model file }"
"{image i   || path to image file }"
"{i_blob    | input | input blob name) }"
"{o_blob    | softmax2 | output blob name) }"
"{c_names c | imagenet_comp_graph_label_strings.txt | path to file with classnames for class id }"
"{result r  || path to save output blob (optional, binary format, NCHW order) }"
;*/

namespace Vision {
	namespace TrafficLight {
		namespace DeepLearning {

			
			DeepLearning::DeepLearning(IParameters *params, IData *input, IData *output) : Base(params, input, output)
			{
				dependenciesPath = "C:/Users/Salma/Documents/CapstoneML/BlindAid/BlindAid/MachineLearning";
				modelFile = dependenciesPath+"/model.pb";
				config = dependenciesPath+"/modeln.pbtxt";
				imageFile = "C:/Users/Salma/Documents/CapstoneML/keras_model/color_26.png";
				inBlobName = "input_1";
				outBlobName = "softmax/Softmax";
				classNamesFile = dependenciesPath+"/class_strings";
			

			
				//! [Initialize network]
				net = readNetFromTensorflow(modelFile, config);
			}

			void DeepLearning::Process()
			{
				steady_clock::time_point start = steady_clock::now();

				PreprocessImage();
				RunDeepLearning();
				UpdateResults();

				steady_clock::time_point end = steady_clock::now();
				duration<double> time_span = duration_cast<duration<double>>(end - start);
				cout << "[TRAF-DL] Traffic lights detected.\t(" << setw(5) << (int)(time_span.count() * 1000) << " ms)\n";
			}

			void DeepLearning::PreprocessImage()
			{
				// GetFiltered the color image, crop to only the top half (since traffic lights are only expected in upper fraction of frame), and resize to size required by deep learning.
				resize((*_input->GetColorImage())(Rect((int)(_input->GetColorImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2 ), 0, (int)(_input->GetColorImage()->cols *  _params->GetCenterRegionRatio()), (int)(_input->GetColorImage()->rows*_params->GetUpperRegionRatio()))), _preprocessedImage, _params->GetDeepLearningParams()->GetColorImageSize());

			}

			void DeepLearning::RunDeepLearning()
			{

				if (net.empty())
				{
					std::cerr << "Can't load network by using the mode file: " << std::endl;
					std::cerr << modelFile << std::endl;
					system("pause");
					exit(-1);
				}

				Mat img = *_input->GetColorImage();

				//! [Prepare blob]
				if (img.empty())
				{
					std::cerr << "Can't read image from the file: " << imageFile << std::endl;
					system("pause");
					exit(-1);
				}

				//Mat inputBlob = blobFromImage(_preprocessedImage, 1.0f, Size(224, 224), Scalar(), true, false);   //Convert Mat to batch of images
				
				Mat inputBlob = blobFromImage(img, 1.0 / 255.0f, Size(224, 224), Scalar(0, 0, 0), true, true);			 //Convert Mat to batch of images																					  //! [Prepare blob]
				//inputBlob -= 117.0;

				//! [Set input blob]
				net.setInput(inputBlob, inBlobName);        //set the network input
															//! [Set input blob]

				cv::TickMeter tm;
				tm.start();

				//! [Make forward pass]
				Mat result = net.forward(outBlobName);                          //compute output
																				//! [Make forward pass]

				tm.stop();

				std::cout << "Output blob shape " << result.size[0] << " x " << result.size[1] << " x " << result.size[2] << " x " << result.size[3] << std::endl;
				std::cout << "Inference time, ms: " << tm.getTimeMilli() << std::endl;
				std::cout << "all result" << result << endl;		//print predictions

				if (!classNamesFile.empty()) {
					std::vector<String> classNames = readClassNames(classNamesFile.c_str());

					int classId;
					double classProb;
					getMaxClass(result, &classId, &classProb);//find the best class

															  //! [Print results]
					std::cout << "Best class: #" << classId << " '" << classNames.at(classId) << "'" << std::endl;
					std::cout << "Probability: " << classProb * 100 << "%" << std::endl;
					
					int map[] = { 3, 0, 1 };
					for (int i = 0; i < 4; ++i) _confidence[i] = 0;
					_confidence[map[classId]] = classProb;
				}
			}

			void DeepLearning::UpdateResults()
			{
				for (int i = 0; i < 4; ++i)
				{
					bool success = true;
					for (int j = 0; j < 4; ++j)
					{
						if (_confidence[i] < _confidence[j])
							success = false;
					}
					if (success)
						_output->Set(Result(_confidence));
				}
			}

			/* Find best class for the blob (i. e. class with maximal probability) */
			void DeepLearning::getMaxClass(const Mat &probBlob, int *classId, double *classProb)
			{
				Mat probMat = probBlob.reshape(1, 1); //reshape the blob to 1x1000 matrix
				Point classNumber;

				minMaxLoc(probMat, NULL, classProb, NULL, &classNumber);
				*classId = classNumber.x;
			}

			std::vector<String> DeepLearning::readClassNames(const char *filename)
			{
				std::vector<String> classNames;

				std::ifstream fp(filename);
				if (!fp.is_open())
				{
					std::cerr << "File with classes labels not found: " << filename << std::endl;
					exit(-1);
				}

				std::string name;
				while (!fp.eof())
				{
					std::getline(fp, name);
					if (name.length())
						classNames.push_back(name);
				}

				fp.close();
				return classNames;
			}
		}
	}
}