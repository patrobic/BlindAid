/******************************************************************************
INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2016 Intel Corporation. All Rights Reserved.
*******************************************************************************/
#pragma once
#include "RealSense/SenseManager.h"
#include "RealSense/VideoModule.h"
#include "RealSense/Session.h"
#include "RealSense/Service/SenseManagerService.h"
#include "RealSense/Service/SampleReaderService.h"

namespace Intel {
    namespace RealSense {

        class SampleReader : public Base {
        public:
            PXC_CUID_OVERWRITE(0x36343489);

            /**
            @brief Activate a SampleReader instance out of the SenseManager instance.
            @param[in] sm           The SenseManager instance.
            @return The SampleReader instance.
            */
            static __inline SampleReader* Activate(SenseManager *sm) {
                Base* reader = 0;
                int32_t mid = CUID;
                if (sm) sm->QueryInstance<Service::SenseManagerService>()->ActivateModule(mid, true, &reader);
                if (!reader) return 0;
                Service::SampleReaderService *srs = reader->QueryInstance<Service::SampleReaderService>();
                srs->SetSenseManager(sm);
                srs->SetIdentifier(mid);
                return reader->QueryInstance<SampleReader>();
            }

            /**
            @brief Enable a stream in the SampleReader. All streams enabled within the same SampleReader instance
                are synchronized. To request asynchronous streams, activate multiple SampleReader instances.
            @param[in] width        The requested stream width.
            @param[in] height       The requested stream height.
            @param[in] fps          The requested stream frame rate.
            @param[in] options      The requested stream options.
            */
            virtual void PXCAPI EnableStream(StreamType type, int32_t width = 0, int32_t height = 0, float fps = 0, StreamOption options = Intel::RealSense::StreamOption::STREAM_OPTION_ANY) = 0;

            /**
            @brief Enable a set of streams at once. All streams enabled within the same SampleReader instance
            are synchronized. To request asynchronous streams, activate multiple SampleReader instances.
            @param[in] ddesc        Multiple stream request descriptions.
            */
            virtual void PXCAPI EnableStreams(const DataDesc *ddesc) = 0;

            /**
            @brief Pause/resume delivering the stream samples. The camera is still open even if pause=true.
            @param[in] pause        if true, pause the stream sample delivery.
            */
            virtual void PXCAPI Pause(bool pause) = 0;

            /**
            @brief Get the most recent sample.
            @return The Sample instance.
            The sample instance and the images are managed. Do not release it.
            */
            virtual Sample* PXCAPI GetSample() = 0;

            class Handler {
            public:

                /**
                @brief Invoked when some sample data is ready.
                @param[in] sender     The SampleReader instance that manages the streams.
                @param[in] sample     The Sample instance that contains the data.
                */
                virtual void PXCAPI OnSampleArrived(SampleReader *sender, Sample* sample) = 0;
            };

            /**
            @brief Add listener to the SampleReader events.
            @param[in] handler    The handler instance.
            */
            virtual void PXCAPI AddListener(Handler *handler) = 0;

            /**
            @brief Remove listener from the SampleReader events.
            @param[in] handler    The handler instance.
            */
            virtual void PXCAPI RemoveListener(Handler *handler) = 0;
        };
    }
}
