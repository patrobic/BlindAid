/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Session.h"
#include "RealSense/PowerState.h"

namespace Intel {
    namespace RealSense {

            namespace Service {

                class PowerStateServiceClient :public Base {
                public:
                    PXC_CUID_OVERWRITE(PXC_UID('P', 'W', 'M', 'C'));

                    /* Queries unique id for desired device & stream and client id */
                    virtual int32_t QueryUniqueId(int32_t deviceId, int32_t streamId, int32_t mId) = 0;

                    /* Register module with the Power Manager */
                    virtual Status RegisterModule(int32_t uId, ImplGroup group, ImplSubgroup subGroup) = 0;

                    /* Unregister module from certain device & stream. All further requests for this device from this module will be ignored */
                    virtual Status UnregisterModule(int32_t uId) = 0;

                    /* Request state for stream on device, module may call QueryState to test if the state was actually set */
                    virtual Status SetState(int32_t uId, PowerStateType state) = 0;

                    /* Query power state on stream on device */
                    virtual Status QueryState(int32_t uId, PowerStateType* state) = 0;
                };
            }
        }
    }
