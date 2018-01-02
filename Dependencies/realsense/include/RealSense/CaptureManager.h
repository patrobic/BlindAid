/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Capture.h"
#include "RealSense/VideoModule.h"
#include "RealSense/Session.h"

#ifdef _WIN32
#include <string.h>
#define PXC_STRCPY(_DST, _SRC, _SIZE) wcscpy_s<_SIZE>(_DST, _SRC)
#else
#include <string>
#define PXC_STRCPY(_DST, _SRC, _SIZE) wcsncpy(_DST, _SRC, _SIZE)
#endif
class PXCSyncPoint;

namespace Intel {
    namespace RealSense {

        /**
        The CaptureManager interface provides the following features:
        (1) Locate an I/O device that meets all module input needs.
        (2) Record any streaming data to a file and playback from the file.
        */
        class CaptureManager : public Base {
        public:
            PXC_CUID_OVERWRITE(0xD8912345);

            /**
            This is the PXCCaptureManager callback interface.
            */
            class Handler {
            public:
                /**
                @brief    The CaptureManager callbacks this function when creating a device instance.
                @param[in]    mdesc     The I/O module descriptor.
                @param[in]    device    The device instance.
                @return The CaptureManager aborts the device match if the status is an error.
                */
                virtual Status PXCAPI OnCreateDevice(ImplDesc* /*mdesc*/, Device* /*device*/) {
                    return Status::STATUS_NO_ERROR;
                }

                /**
                @brief    The CaptureManager callbacks this function when configuring the device streams.
                @param[in]    device    The device instance.
                @param[in]    types     The bit-OR'ed value of all streams.
                @return The CaptureManager aborts the device match if the status is an error.
                */
                virtual Status PXCAPI OnSetupStreams(Device* /*device*/, StreamType /*types*/) {
                    return Status::STATUS_NO_ERROR;
                }

                /**
                @brief    The CaptureManager callbacks this function when the current device failed to
                meet the algorithm needs. If the function returns any error, the CaptureManager performs
                the current device match again, allowing to try multiple configurations on the same device.
                @param[in]    device    The device instance.
                @return The CaptureManager repeats the match on the same device if the status code is any
                error, or go onto the next device if the status code is no error.
                */
                virtual Status PXCAPI OnNextDevice(Device*) {
                    return Status::STATUS_NO_ERROR;
                }
            };

            /**
            @brief    The function adds the specified DeviceInfo to the DeviceInfo filter list.
            @param[in] dinfo    The DeviceInfo structure to be added to the filter list, or NULL to clean up the filter list.
            */
            virtual void PXCAPI FilterByDeviceInfo(DeviceInfo *dinfo) = 0;

            /**
            @brief    The function adds the specified device information to the DeviceInfo filter list.
            @param[in] name     The optional device friendly name.
            @param[in] did      The optional device symbolic name.
            @param[in] didx     The optional device index.
            */
            void __inline FilterByDeviceInfo(wchar_t *name, wchar_t *did, int32_t didx) {
                DeviceInfo dinfo = {};
                if (name) PXC_STRCPY(dinfo.name, name, sizeof(dinfo.name) / sizeof(wchar_t));
                if (did) PXC_STRCPY(dinfo.did, did, sizeof(dinfo.did) / sizeof(wchar_t));
                dinfo.didx = didx;
                FilterByDeviceInfo(&dinfo);
            }

            /**
            @brief    The function adds the specified StreamProfile to the StreamProfile filter list.
            @param[in] dinfo    The stream configuration to be added to the filter list, or NULL to clean up the filter list.
            */
            virtual void PXCAPI FilterByStreamProfiles(StreamProfileSet *profiles) = 0;

            /**
            @brief    The function adds the specified StreamProfile to the StreamProfile filter list.
            @param[in] type     The stream type.
            @param[in] width    The optional image width.
            @param[in] height   The optional image height.
            @param[in] fps      The optional frame rate.
            */
            void __inline FilterByStreamProfiles(StreamType type, int32_t width, int32_t height, float fps) {
                StreamProfileSet profiles = {};
                profiles[type].imageInfo.width = width;
                profiles[type].imageInfo.height = height;
                profiles[type].frameRate.min = profiles[type].frameRate.max = fps;
                FilterByStreamProfiles(&profiles);
            }

