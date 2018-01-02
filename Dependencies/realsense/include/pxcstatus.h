/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcstatus.h
    Defines the return status codes used by SDK interfaces.
  */
#pragma once
#include "RealSense/Status.h"

/**
   This enumeration defines various return codes that SDK interfaces
   use.  Negative values indicate errors, a zero value indicates success,
   and positive values indicate warnings.
 */
typedef Intel::RealSense::Status pxcStatus;
using namespace Intel::RealSense::NSStatus;
