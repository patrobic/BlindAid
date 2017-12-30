/*******************************************************************************                                                                                                                                                                                                                          /*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file PXCSmoother.h
    Defines the PXCSmoother interface, which allows to smooth any data using different algorithms
 */
#pragma once
#include "pxcbase.h"
#include "RealSense/Utility/Smoother.h"

/** @class PXCSmoother 
	A utility that allows smoothing data of different types, using a variety of algorithms
	Stabilizer Smoother – The stabilizer smoother keeps the smoothed data point stable as long as it has not moved more than a given threshold. 
	Weighted Smoother – The weighted smoother applies a (possibly) different weight to each of the previous data samples. 
	Quadratic Smoother – The quadratic smoother is a time based smoother ideal for UI (User Interface) purposes. 
	Spring Smoother – The spring smoother is a time based smoother ideal for gaming purposes. 
*/
typedef Intel::RealSense::Utility::Smoother PXCSmoother;