            /**
            @brief    Add the module input needs to the CaptureManager device search. The application must call
            this function for all modules before the LocalStreams function, where the CaptureManager performs
            the device match.
            @param[in]  mid         The module identifier. The application can use any unique value to later identify the module.
            @param[in]  inputs      The module input descriptor.
            @return PXC_STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI RequestStreams(int32_t mid, DataDesc *inputs) = 0;

            /**
            @brief    The function locates an I/O device that meets any module input needs previously specified
            by the RequestStreams function. The device and its streams are configured upon a successful return.
            @param[in]  handler     The optional handler instance for callbacks during the device match.
            @return PXC_STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI LocateStreams(Handler *handler) = 0;

            /**
            @brief    The function locates an I/O device that meets any module input needs previously specified
            by the RequestStreams function. The device and its streams are configured upon a successful return.
            @return PXC_STATUS_NO_ERROR        Successful execution.
            */
            Status __inline LocateStreams(void) {
                return LocateStreams(0);
            }

            /**
            @brief    Close the streams.
            */
            virtual void PXCAPI CloseStreams(void) = 0;

            /**
            @brief    Return the capture instance.
            @return the capture instance.
            */
            virtual Capture* PXCAPI QueryCapture(void) = 0;

            /**
            @brief    Return the device instance.
            @return the device instance.
            */
            virtual Device* PXCAPI QueryDevice(void) = 0;

            /**
            @brief    Return the stream resolution of the specified stream type.
            @param[in]  type        The stream type.
            @return the stream resolution.
            */
            virtual SizeI32 PXCAPI QueryImageSize(StreamType type) = 0;

            /**
            @brief    Read the image samples for a specified module.
            @param[in]  mid         The module identifier.
            @param[out] sample      The captured sample, to be returned.
            @return PXC_STATUS_NO_ERROR        Successful execution.
            */
            virtual /*PXC_DEPRECATED("Deprecated. Use SampleReader or SenseManager::EnableStreams instead.")*/ Status PXCAPI ReadModuleStreamsAsync(int32_t mid, Sample *sample, PXCSyncPoint **reserved) = 0;

            /**
            @brief    Setup file recording or playback.
            @param[in]  file        The file name.
            @param[in]  record      If true, the file is opened for recording. Otherwise, the file is opened for playback.
            @return PXC_STATUS_NO_ERROR        Successful execution.
            */
            virtual Status PXCAPI SetFileName(const wchar_t *file, bool32_t record) = 0;

            /**
            @brief    Set up to record or playback certain stream types.
            @param[in]  types       The bit-OR'ed stream types.
            */
            virtual void PXCAPI SetMask(StreamType types) = 0;

            /**
            @brief    Pause/Resume recording or playing back.
            @param[in]  pause       True for pause and false for resume.
            */
            virtual void PXCAPI SetPause(bool32_t pause) = 0;

            /**
            @brief    Set the realtime playback mode.
            @param[in]  realtime    True to playback in real time, or false to playback as fast as possible.
            */
            virtual void PXCAPI SetRealtime(bool32_t realtime) = 0;

            /**
            @brief    Reset the playback position by the frame index.
            @param[in]  frame       The frame index.
            */
            virtual void PXCAPI SetFrameByIndex(int32_t frame) = 0;

            /**
            @brief    Return the current playback position in frame index.
            @return The frame index.
            */
            virtual int32_t PXCAPI QueryFrameIndex(void) = 0;

            /**
            @brief    Reset the playback position by the nearest time stamp.
            @param[in]  ts          The time stamp, in 100ns.
            */
            virtual void PXCAPI SetFrameByTimeStamp(int64_t ts) = 0;

            /**
            @brief    Return the current playback frame time stamp.
            @return The time stamp, in 100ns.
            */
            virtual int64_t PXCAPI QueryFrameTimeStamp(void) = 0;

            /**
            @brief    Return the frame number in the recorded file.
            @return The number of frames.
            */
            virtual int32_t PXCAPI QueryNumberOfFrames(void) = 0;

            /**
            @brief Enable detection of device rotation. Call function PXCImage::QueryRotation on current image to query rotation data.
            @param[in] enableFlag       If true, enable detection of device rotation, otherwise disable.
            @return PXC_STATUS_NO_ERROR         Successful execution.
            */
            virtual Status PXCAPI EnableDeviceRotation(bool32_t enableFlag) = 0;

            /**
            @brief Query if device rotation enabled.
            */
            virtual bool32_t PXCAPI IsDeviceRotationEnabled() = 0;

			/**
			@brief Create an instance of the PXCCaptureManager interface.
			@return The PXCCaptureManager instance.
			*/
			__inline static CaptureManager* CreateInstance(Session *session) {
				CaptureManager *cm = 0;
				session->CreateImpl<CaptureManager>(&cm);
				return cm;
			}
        };
    }
}
