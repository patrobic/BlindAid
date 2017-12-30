/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/SampleReader.h"

namespace Intel {
    namespace RealSense {
        namespace Service {
            class SampleReaderService : public Base {
            public:

                PXC_CUID_OVERWRITE(0x49384958);

                virtual void PXCAPI SetSenseManager(SenseManager* sm) = 0;
                virtual void PXCAPI SetIdentifier(int32_t mid) = 0;
            };
        }
    }
}
