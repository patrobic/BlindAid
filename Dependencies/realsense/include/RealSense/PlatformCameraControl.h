/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Capture.h"

namespace Intel {
    namespace RealSense {

        class PlatformCameraControl : public Base
        {
        public:
            class Handler
            {
            public:
                virtual void PXCAPI OnPlatformCameraSample(Sample& sample) = 0;
                virtual void PXCAPI OnPlatformCameraError() = 0;
            };

            PXC_CUID_OVERWRITE(PXC_UID('D', 'P', 'C', 'C'));

            virtual Status PXCAPI EnumPhotoProfile(int32_t idx, StreamProfile* photoProfile) = 0;
            virtual Status PXCAPI TakePhoto(const StreamProfile& photoProfile, Handler* handler) = 0;
            virtual Projection* PXCAPI CreatePhotoProjection(const StreamProfile& profile) = 0;
        };
    }
}
