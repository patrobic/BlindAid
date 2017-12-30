/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxccapture.h"
#include "pxcvideomodule.h"
#include "RealSense/CaptureManager.h"

/** 
    The CaptureManager interface provides the following features:
    (1) Locate an I/O device that meets all module input needs.
    (2) Record any streaming data to a file and playback from the file.
*/
typedef Intel::RealSense::CaptureManager PXCCaptureManager;
