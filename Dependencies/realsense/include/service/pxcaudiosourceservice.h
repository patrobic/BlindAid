/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcbase.h"
#include "pxcaudio.h"
#include "RealSense/Service/AudioSourceService.h"

/**
	The PXCAudioSourceService extends PXCAudioSource and operates on audio device selected
    in PXCAudioSource::SetDevice function.
*/
typedef Intel::RealSense::Service::AudioSourceService PXCAudioSourceService;
