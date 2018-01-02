/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Session.h"

namespace Intel {
    namespace RealSense {

            namespace Service {
                class SerializableService : public Base {
                public:
                    PXC_CUID_OVERWRITE(PXC_UID('S', 'L', 'Z', 'S'));

                    struct ProfileInfo {
                        ImplDesc  implDesc;
                        int32_t   dataSize;
                        int32_t   reserved[7];
                    };

                    virtual Status PXCAPI QueryProfile(ProfileInfo *pinfo, uint8_t *data) = 0;
                    virtual Status PXCAPI SetProfile(ProfileInfo *pinfo, uint8_t *data) = 0;
                };

                typedef SerializableService::ProfileInfo SerializableProfileInfo;
            }
        }
    }
