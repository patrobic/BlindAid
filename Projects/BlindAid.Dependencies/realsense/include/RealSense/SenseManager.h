/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include <string.h>
#include "RealSense/CaptureManager.h"
#include "RealSense/Session.h"

namespace Intel {
    namespace RealSense {

        /* Forward declaration of known modules */
        namespace Face {
            class FaceModule;
        }
        namespace Hand {
            class HandModule;
        }
        namespace HandCursor {
            class HandCursorModule;
        }
        namespace Blob {
            class BlobModule;
        }
        namespace PersonTracking {
            class PersonTrackingModule;
        }
        namespace TouchlessControl {
            class TouchlessController;
        }
        namespace Segmentation {
            class Seg3D;
        }
        namespace Scan {
            class Scan3D;
        }
        namespace ScenePerception {
            class ScenePerception;
        }
        namespace Videography {
            class EnhancedVideo;
        }
        namespace ObjectRecognition {
            class ObjectRecognitionModule;
        }
        namespace ObjectTracking {
            class Tracker;
        }

        /**
        This is the main interface for the SDK pipeline.
        Control the pipeline execution with this interface.
        */
        class SenseManager : public Base {
        public:

            PXC_CUID_OVERWRITE(0xD8954321);
            PXC_DEFINE_CONST(TIMEOUT_INFINITE, -1);
            enum {
                PXC_CUID_FACE_MODULE = PXC_UID('F', 'A', '3', 'D'),
                PXC_CUID_HAND_MODULE = PXC_UID('H', 'A', 'N', 'N'),
                PXC_CUID_HAND_CURSOR_MODULE = PXC_UID('H', 'C', 'M', 'N'),
                PXC_CUID_BLOB_MODULE = PXC_UID('B', 'M', 'M', 'D'),
                PXC_CUID_PERSON_TRACKING_MODULE = PXC_UID('P', 'O', 'T', 'M'),
                PXC_CUID_TOUCHLESS_CONTROLLER = PXC_UID('F', 'L', 'K', 'S'),
                PXC_CUID_3D_SEG = PXC_UID('S', 'G', 'I', '1'),
                PXC_CUID_3D_SCAN = PXC_UID('S', 'C', 'I', '1'),
                PXC_CUID_SCENE_PERCEPTION = PXC_UID('S', 'C', 'N', 'P'),
                PXC_CUID_ENHANCED_VIDEO = PXC_UID('E', 'V', 'I', 'N'),
                PXC_CUID_OBJECT_RECOGNITION_MODULE = PXC_UID('O', 'B', 'J', 'M'),
                PXC_CUID_TRACKER = PXC_UID('T', 'R', 'K', 'R'),
            };

            /**
            The PXCSenseManager callback instance.
            */
            class Handler {
            public:
                /**
                @brief The SenseManager calls back this function when there is a device connection or
                disconnection. During initialization, the SenseManager callbacks this function when
                openning or closing any capture devices.
                @param[in] device           The video device instance.
                @param[in] connected        The device connection status.
                @return The return status is ignored during the PXCSenseManager initialization. During
                streaming, the SenseManager aborts the execution pipeline if the status is an error.
                */
                virtual Status PXCAPI OnConnect(Device* /*device*/, bool32_t /*connected*/) {
                    return Status::STATUS_DEVICE_FAILED;
                }

                /**
                @brief The SenseManager calls back this function during initialization after each device
                configuration is set.
                @param[in] mid          The module identifier. Usually this is the interface identifier, or PXCCapture::CUID+n for raw video streams.
                @param[in] module       The module instance, or NULL for raw video streams.
                @return The SenseManager aborts the execution pipeline if the status is an error.
                */
                virtual Status PXCAPI OnModuleSetProfile(int32_t /*mid*/, Base* /*module*/) {
                    return Status::STATUS_NO_ERROR;
                }

                /**
                @brief The SenseManager calls back this function after a module completed processing the frame data.
                @param[in] mid          The module identifier. Usually this is the interface identifier.
                @param[in] module       The module instance.
                @return The SenseManager aborts the execution pipeline if the status is an error.
                */
                virtual Status PXCAPI OnModuleProcessedFrame(int32_t /*mid*/, Base* /*module*/, Sample* /*sample*/) {
                    return Status::STATUS_NO_ERROR;
                }

