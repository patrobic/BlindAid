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

namespace Intel {
    namespace RealSense {

        typedef int32_t bool32_t;

        /** A rectangle type defined with pxcI32 values */
        struct RectI32 {
            int32_t x, y, w, h;
        };

        /** A rectangle type defined with pxcF32 values */
        struct RectF32 {
            float x, y, w, h;
        };

        /** A type representing an two dimensional extent defined with pxcI32 values */
        struct SizeI32 {
            int32_t width, height;
        };

        /** A type representing an three dimensional extent defined with pxcF32 values */
        struct Size3DF32 {
            float width, height, depth;
        };

        /** A type representing a two dimensional point defined with pxcF32 values */
        struct PointF32 {
            float x, y;
        };

        /** A type representing a two dimensional point defined with pxcI32 values */
        struct PointI32 {
            int32_t x, y;
        };

        /** A type representing a range defined with pxcF32 values */
        struct RangeF32 {
            float min, max;
        };

        /** A type representing a three-dimensional point defined with pxcF32 values */
        struct Point3DF32 {
            float x, y, z;
        };

        /** A type representing a four-dimensional point or vector, for instance quaternion */
        struct Point4DF32 {
            float x, y, z, w;
        };

        /** A type representing a 3d box with pxcF32 values */
        struct Box3DF32 {
            Point3DF32 centerOffset, dimension;
        };

        /** This macro constructs a pxcUID given four byte values.  The arguments will
        be evaluated exactly once, cast to unsigned int and shifted into one of the
        byte positions.  Hence, arguments must not hold values larger than a byte.
        The result is a pxcUID. */
#define PXC_UID(X1,X2,X3,X4) ((int32_t)(((unsigned int)(X4)<<24)+((unsigned int)(X3)<<16)+((unsigned int)(X2)<<8)+(unsigned int)(X1)))

        /** This macro defines a constant symbol of an integral type within the scope
        of a class or struct.  The type of the constant is that of a symbol in an
        anonymous enumeration (with unspecified width), hence an unspecified
        integral compile-time constant. */
#define PXC_DEFINE_CONST(Y,X) enum {Y=X}

        /** This macro defines a UID in the context of a class deriving from PXCBase. */
#define PXC_DEFINE_UID(Y,X1,X2,X3,X4) enum {Y=PXC_UID(X1,X2,X3,X4)}

#if defined(_WIN32) || defined(_WIN64)
#define PXC_DEPRECATED(_MSG) __declspec(deprecated(_MSG))
#else
#define PXC_DEPRECATED(_MSG)
#endif
    }
}
