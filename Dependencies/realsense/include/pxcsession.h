/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcsession.h
    Defines the PXCSession interface, which maintains the SDK context.  The
    application can query and create instances of I/O and algorithm module
    implementations.
*/
#pragma once
#include "pxcbase.h"
#include "pxcversion.h"
#include "pxcimage.h"
#include "pxcmetadata.h"
#include "RealSense/Session.h"

/**
    This class defines a standard interface for maintaining the SDK context.
    The application can query and create instances of I/O and algorithm module
    implementations.

    The interface extends PXCMetadata. Use QueryMetadata() to access 
    the PXCMetadata features.
*/
typedef Intel::RealSense::Session PXCSession;
typedef Intel::RealSense::SenseManager PXCSenseManager;
typedef Intel::RealSense::CaptureManager PXCCaptureManager;
typedef Intel::RealSense::PowerState PXCPowerState;
typedef Intel::RealSense::Photography::Photo PXCPhoto;