                /**
                @brief The SenseManager calls back this function when raw video streams (explicitly requested) are available.
                @param[in] mid          The module identifier. Usually this is the interface identifier.
                @param[in] sample       The sample from capture device
                @return The SenseManager aborts the execution pipeline if the status is an error.
                */
                virtual Status PXCAPI OnNewSample(int32_t /*mid*/, Sample* /*sample*/) {
                    return Status::STATUS_NO_ERROR;
                }

                /**
                @brief The SenseManager calls back this function when error or warning detected during streaming
                @param[in] mid          The identifier of module reported error or warning
                @param[in] sts          The error or warning code
                */
                virtual void PXCAPI OnStatus(int32_t /*mid*/, Status /*sts*/) {
                }
            };

            /**
            @brief    Return the PXCSession instance. Internally managed. Do not release the instance.
            The session instance is managed internally by the SenseManager. Do not release the session instance.
            @return The PXCSession instance.
            */
            virtual Session* PXCAPI QuerySession(void) = 0;

            /**
            @brief    Return the PXCCaptureManager instance. Internally managed. Do not release the instance.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The PXCCaptureManager instance.
            */
            virtual CaptureManager* PXCAPI QueryCaptureManager(void) = 0;

            /**
            @brief    Return the captured sample for the specified module or explicitly/impl requested streams.
            For modules, use mid=module interface identifier.
            For explictly requested streams via multiple calls to EnableStream(s), use mid=PXCCapture::CUID+0,1,2...
            The captured sample is managed internally by the SenseManager. Do not release the instance.
            @param[in] mid        The module identifier. Usually this is the interface identifier, or PXCCapture::CUID+n for raw video streams.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            virtual Sample* PXCAPI QuerySample(int32_t mid) = 0;

            /**
            @brief    Return available captured sample, explicitly or implicitly requested.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QuerySample(void) {
                return QuerySample(0);
            }

            /**
            @brief    Return the captured sample for the face module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryFaceSample(void) {
                return QuerySample(PXC_CUID_FACE_MODULE);
            }

            /**
            @brief    Return the captured sample for the hand module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryHandSample(void) {
                return QuerySample(PXC_CUID_HAND_MODULE);
            }


            /**
            @brief    Return the captured sample for the hand cursor module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryHandCursorSample(void) {
                return QuerySample(PXC_CUID_HAND_CURSOR_MODULE);
            }

            /**
            @brief    Return the captured sample for the object recognition module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryObjectRecognitionSample(void) {
                return QuerySample(PXC_CUID_OBJECT_RECOGNITION_MODULE);
            }

            /**
            @brief    Return the captured sample for the blob module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryBlobSample(void) {
                return QuerySample(PXC_CUID_BLOB_MODULE);
            }

            /**
            @brief    Return the captured sample for the Person tracking module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryPersonTrackingSample(void) {
                return QuerySample(PXC_CUID_PERSON_TRACKING_MODULE);
            }

            /**
            @brief    Return the captured sample for the scene perception module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline Sample* QueryScenePerceptionSample(void) {
                return QuerySample(PXC_CUID_SCENE_PERCEPTION);
            }

            /**
            @brief      Return the captured sample for the object tracker module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline const Sample* QueryTrackerSample(void) {
                return QuerySample(PXC_CUID_TRACKER);
            }

            /**
            @brief      Return the captured sample for the enhanced Videography module.
            The captured sample is managed internally by the SenseManager. Do not release the sample.
            @return The sample instance, or NULL if the captured sample is not available.
            */
            __inline const Sample* QueryEnhancedVideoSample(void) {
                return QuerySample(PXC_CUID_ENHANCED_VIDEO);
            }

            /**
            @brief    Return the module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @param[in] mid        The module identifier. Usually this is the interface identifier.
            @return The module instance.
            */
            virtual Base* PXCAPI QueryModule(int32_t mid) = 0;

