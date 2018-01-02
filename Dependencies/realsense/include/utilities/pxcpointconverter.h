/*******************************************************************************                                                                                                                                                                                                                          /*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file PXCPointConverter.h
    Defines the PXCPointConverter interface, which allows to convert 2D/3D data points.
 */
#pragma once
#include "pxcbase.h"
#include "RealSense/Utility/PointConverter.h"

/** @class PXCPointConverter 
	A utility for converting 2D/3D data points from defined source to a defined target.
	The class provides with setters for both source and target rectangle/box
	The class provides with getters for 2D/3D converted points
	2D Rectangle - A data structure that represents a 2D rectangle
	3D Box - A data structure representing a "box" in 3D space (a 3D cube).
	Example: convert from hand-joint image coordinates to user defined screen area coordinates.
	Example: convert from face-landmark 3d position to a 3d game coordinate system.
*/
typedef Intel::RealSense::Utility::PointConverter PXCPointConverter;
