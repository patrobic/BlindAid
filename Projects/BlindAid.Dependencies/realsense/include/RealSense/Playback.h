/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Session.h"
#include "RealSense/Capture.h"

namespace Intel {
    namespace RealSense {
		/**
			@brief Standalone playback interface. The playback sequence as follows:
            CreateInstance();
			Read samples from the Device interface.
			Random access as needed.
			Release();
		*/
        class Playback : public Device {
        public:
            PXC_CUID_OVERWRITE(0x947288aa);

            /**
            @brief Create the Playback instance.
            @param[in] session      The session object.
            @param[in] file         The input file name.
            @return The Playback instance.
            */
            __inline static Playback* CreateInstance(Session *session, const wchar_t* filename) {
                Playback *playback = 0;
                session->CreateImpl<Playback>(&playback);
                if (playback && playback->SetFileName(filename) < Status::STATUS_NO_ERROR) {
                    playback->Release();
                    playback = NULL;
                }
                return playback;
            }

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

        protected:
            /**
            @brief Set the input file name.
            @param[in] file         The file name.
            */
            virtual Status PXCAPI SetFileName(const wchar_t* file) = 0;
		};
    }
}
