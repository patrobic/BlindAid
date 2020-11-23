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
#include "RealSense/Base.h"
#include "RealSense/Session.h"

namespace Intel {
    namespace RealSense {
        namespace Utility {

            /** @class PXCPointConverter
            A utility for converting 2D/3D data points from defined source to a defined target.
            The class provides with setters for both source and target rectangle/box
            The class provides with getters for 2D/3D converted points
            2D Rectangle - A data structure that represents a 2D rectangle
            3D Box - A data structure representing a "box" in 3D space (a 3D cube).
            Example: convert from hand-joint image coordinates to user defined screen area coordinates.
            Example: convert from face-landmark 3d position to a 3d game coordinate system.
            */
            class PointConverter : public Base
            {
            public:

                /* Constants */
                PXC_CUID_OVERWRITE(PXC_UID('P', 'P', 'C', 'F'));

                /**
                @brief Set 2D image rectangle source
                @param[in] rectangle2D containing desired source rectangle dimensions
                @note rectangle2D x,y is the rectangle starting point, w is rectangle width, h is rectangle height
                @return PXC_STATUS_VALUE_OUT_OF_RANGE if rectangle2D w,h params <= 0
                @return PXC_STATUS_NO_ERROR if rectangle2D w,h params > 0
                */
                virtual Status /*Deprecated*/ PXCAPI Set2DSourceRectangle(RectF32 rectangle2D) = 0;

				__inline Status SetSourceRectangle2D(RectF32 rectangle2D) {
					return Set2DSourceRectangle(rectangle2D);
				}

                /**
                @brief Set 2D target rectangle
                @param[in] rectangle2D containing desired target rectangle dimensions
                @note rectangle2D x,y is the rectangle starting point, w is rectangle width, h is rectangle height
                @return PXC_STATUS_VALUE_OUT_OF_RANGE if rectangle2D w,h params <= 0
                @return PXC_STATUS_NO_ERROR if rectangle2D w,h params > 0
                */
                virtual Status PXCAPI /*Deprecated*/ Set2DTargetRectangle(RectF32 rectangle2D) = 0;

				__inline Status SetTargetRectangle2D(RectF32 rectangle2D) {
					return Set2DTargetRectangle(rectangle2D);
				}

                /**
                @brief Set 2D point to be converted
                @note only relevant when using CreateCustomPointConverter
                @return PXC_STATUS_ITEM_UNAVAILABLE if not using CustomPointConverter
                */
                virtual Status /*Deprecated*/ PXCAPI Set2DPoint(PointF32 point2D) = 0;

				__inline Status SetPoint2D(PointF32 point2D) {
					return Set2DPoint(point2D);
				}

                /**
                @brief Get converted 2D point from source to target
                @note If not using CustomPointConverter, Call Module output->Update() before calling this function in order to get converted point based on updated frame data.
                @note If point is out of source rectangle the converted point value will be target rectangle x,y
                @param[out] PointF32 converted 2D point
                @return Converted 2D Point
                */
                virtual PointF32 /*Deprecated*/ PXCAPI GetConverted2DPoint() = 0;
				 
				__inline PointF32 GetConvertedPoint2D() {
					return GetConverted2DPoint();
				}

                /**
                @brief inverting x,y axis
                Use if you wish to invert converted point axis.
                @example Use Invert2DAxis(false, true) if user app y axis is facing up
                @param[in] x invert x axis
                @param[in] y invert y axis
                @return PXC_STATUS_NO_ERROR
                */
                virtual Status /*Deprecated*/ PXCAPI Invert2DAxis(bool32_t x, bool32_t y) = 0;

				__inline Status InvertAxis2D(bool32_t x, bool32_t y)
				{
					return Invert2DAxis(x, y);
				}

                /**
                @brief Set 3D world box source
                @param[in] box3D containing desired source world box dimensions
                @note box3D centerOffset defines the box center point and dimension
                @return PXC_STATUS_VALUE_OUT_OF_RANGE if any of box3D dimension params <= 0
                @return PXC_STATUS_NO_ERROR if box3D dimension params > 0
                */
                virtual Status /*Deprecated*/ PXCAPI Set3DSourceBox(Box3DF32 box3D) = 0;

				__inline Status SetSourceBox3D(Box3DF32 box3D) {
					return Set3DSourceBox(box3D);
				}

                /**
                @brief Set 3D target box
                @param[in] box3D containing desired target box dimensions
                @note box3D centerOffset defines the box center point and dimension
                @return PXC_STATUS_VALUE_OUT_OF_RANGE if any of box3D dimension params <= 0
                @return PXC_STATUS_NO_ERROR if box3D dimension params > 0
                */
                virtual Status /*Deprecated*/ PXCAPI Set3DTargetBox(Box3DF32 box3D) = 0;

				__inline Status SetTargetBox3D(Box3DF32 box3D) {
					return Set3DTargetBox(box3D);
				}

                /**
                @brief Set 3D point to be converted
                @note only relevant when using CreateCustomPointConverter
                @return PXC_STATUS_ITEM_UNAVAILABLE if not using CustomPointConverter
                */
                virtual Status /*Deprecated*/ PXCAPI Set3DPoint(Point3DF32 point3D) = 0;

				__inline Status SetPoint3D(Point3DF32 point3D) {
					return Set3DPoint(point3D);
				}

                /**
                @brief Get converted 3D point from source to target
                @note If not using CustomPointConverter, Call Module output->Update() before calling this function in order to get converted point based on updated frame data.
                @note If point is out of source box the converted point value will be target box x,y,z
                @param[out] PXCPoint3DF32 converted 3D point
                @return Converted 3D Point
                */
                virtual Point3DF32 /*Deprecated*/ PXCAPI GetConverted3DPoint() = 0;

				__inline Point3DF32 GetConvertedPoint3D() {
					return GetConverted3DPoint();
				}

                /**
                @brief inverting x,y,z axis
                Use if you wish to invert converted point axis.
                @example Use Invert3DAxis(false,true,false ) if user app y axis is facing down
                @param[in] x invert x axis
                @param[in] y invert y axis
                @param[in] z invert z axis
                @return PXC_STATUS_NO_ERROR
                */
                virtual Status /*Deprecated*/ PXCAPI Invert3DAxis(bool32_t x, bool32_t y, bool32_t z) = 0;

				__inline Status InvertAxis3D(bool32_t x, bool32_t y, bool32_t z) {
					return Invert3DAxis(x, y, z);
				}

				/**
				@brief    Create an instance of the PointConverter interface.
				@return The PointConverter instance.
				*/
				__inline static PointConverter* CreateInstance(Session* session) {
					PointConverter *converter = 0;
					session->CreateImpl<PointConverter>(&converter);
					return converter;
				}
            };
        }
    }
}
