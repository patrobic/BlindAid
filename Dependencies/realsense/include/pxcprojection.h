/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcprojection.h
Defines the PXCProjection interface, which defines mappings between
pixel, depth, and real world coordinates.
*/
#pragma once
#include "pxcimage.h"
#include "pxccalibration.h"
#include "RealSense/Projection.h"

/**
This interface defines mappings between various coordinate systems
used by modules of the SDK. Call the PXCCapture::Device::CreateProjection
to create an instance of this interface.

The class extends PXCSerializeableService. Use QueryInstance<PXCSerializeableService>
to access the PXCSerializableService interface.
*/
typedef Intel::RealSense::Projection PXCProjection;
