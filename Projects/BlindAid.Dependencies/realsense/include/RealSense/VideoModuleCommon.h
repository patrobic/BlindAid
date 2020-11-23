/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/VideoModule.h"
#ifdef _WIN32
#include "RealSense/Service/SenseManagerService.h"
#endif

namespace Intel {
    namespace RealSense {

        template <class MODULE> class VideoModuleCommon : public Base
        {
#ifdef _WIN32
        public:
            /**
            @brief Pause/Resume the module data processing.
            @param[in] pause     The boolean value to pause or resume.
            */
            __inline static MODULE* PXCAPI Activate(SenseManager *sm) {
                if (!sm) return 0;
                Base *module = 0;
                int32_t mid = MODULE::CUID;
                sm->QueryInstance<Service::SenseManagerService>()->ActivateModule(mid, false, &module);
                if (!module) return 0;
                MODULE *module2 = module->QueryInstance<MODULE>();
                if (module2) module2->SetSenseManager(sm);
                return module2;
            }

            /**
            @brief Retrieve the module processed sample. If NULL, the module is in the middle of processing data.
            @return the Sample instance.
            The Sample instance is managed. Do not release it.
            */
            virtual Sample* PXCAPI GetSample() = 0;

            /**
            @brief Pause/Resume the module data processing.
            @param[in] pause     The boolean value to pause or resume.
            */
            virtual void PXCAPI Pause(bool pause) = 0;

            class FrameHandler : public Service::SenseManagerService::FrameHandlerBase {
            public:

                /**
                @brief Invoked when some sample data is ready.
                @param[in] sender     The SampleReader instance that manages the streams.
                @param[in] sample     The Sample instance that contains the data.
                */
                virtual void PXCAPI OnFrameProcessed(MODULE *sender, Sample* sample) = 0;

            protected:

                virtual void PXCAPI OnFrameProcessed(Base *sender, Sample* sample) {
                    OnFrameProcessed(sender->QueryInstance<MODULE>(), sample);
                }
            };

            /**
            @brief Add listener to the SampleReader events.
            @param[in] handler    The handler instance.
            */
            virtual void PXCAPI AddFrameListener(FrameHandler *handler) = 0;

            /**
            @brief Remove listener from the SampleReader events.
            @param[in] handler    The handler instance.
            */
            virtual void PXCAPI RemoveFrameListener(FrameHandler *handler) = 0;

        protected:
            virtual void PXCAPI SetSenseManager(SenseManager *sm) = 0;
#endif
        };
    }
}