            /**
            @brief    Return the Face module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline Face::FaceModule* QueryFace(void) {
                Base *instance = QueryModule(PXC_CUID_FACE_MODULE);
                return instance ? (Face::FaceModule*)instance->QueryInstance(PXC_CUID_FACE_MODULE) : 0;
            }

            __inline PersonTracking::PersonTrackingModule* QueryPersonTracking(void) {
                Base *instance = QueryModule(PXC_CUID_PERSON_TRACKING_MODULE);
                return instance ? (PersonTracking::PersonTrackingModule*)instance->QueryInstance(PXC_CUID_PERSON_TRACKING_MODULE) : 0;
            }

            /**
            @brief    Return the tracker module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline ObjectTracking::Tracker* QueryTracker(void) {
                Base *instance = QueryModule(PXC_CUID_TRACKER);
                return instance ? (ObjectTracking::Tracker*)instance->QueryInstance(PXC_CUID_TRACKER) : 0;
            }


            /**
            @brief    Return the hand module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline Hand::HandModule* QueryHand(void) {
                Base *instance = QueryModule(PXC_CUID_HAND_MODULE);
                return instance ? (Hand::HandModule*)instance->QueryInstance(PXC_CUID_HAND_MODULE) : 0;
            }

            /**
            @brief    Return the hand module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline HandCursor::HandCursorModule* QueryHandCursor(void) {
                Base *instance = QueryModule(PXC_CUID_HAND_CURSOR_MODULE);
                return instance ? (HandCursor::HandCursorModule*)instance->QueryInstance(PXC_CUID_HAND_CURSOR_MODULE) : 0;
            }

            /**
            @brief    Return the object recognition module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline ObjectRecognition::ObjectRecognitionModule* QueryObjectRecognition(void) {
                Base *instance = QueryModule(PXC_CUID_OBJECT_RECOGNITION_MODULE);
                return instance ? (ObjectRecognition::ObjectRecognitionModule*)instance->QueryInstance(PXC_CUID_OBJECT_RECOGNITION_MODULE) : 0;
            }

            /**
            @brief    Return the blob module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline Blob::BlobModule* QueryBlob(void) {
                Base *instance = QueryModule(PXC_CUID_BLOB_MODULE);
                return instance ? (Blob::BlobModule*)instance->QueryInstance(PXC_CUID_BLOB_MODULE) : 0;
            }


            /**
            @brief    Return the Person tracking module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline PersonTracking::PersonTrackingModule* QueryPersonTacking(void) {
                Base *instance = QueryModule(PXC_CUID_PERSON_TRACKING_MODULE);
                return instance ? (PersonTracking::PersonTrackingModule*)instance->QueryInstance(PXC_CUID_PERSON_TRACKING_MODULE) : 0;
            }


            /**
            @brief    Return the Touchless module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline TouchlessControl::TouchlessController* QueryTouchlessController(void) {
                Base *instance = QueryModule(PXC_CUID_TOUCHLESS_CONTROLLER);
                return instance ? (TouchlessControl::TouchlessController*)instance->QueryInstance(PXC_CUID_TOUCHLESS_CONTROLLER) : 0;
            }

            /**
            @brief    Return the 3D Segmentation module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline Segmentation::Seg3D* Query3DSeg(void) {
                Base *instance = QueryModule(PXC_CUID_3D_SEG);
                return instance ? (Segmentation::Seg3D*)instance->QueryInstance(PXC_CUID_3D_SEG) : 0;
            }

            /**
            @brief    Return the Mesh Capture module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline Scan::Scan3D* Query3DScan(void) {
                Base *instance = QueryModule(PXC_CUID_3D_SCAN);
                return instance ? (Scan::Scan3D*)instance->QueryInstance(PXC_CUID_3D_SCAN) : 0;
            }

            /**
            @brief    Return the Scene Perception module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline ScenePerception::ScenePerception* QueryScenePerception(void) {
                Base *instance = QueryModule(PXC_CUID_SCENE_PERCEPTION);
                return instance ? (ScenePerception::ScenePerception*)instance->QueryInstance(PXC_CUID_SCENE_PERCEPTION) : 0;
            }

            /**
            @brief    Return the Enhanced Videography module instance. Between AcquireFrame/ReleaseFrame, the function returns
            NULL if the specified module hasn't completed processing the current frame of image data.
            The instance is managed internally by the SenseManager. Do not release the instance.
            @return The module instance.
            */
            __inline Videography::EnhancedVideo* QueryEnhancedVideo(void) {
                Base *instance = QueryModule(PXC_CUID_ENHANCED_VIDEO);
                return instance ? (Videography::EnhancedVideo*)instance->QueryInstance(PXC_CUID_ENHANCED_VIDEO) : 0;
            }

