                                                                                                                                                                                                                            /*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxccapture.h
    Defines the PXCCapture interface, which allows a program create and interact
    with video streams. 
 */
#pragma once
#include "pxcimage.h"
#include "pxcsyncpoint.h"
#include "RealSense/Capture.h"
#include "RealSense/Sample.h"
#include "pxcprojection.h"

/**
   This interface provides member functions to create instances of and query stream capture devices.
*/
typedef Intel::RealSense::Capture PXCCapture;
