/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/

#pragma once
#include "RealSense/Image.h"
#include "RealSense/Capture.h"

#pragma warning(push)
#pragma warning(disable:4351) /* new behavior: elements of array will be default initialized */

namespace Intel {
    namespace RealSense {
        PXC_DEFINE_CONST(STREAM_LIMIT, 8);

        /**
        @struct Sample
        The capture sample that contains multiple streams.
        */
        struct Sample {
            Image *color;
            Image *depth;
            Image *ir;
            Image *left;
            Image *right;
            Image *auxColor;
            Image *reserved[STREAM_LIMIT - 6];

            /**
            @brief Return the image element by StreamType.
            @param[in] type        The stream type.
            @return The image instance.
            */
            __inline Image* &operator[](StreamType type) {
                if (type == StreamType::STREAM_TYPE_COLOR)    return color;
                if (type == StreamType::STREAM_TYPE_DEPTH)    return depth;
                if (type == StreamType::STREAM_TYPE_IR)       return ir;
                if (type == StreamType::STREAM_TYPE_LEFT)     return left;
                if (type == StreamType::STREAM_TYPE_RIGHT)    return right;
                if (type == StreamType::STREAM_TYPE_AUX_COLOR) return auxColor;
                for (int i = sizeof(reserved) / sizeof(reserved[0]) - 1, j = (1 << (STREAM_LIMIT - 1)); i >= 0; i--, j >>= 1)
                    if (type&j) return reserved[i];
                return reserved[sizeof(reserved) / sizeof(reserved[0]) - 1];
            }

            /**
            @brief Release the sample elements if not NULL
            */
            __inline void ReleaseImages(void) {
                if (color) color->Release(), color = 0;
                if (depth) depth->Release(), depth = 0;
                if (ir) ir->Release(), ir = 0;
                if (left) left->Release(), left = 0;
                if (right) right->Release(), right = 0;
                if (auxColor) auxColor->Release(), auxColor = 0;
                for (int i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++)
                    if (reserved[i]) reserved[i]->Release(), reserved[i] = 0;
            }

            /**
            @brief Retain the sample elements if not NULL
            */
            __inline void RetainImages(void) {
                if (color) color->AddRef();
                if (depth) depth->AddRef();
                if (ir) ir->AddRef();
                if (left) left->AddRef();
                if (right) right->AddRef();
                if (auxColor) auxColor->AddRef();
                for (int i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++)
                    if (reserved[i]) reserved[i]->AddRef();
            }

            /**
            @brief The constructor zeros the image instance array
            */
            __inline Sample(void) :color(0), depth(0), ir(0), left(0), right(0), auxColor(0), reserved() {
            }

            /**
            @brief Assess internal pointers and returns true if at least one of them have data
            */
            __inline bool IsEmpty(void) {
                if (color)  return false;
                if (depth)  return false;
                if (ir)     return false;
                if (left)   return false;
                if (right)  return false;
                if (auxColor) return false;
                for (int i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++)
                    if (reserved[i]) return false;
                return true;
            }
        };
    }
}

#pragma warning(pop)