            /**
            @brief    Initialize the SenseManager pipeline for streaming with callbacks. The application must
            enable raw streams or algorithm modules before this function.
            @param[in] handler          Optional callback instance.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI Init(Handler *handler) = 0;

            /**
            @brief    Initialize the SenseManager pipeline for streaming. The application must enable raw
            streams or algorithm modules before this function.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status Init(void) {
                return Init(0);
            }

            /**
            @brief    Stream frames from the capture module to the algorithm modules. The application must
            initialize the pipeline before calling this function. If blocking, the function blocks until
            the streaming stops (upon any capture device error or any callback function returns any error.
            If non-blocking, the function returns immediately while running streaming in a thread.
            AcquireFrame/ReleaseFrame are not compatible with StreamFrames. Run the SenseManager in the pulling
            mode with AcquireFrame/ReleaseFrame, or the callback mode with StreamFrames.
            @param[in]    blocking      The blocking status.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI StreamFrames(bool32_t blocking) = 0;

            /**
            @brief    This function returns the input device connection status during streaming.
            The connection status is valid only in between the Init function and the Close function.
            @return true        The input device is connected.
            @return false       The input device is not connected.
            */
            virtual bool32_t PXCAPI IsConnected(void) = 0;

            /**
            @brief    This function starts streaming and waits until certain events occur. If ifall=true,
            the function blocks until all samples are ready and the modules completed processing the samples.
            If ifall=false, the function blocks until any of the mentioned is ready. The SenseManager
            pipeline pauses at this point for the application to retrieve the processed module data, until
            the application calls ReleaseFrame.
            AcquireFrame/ReleaseFrame are not compatible with StreamFrames. Run the SenseManager in the pulling
            mode with AcquireFrame/ReleaseFrame, or the callback mode with StreamFrames.
            @param[in]    ifall             If true, wait for all modules to complete processing the data.
            @param[in]    timeout           The time out value in milliseconds.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI AcquireFrame(bool32_t ifall, int32_t timeout) = 0;

            /**
            @brief    This function starts streaming and waits until certain events occur. If ifall=true,
            the function blocks until all samples are ready and the modules completed processing the samples.
            If ifall=false, the function blocks until any of the mentioned is ready. The SenseManager
            pipeline pauses at this point for the application to retrieve the processed module data, until
            the application calls ReleaseFrame.
            AcquireFrame/ReleaseFrame are not compatible with StreamFrames. Run the SenseManager in the pulling
            mode with AcquireFrame/ReleaseFrame, or the callback mode with StreamFrames.
            @param[in]    ifall         If true, wait for all modules to complete processing the data.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status AcquireFrame(bool32_t ifall = true) {
                return AcquireFrame(ifall, (int32_t)TIMEOUT_INFINITE);
            }

            /**
            @reserved DO NOT USE THIS FUNCTION.
            @brief    This function discards any internally cached sample from the capture device (and restart
            new streaming.) Use this function together after file playback repositioning to avoid any caching
            effects. Use also this function in the snapshot mode to get the most recent sample without any
            streaming caching effect.
            */
            virtual void PXCAPI FlushFrame(void) = 0;

            /**
            @brief    This function resumes streaming after AcquireFrame.
            AcquireFrame/ReleaseFrame are not compatible with StreamFrames. Run the SenseManager in the pulling
            mode with AcquireFrame/ReleaseFrame, or the callback mode with StreamFrames.
            */
            virtual void PXCAPI ReleaseFrame(void) = 0;

