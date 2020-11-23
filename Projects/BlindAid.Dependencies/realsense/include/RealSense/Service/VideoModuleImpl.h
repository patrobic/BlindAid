/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/VideoModule.h"
#include "RealSense/VideoModuleCommon.h"
#include "RealSense/Service/SenseManagerService.h"

namespace Intel {
    namespace RealSense {
        namespace Service {
            template <class MODULE> class VideoModuleImpl : public BaseImpl2<VideoModule, MODULE> {
            public:
#ifdef _WIN32
                virtual void PXCAPI SetSenseManager(SenseManager *sm) {
                    this->sm = sm;
                }

                virtual void PXCAPI Pause(bool pause) {
                    if (sm) sm->QueryInstance<SenseManagerService>()->PauseModule(MODULE::CUID, pause);
                }

                virtual Sample* PXCAPI GetSample() {
                    return sm ? sm->QueryInstance<SenseManagerService>()->QuerySample(MODULE::CUID) : NULL;
                }

                /**
                @brief Add listener to the SampleReader events.
                @param[in] handler    The handler instance.
                */
                virtual void PXCAPI AddFrameListener(typename VideoModuleCommon<MODULE>::FrameHandler *handler) {
                    if (sm && handler) sm->QueryInstance<SenseManagerService>()->AddFrameListener(MODULE::CUID, handler);
                }

                /**
                @brief Remove listener from the SampleReader events.
                @param[in] handler    The handler instance.
                */
                virtual void PXCAPI RemoveFrameListener(typename VideoModuleCommon<MODULE>::FrameHandler *handler) {
                    if (sm && handler) sm->QueryInstance<SenseManagerService>()->RemoveFrameListener(MODULE::CUID, handler);
                }

            protected:

                SenseManager *sm;
#endif
            };
        }
    }
}
