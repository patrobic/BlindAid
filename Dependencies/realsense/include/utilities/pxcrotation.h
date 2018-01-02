/*******************************************************************************                                                                                                                                                                                                                          /*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/

/** @file PXCRotations.h
    Defines the PXCRotations interface, which allows creating and handling of rotation instances, using different representations.
	Various useful rotation algorithms are also supported.
	Available representations: Quaternions, Euler Angles, Rotations Matrices, Axis + Angle.
 */

#pragma once
#include "pxcbase.h"
#include "RealSense/Utility/Rotation.h"

/** @class PXCRotation 
	@brief A class factory that allows the creation of a Rotation instance using different input representations. 
	Available representations: Quaternions, Euler Angles, Rotations Matrices, Axis + Angle.     

	example code sample - create Rotation instance from quaternion and get Euler angles representation.

	PXCPoint4DF32 quaternion; // You should set the quaternion

	// Create PXCsession instance
	PXCSession* session = PXCSession::CreateInstance();

	// Create PXCRotation instance
	PXCRotation* rotation;
	session->CreateImpl<PXCRotation>(&rotation);

	//Set rotation from quaternion
	rotation->SetFromQuaternion(quaternion)

	// Query rotation in Euler angles representation
	PXCPoint3DF32 eulerAngles = rotation->QueryEulerAngles();
*/
typedef Intel::RealSense::Utility::Rotation PXCRotation;
