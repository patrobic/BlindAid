/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/SenseManager.h"

namespace Intel {
    namespace RealSense {
        namespace Service {

            class SenseManagerService : public Base {
            public:
                PXC_CUID_OVERWRITE(0x758075F4);

                /**
                    @brief  Create a module instance, managed by SenseManaer. The function returns
                    the module instance and the module identifier, if different from the specified one.
                    @param[in, out] mid       The base module identifier. [out] current identifier.
                    @param[in] renew          If true, always create a new instance.
                    @param[out] module        The created module instance.
                */
                virtual Status    PXCAPI ActivateModule(int32_t &mid, bool renew, Base **module) = 0;
                virtual void      PXCAPI PauseModule(int32_t mid, bool32_t pause) = 0;
                virtual Sample*   PXCAPI QuerySample(int32_t mid) = 0;

                class FrameHandlerBase {
                public:
                    virtual void PXCAPI OnFrameProcessed(Base *sender, Sample *sample) = 0;
                };

                virtual void PXCAPI AddFrameListener(int32_t mid, FrameHandlerBase *handler) = 0;
                virtual void PXCAPI RemoveFrameListener(int32_t mid, FrameHandlerBase *handler) = 0;
            };
        }
    }
}
