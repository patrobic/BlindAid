/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcmetadata.h
    Defines the PXCMetadata interface, which is used for managing
    metadata storage.
 */
#pragma once
#include "pxcbase.h"
#include "RealSense/Metadata.h"

/**
    This interface manages metadata storage.  The PXCSession, PXCImage
    and PXCAudio implementations expose the PXCMetadata interface.
 */
typedef Intel::RealSense::Metadata PXCMetadata;
