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
			@brief Standalone recording interface. The recording sequence as follows:
                CreateInstance();
				VideoModule::SetCaptureProfile();
				VideoModule::SetProjection();
				optional AddStreams();
				while () { VideoModule::ProcessSample }
				Release();
		*/
		class Recording : public Base {
        public:
            PXC_CUID_OVERWRITE(0x9472893a);

            /**
            @brief Create the recording instance. Each instance can do a single recording.
            @return The Recording instance.
            */
            __inline static Recording* CreateInstance(Session *session, const wchar_t* filename) {
                Recording *recording = 0;
                session->CreateImpl<Recording>(&recording);
                if (recording && recording->SetFileName(filename) < Status::STATUS_NO_ERROR) {
                    recording->Release();
                    recording = NULL;
                }
                return recording;
            }

            /**
            @brief Wraps device object into another device object with recording all data into file
            @param[in] device       The device object to wrap into recording device
            */
            virtual Device* PXCAPI WrapIntoRecordingDevice(Device *device) = 0;

            /**
                @brief Configure the maximum file size.
                @param[in] fileSize   File size in bytes.
            */
            virtual void PXCAPI SetMaxFileSize(int64_t fileSize) = 0;

            /**
                @brief Returns how many bytes recorded to file on disk.
                @return the file size.
            */
            virtual int64_t PXCAPI QueryFileSize() = 0;

            /**
                @brief Configure the maximum buffer size.
                The buffer in memory used in case writing to disk is slower than camera data rate.
                @param[in] bufferSize   Buffer size in bytes.
            */
			virtual void PXCAPI SetMaxBufferSize(int64_t bufferSize) = 0;

			/**
				@brief Returns the current buffer size in memory.
				@return the current buffer size.
			*/
			virtual int64_t PXCAPI QueryBufferSize() = 0;

			/**
				@brief Configure the sync mode: by default it is on.
				       The sync mode overrides the sample sync id.
				@param[in] sync         If true, overwrite the sync id.
			*/
			virtual void PXCAPI SetSyncMode(bool syncMode) = 0;

			/**
				@brief Add extra streams like an HD stream into the recorded file. 
				Call VideoModule::ProcessSample for aysnchrously inserting samples into the recorded file.
				@param[in] profile      The stream info to be recorded into the file.
			*/
			virtual void PXCAPI AddStreams(StreamProfileSet *profile) = 0;

        protected:
            /**
            @brief Set the output file name.
            @param[in] file         The file name.
            */
            virtual Status PXCAPI SetFileName(const wchar_t* file) = 0;
		};
    }
}
