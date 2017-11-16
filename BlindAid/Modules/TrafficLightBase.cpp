#include "TrafficLightBase.h"
#include "TrafficLightBlobDetector.h"
#include "TrafficLightDeepLearning.h"

namespace Vision
{
  namespace TrafficLight
  {
    Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output)
    {
      if (((SwitchableParameters*)params)->GetMode() == Parameters::Mode::BlobDetector)
        return new BlobDetector::BlobDetector(params, input, output);
      else
        return new DeepLearning::DeepLearning(params, input, output);
    }

    Base::Base(IParameters *params, IData *input, IData *output) : DetectBase(params, input, output)
    {

    }

    std::vector<Result> Data::FilterByConsecutiveCount()
    {
      std::vector<Result> filtered;

      for (int i = 0; i < _results.size(); ++i)
      {
        if (_results.at(i)._count > _consecutiveCount)
          filtered.push_back(_results.at(i));
      }

      return filtered;
    }

    // TODO: Must be unit tested thoroughly.
    void Data::MatchPoints(std::vector<Result> &results)
    {
      std::vector<Result> matched; // stores new detections that match previous ones in position and size.

      double distance;
      double radiusDifference;
      bool sameColor;
      double minimumDistance = INT_MAX;
      double minimumRadiusDifference;
      int nearestCurrent;
      int nearestPrevious;
      bool found = false;

      // for each point in incoming vector, while remaining points that are close enough still exist.
      do
      {
        minimumDistance = INT_MAX;
        found = false;

        // find nearest pair of current and previous points.
        for (int i = 0; i < results.size(); ++i)
          for (int j = 0; j < _results.size(); ++j)
          {
            distance = results.at(i).CartesianDistance(_results.at(j));
            radiusDifference = results.at(i).RadiusDifference(_results.at(j));
            sameColor = results.at(i).SameColor(_results.at(j));

            // consider two points a pair candidate if distanace and radius thresholds are met, only if it is the closest pair found yet.
            if (distance < minimumDistance && radiusDifference < _maximumRadiusDiff && sameColor)
            {
              minimumDistance = distance;
              minimumRadiusDifference = results.at(i).RadiusDifference(_results.at(j));
              nearestCurrent = i;
              nearestPrevious = j;
              found = true;
            }
          }

        // circle qualifies as existing if its distance to nearest circle is close and radius is similar.
        if (minimumDistance < _maximumDistance && minimumRadiusDifference < _maximumRadiusDiff)
        {
          results.at(nearestCurrent)._count = ++_results.at(nearestPrevious)._count; // retreive and increment count from matched point
          matched.push_back(results.at(nearestCurrent)); // insert matched point into temporary vector
          results.erase(results.begin() + nearestCurrent); // remove matched point from incoming vector
          _results.erase(_results.begin() + nearestPrevious); // remove matched point from previous vector also
        }
        else if (found == true)
          results.erase(results.begin() + nearestCurrent);
      } while (minimumDistance < _maximumDistance);

      _results = matched; // store points that were matched with detections from previous frame.
      _results.insert(_results.end(), results.begin(), results.end()); // also store points that were newly detected this frame.
    }
  }
}