            /**
            @brief    This function closes the execution pipeline.
            */
            virtual void PXCAPI Close(void) = 0;

            /**
            @brief    Explicitly request to stream the specified raw streams. If specified more than a stream,
            SenseManager will synchronize these streams. If called multiple times, the function treats each
            stream request as independent (unaligned.) The stream identifier is PXCCapture::CUID+n.
            @param[in] sdesc            The stream descriptor.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI EnableStreams(DataDesc *sdesc) = 0;

            /**
            @brief    Explicitly request to stream the specified raw stream. If specified more than one stream,
            SenseManager will synchronize these streams. If called multiple times, the function treats each
            stream request as independent (unaligned). The stream identifier is PXCCapture::CUID+n.
            @param[in] type             The stream type.
            @param[in] width            Optional width.
            @param[in] height           Optional height.
            @param[in] fps              Optional frame rate.
            @param[in] option            Optional stream flags.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableStream(StreamType type, int32_t width = 0, int32_t height = 0, float fps = 0, StreamOption options = StreamOption::STREAM_OPTION_ANY) {
                DataDesc ddesc = {};
                ddesc.deviceInfo.streams = type;
                StreamDesc& sdesc = ddesc.streams[type];
                sdesc.sizeMin.width = sdesc.sizeMax.width = width;
                sdesc.sizeMin.height = sdesc.sizeMax.height = height;
                sdesc.frameRate.min = fps;
                sdesc.frameRate.max = fps;
                sdesc.options = options;
                return EnableStreams(&ddesc);
            }

            /**
            @brief    Enable a module in the pipeline.
            @param[in] mid              The module identifier. This is usually the interface identifier.
            @param[in] mdesc            The module descriptor.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI EnableModule(int32_t mid, ImplDesc *mdesc) = 0;

            /**
            @brief    Enable the face module in the pipeline.
            @param[in] name             The optional module name.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableFace(wchar_t *name = 0) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_FACE_MODULE;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_FACE_MODULE, &mdesc);
            }

            /**
            @brief    Enable the Tracker module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableTracker(void) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_TRACKER;
                return EnableModule(PXC_CUID_TRACKER, &mdesc);
            }


            /**
            @brief    Enable the hand module in the pipeline.
            @param[in] name        The optional module name.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableHand(wchar_t *name = 0) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_HAND_MODULE;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_HAND_MODULE, &mdesc);
            }


            /**
            @brief    Enable the hand cursor module in the pipeline.
            @param[in] name        The optional module name.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableHandCursor(wchar_t *name = 0) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_HAND_CURSOR_MODULE;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_HAND_CURSOR_MODULE, &mdesc);
            }

            /**
            @brief    Enable the blob module in the pipeline.
            @param[in] name        The optional module name.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableBlob(wchar_t *name = 0) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_BLOB_MODULE;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_BLOB_MODULE, &mdesc);
            }


            /**
            @brief    Enable the Person tracking module in the pipeline.
            @param[in] name        The optional module name.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnablePersonTracking(wchar_t *name = 0) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_PERSON_TRACKING_MODULE;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_PERSON_TRACKING_MODULE, &mdesc);
            }


            /**
            @brief    Enable the touchless controller module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableTouchlessController(void) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_TOUCHLESS_CONTROLLER;
                return EnableModule(PXC_CUID_TOUCHLESS_CONTROLLER, &mdesc);
            }

            /**
            @brief    Enable the 3D Segmentation module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status Enable3DSeg(wchar_t *name = NULL) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_3D_SEG;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_3D_SEG, &mdesc);
            }


            /**
            @brief    Enable the Mesh Capture module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status Enable3DScan(wchar_t *name = NULL) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_3D_SCAN;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_3D_SCAN, &mdesc);
            }

            /**
            @brief    Enable the Scene Perception module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableScenePerception(wchar_t *name = NULL) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_SCENE_PERCEPTION;
                if (name) PXC_STRCPY(mdesc.friendlyName, name, sizeof(mdesc.friendlyName) / sizeof(wchar_t));
                return EnableModule(PXC_CUID_SCENE_PERCEPTION, &mdesc);
            }

            /**
            @brief    Enable the Enhanced Videogrphy module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableEnhancedVideo(void) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_ENHANCED_VIDEO;
                return EnableModule(PXC_CUID_ENHANCED_VIDEO, &mdesc);
            }

            /**
            @brief    Enable the Object recognition module in the pipeline.
            @return Status::STATUS_NO_ERROR        Successful execution.
            */
            __inline Status EnableObjectRecognition(void) {
                ImplDesc mdesc = {};
                mdesc.cuids[0] = PXC_CUID_OBJECT_RECOGNITION_MODULE;
                return EnableModule(PXC_CUID_OBJECT_RECOGNITION_MODULE, &mdesc);
            }

