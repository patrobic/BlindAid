/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcimage.h
Defines the PXCImage interface, which manages image buffer access.
*/
#pragma once
#include "pxcbase.h"
#include "pxcaddref.h"
#include "pxcmetadata.h"
#include "RealSense/Image.h"

/**
This class defines a standard interface for image buffer access.

The interface extends PXCAddRef. Use QueryInstance<PXCAddRef>(), or the helper
function AddRef() to access the PXCAddRef features.

The interface extends PXCMetadata. Use QueryMetadata() to access 
the PXCMetadata features.
*/
typedef Intel::RealSense::Image PXCImage;
