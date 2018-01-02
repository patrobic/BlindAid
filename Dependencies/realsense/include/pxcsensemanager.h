/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxccapturemanager.h"
#include "pxcsession.h"
#include "RealSense/SenseManager.h"

/**
    This is the main interface for the SDK pipeline.
    Control the pipeline execution with this interface.
*/ 
typedef Intel::RealSense::SenseManager                                     PXCSenseManager;
typedef Intel::RealSense::Face::FaceModule                                 PXCFaceModule;
typedef Intel::RealSense::Hand::HandModule                                 PXCHandModule;
typedef Intel::RealSense::HandCursor::HandCursorModule                     PXCHandCursorModule;
typedef Intel::RealSense::Blob::BlobModule                                 PXCBlobModule;  
typedef Intel::RealSense::PersonTracking::PersonTrackingModule             PXCPersonTrackingModule;
typedef Intel::RealSense::TouchlessControl::TouchlessController            PXCTouchlessController;
typedef Intel::RealSense::Segmentation::Seg3D                              PXC3DSeg;
typedef Intel::RealSense::Scan::Scan3D                                     PXC3DScan;
typedef Intel::RealSense::ScenePerception::ScenePerception                 PXCScenePerception;
typedef Intel::RealSense::Videography::EnhancedVideo                       PXCEnhancedVideo;
typedef Intel::RealSense::ObjectRecognition::ObjectRecognitionModule       PXCObjectRecognitionModule;
typedef Intel::RealSense::ObjectTracking::Tracker                          PXCTracker;
