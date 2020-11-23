/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcdefs.h
    Defines various primitive types used throughout the SDK as well as some
    common structures.  All primitive types start with the prefix ``pxc''.
    Integral primitive types follow that with either an `I' or `U' to indicate
    signed or unsigned and then an integer indicating the number of bits used
    by that type.  For instance, pxcI32 aliases a 32-bit integral type.

    Finally, this class also defines some helper macros to construct some of
    these types as well as other general tasks.
 */
#pragma once
#include <stdint.h>
#include "RealSense/Type.h"

typedef wchar_t pxcCHAR;

/** A signed 16-bit integer */
typedef int16_t             pxcI16;
/** This type is used as a unique identifier */
typedef int32_t             pxcUID;
/** A signed 32-bit integer */
typedef int32_t             pxcI32;
/** An signed 64-bit integer */
typedef int64_t             pxcI64;
/** An unsigned 16-bit integer */
typedef uint16_t            pxcU16;
/** A byte (an unsigned 8-bit integer) */
typedef uint8_t             pxcBYTE;
/** A common type for enumeration values */
typedef int32_t             pxcEnum;
/** A boolean value, zero indicates false */
typedef int32_t             pxcBool;
/** A single-precision (32-bit) floating point type */
typedef float               pxcF32;
/** A double-precision (64-bit) floating point type */
typedef double              pxcF64;

/** A rectangle type defined with pxcI32 values */
typedef Intel::RealSense::RectI32 PXCRectI32;

/** A rectangle type defined with pxcF32 values */
typedef Intel::RealSense::RectF32 PXCRectF32;

/** A type representing an two dimensional extent defined with pxcI32 values */
typedef Intel::RealSense::SizeI32 PXCSizeI32;

/** A type representing an three dimensional extent defined with pxcF32 values */
typedef Intel::RealSense::Size3DF32 PXCSize3DF32;

/** A type representing a two dimensional point defined with pxcF32 values */
typedef Intel::RealSense::PointF32 PXCPointF32;

/** A type representing a two dimensional point defined with pxcI32 values */
typedef Intel::RealSense::PointI32 PXCPointI32;

/** A type representing a range defined with pxcF32 values */
typedef Intel::RealSense::RangeF32 PXCRangeF32;

/** A type representing a three-dimensional point defined with pxcF32 values */
typedef Intel::RealSense::Point3DF32 PXCPoint3DF32;

/** A type representing a four-dimensional point or vector, for instance quaternion */
typedef Intel::RealSense::Point4DF32 PXCPoint4DF32;

/** A type representing a 3d box with pxcF32 values */
typedef Intel::RealSense::Box3DF32 PXCBox3DF32;
