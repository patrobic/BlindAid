/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2012-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcprojection.h
Defines the Projection interface, which defines mappings between
pixel, depth, and real world coordinates.
*/
#pragma once
#include "RealSense/Image.h"
#include "RealSense/Calibration.h"
#include "RealSense/Reference.h"

#ifndef _WIN32
extern "C" {
    struct rs_intrinsics;
    struct rs_extrinsics;
    void* RS_Projection_CreateInstanceFromIntrinsicsExtrinsics(rs_intrinsics *colorIntrinsics, rs_intrinsics *depthIntrinsics, rs_extrinsics *extrinsics);
}
#endif

namespace Intel {
    namespace RealSense {

        /**
        This interface defines mappings between various coordinate systems
        used by modules of the SDK. Call the PXCCapture::Device::CreateProjection
        to create an instance of this interface.

        The class extends PXCSerializeableService. Use QueryInstance<PXCSerializeableService>
        to access the PXCSerializableService interface.
        */
        class Projection : public Base {
        public:
            PXC_CUID_OVERWRITE(0x494A8537);
            enum { CUID_PROJECTION_CLIPPING_NONE = 0x11a4c912 };

            enum ProjectionOption {
                PROJECTION_OPTION_DEFAULT = 0,
                PROJECTION_OPTION_CLIPPING_NONE = 1,
            };

            __inline Projection* SelectOption(ProjectionOption option) {
                if (option == ProjectionOption::PROJECTION_OPTION_CLIPPING_NONE) return (Projection*)QueryInstance(CUID_PROJECTION_CLIPPING_NONE);
                return (Projection*)QueryInstance(CUID);
            }

            /**
            @brief Map depth coordinates to color coordinates for a few pixels.
            @param[in]  npoints         The number of pixels to be mapped.
            @param[in]  pos_uvz         The array of depth coordinates + depth value in the Point3DF32 structure.
            @param[out] pos_ij          The array of color coordinates, to be returned.
            @return PXC_STATUS_NO_ERROR Successful execution.
            */
            virtual Status PXCAPI MapDepthToColor(int32_t npoints, Point3DF32 *pos_uvz, PointF32  *pos_ij) = 0;

            /**
            @brief Map color coordinates to depth coordiantes for a few pixels.
            @param[in]  depth           The depthmap image.
            @param[in]  npoints         The number of pixels to be mapped.
            @param[in]  pos_ij          The array of color coordinates.
            @param[out] pos_uv          The array of depth coordinates, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI MapColorToDepth(Image *depth, int32_t npoints, PointF32 *pos_ij, PointF32 *pos_uv) = 0;

            /**
            @brief Map depth coordinates to world coordinates for a few pixels.
            @param[in]   npoints        The number of pixels to be mapped.
            @param[in]   pos_uvz        The array of depth coordinates + depth value in the Point3DF32 structure.
            @param[out]  pos3d          The array of world coordinates, in mm, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI ProjectDepthToCamera(int32_t npoints, Point3DF32 *pos_uvz, Point3DF32 *pos3d) = 0;

            /**
            @brief Map color pixel coordinates to camera coordinates for a few pixels.
            @param[in]   npoints        The number of pixels to be mapped.
            @param[in]   pos_ijz        The array of color coordinates + depth value in the Point3DF32 structure.
            @param[out]  pos3d          The array of camera coordinates, in mm, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI ProjectColorToCamera(int32_t npoints, Point3DF32 *pos_ijz, Point3DF32 *pos3d) = 0;

            /**
            @brief Map camera coordinates to depth coordinates for a few pixels.
            @param[in]    npoints       The number of pixels to be mapped.
            @param[in]    pos3d         The array of world coordinates, in mm.
            @param[out]   pos_uv        The array of depth coordinates, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI ProjectCameraToDepth(int32_t npoints, Point3DF32 *pos3d, PointF32 *pos_uv) = 0;

            /**
            @brief Map camera coordinates to color coordinates for a few pixels.
            @param[in]    npoints       The number of pixels to be mapped.
            @param[in]    pos3d         The array of world coordinates, in mm.
            @param[out]   pos_ij        The array of color coordinates, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI ProjectCameraToColor(int32_t npoints, Point3DF32 *pos3d, PointF32 *pos_ij) = 0;

            /**
            @brief Retrieve the UV map for the specific depth image. The UVMap is a PointF32 array of depth size width*height.
            @param[in]  depth        The depth image instance.
            @param[out] uvmap        The UV map, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI QueryUVMap(Image *depth, PointF32 *uvmap) = 0;

            /**
            @brief Retrieve the inverse UV map for the specific depth image. The inverse UV map maps color coordinates
            back to the depth coordinates. The inverse UVMap is a PointF32 array of color size width*height.
            @param[in]  depth        The depth image instance.
            @param[out] inv_uvmap    The inverse UV map, to be returned.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI QueryInvUVMap(Image *depth, PointF32 *inv_uvmap) = 0;

            /**
            @brief Retrieve the vertices for the specific depth image. The vertices is a Point3DF32 array of depth
            size width*height. The world coordiantes units are in mm.
            @param[in]  depth        The depth image instance.
            @param[out] vertices     The 3D vertices in World coordinates, to be returned.
            @return PXC_STATUS_NO_ERROR Successful execution.
            */
            virtual Status PXCAPI QueryVertices(Image *depth, Point3DF32 *vertices) = 0;

            /**
            @brief Get the color pixel for every depth pixel using the UV map, and output a color image, aligned in space
            and resolution to the depth image.
            @param[in] depth        The depth image instance.
            @param[in] color        The color image instance.
            @return The output image in the depth image resolution.
            */
            virtual Image* PXCAPI CreateColorImageMappedToDepth(Image *depth, Image *color) = 0;

            /**
            @brief Map every depth pixel to the color image resolution, and output a depth image, aligned in space
            and resolution to the color image. The color image size may be different from original.
            @param[in] depth        The depth image instance.
            @param[in] color        The color image instance.
            @return The output image in the color image resolution.
            */
            virtual Image* PXCAPI CreateDepthImageMappedToColor(Image *depth, Image *color) = 0;

            /**
            @brief    A helper function to access PXCCalibration instance
            */
            __inline Calibration* QueryCalibration(void) {
                return QueryInstance<Calibration>();
            }

            /**
            @brief Increase a reference count.
            */
            __inline void AddRef(void) {
                QueryInstance<Reference>()->AddRef();
            }

#ifndef _WIN32
            /**
            @brief Create instance and initilize on intrinsics and extrinsics
            */
            static __inline Projection* CreateInstance(rs_intrinsics *colorIntrinsics, rs_intrinsics *depthIntrinsics, rs_extrinsics *extrinsics) {
                return (Projection*)RS_Projection_CreateInstanceFromIntrinsicsExtrinsics(colorIntrinsics, depthIntrinsics, extrinsics);
            }
#endif
        };

        typedef Projection::ProjectionOption ProjectionOption;
    }
}