            /**
            @brief    Pause/Resume the execution of the specified module.
            @param[in] mid          The module identifier. This is usually the interface identifier.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            virtual void PXCAPI PauseModule(int32_t mid, bool32_t pause) = 0;

            /**
            @brief    Pause/Resume the execution of the Scene Perception module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseScenePerception(bool32_t pause) {
                PauseModule(PXC_CUID_SCENE_PERCEPTION, pause);
            }

            /**
            @brief    Pause/Resume the execution of the Object Recognition module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseObjectRecognition(bool32_t pause) {
                PauseModule(PXC_CUID_OBJECT_RECOGNITION_MODULE, pause);
            }

            /**
            @brief    Pause/Resume the execution of the face module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseFace(bool32_t pause) {
                PauseModule(PXC_CUID_FACE_MODULE, pause);
            }

            /**
            @brief    Pause/Resume the execution of the Tracker module.
            @param[in] pause    If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseTracker(bool32_t pause) {
                PauseModule(PXC_CUID_TRACKER, pause);
            }

            /**
            @brief    Pause/Resume the execution of the hand module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseHand(bool32_t pause) {
                PauseModule(PXC_CUID_HAND_MODULE, pause);
            }

            /**
            @brief    Pause/Resume the execution of the hand cursor module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseHandCursor(bool32_t pause) {
                PauseModule(PXC_CUID_HAND_CURSOR_MODULE, pause);
            }

            /**
            @brief    Pause/Resume the execution of the blob module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseBlob(bool32_t pause) {
                PauseModule(PXC_CUID_BLOB_MODULE, pause);
            }


            /**
            @brief    Pause/Resume the execution of the Person tracking module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PausePersonTracking(bool32_t pause) {
                PauseModule(PXC_CUID_PERSON_TRACKING_MODULE, pause);
            }

            /**
            @brief    Pause/Resume the execution of the touchless controller module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseTouchlessController(bool32_t pause) {
                PauseModule(PXC_CUID_TOUCHLESS_CONTROLLER, pause);
            }

            /**
            @brief    Pause/Resume the execution of the 3D Segmentation module.
            @param[in] pause        If true, pause the module. Otherwise, resume the module.
            */
            __inline void Pause3DSeg(bool32_t pause) {
                PauseModule(PXC_CUID_3D_SEG, pause);
            }

            /**
            @brief    Pause/Resume the execution of the Enhanced Videography module.
            @param[in] pause    If true, pause the module. Otherwise, resume the module.
            */
            __inline void PauseEnhancedVideo(bool32_t pause) {
                PauseModule(PXC_CUID_ENHANCED_VIDEO, pause);
            }

            /**
            @brief    Create an instance of the SenseManager interface.
            @return The SenseManager instance.
            */
            __inline static SenseManager* CreateInstance(const wchar_t* specifiedRuntimePath = nullptr) {
                Session *session = PXCSession_CreateFromPath(specifiedRuntimePath);
                if (!session)
                    return nullptr;
                SenseManager *sm = session->CreateSenseManager();
                session->Release();
                return sm;
            }

			/**
			@brief Create an instance of the PXCSenseManager interface.
			@return The PXCSenseManager instance.
			*/
			__inline static SenseManager* CreateInstance(Session* session) {
				SenseManager *sm = 0;
				session->CreateImpl<SenseManager>(&sm);
				return sm;
			}
        };
    }
}
