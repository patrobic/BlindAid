/*******************************************************************************                                                                                                                                                                                                                          /*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file PXCSmoother.h
    Defines the PXCSmoother interface, which allows to smooth any data using different algorithms
 */
#pragma once
#include "RealSense/Base.h"
#include "RealSense/Session.h"

namespace Intel {
    namespace RealSense {
        namespace Utility {

            /** @class PXCSmoother
            A utility that allows smoothing data of different types, using a variety of algorithms
            Stabilizer Smoother – The stabilizer smoother keeps the smoothed data point stable as long as it has not moved more than a given threshold.
            Weighted Smoother – The weighted smoother applies a (possibly) different weight to each of the previous data samples.
            Quadratic Smoother – The quadratic smoother is a time based smoother ideal for UI (User Interface) purposes.
            Spring Smoother – The spring smoother is a time based smoother ideal for gaming purposes.
            */
            class Smoother : public Base
            {
            public:
                PXC_CUID_OVERWRITE(PXC_UID('S', 'U', 'M', 'O'));

                /** @class Smoother1D
                Handles the smoothing of a stream of floats, using a specific smoothing algorithm
                */
                class Smoother1D : public Base
                {
                public:
                    PXC_CUID_OVERWRITE(PXC_UID('S', 'U', 'M', 1));

                    /**
                    @brief Add a new data sample to the smoothing algorithm
                    @param[in] value the latest data sample
                    @return smoothed value in float format
                    */
                    virtual float PXCAPI SmoothValue(float value) = 0;
                    /**
                    @brief Reset smoother algorithm data
                    */
                    virtual void PXCAPI Reset() = 0;
                };

                /** @class Smoother2D
                Handles the smoothing of a stream of 2D points, using a specific smoothing algorithm
                */
                class Smoother2D : public Base
                {
                public:
                    PXC_CUID_OVERWRITE(PXC_UID('S', 'U', 'M', 2));

                    /**
                    @brief Add a new data sample to the smoothing algorithm
                    @param[in] value the latest data sample
                    @return smoothed value in PointF32 format
                    */
                    virtual PointF32 PXCAPI SmoothValue(const PointF32 & value) = 0;
                    /**
                    @brief Reset smoother algorithm data
                    */
                    virtual void PXCAPI Reset() = 0;
                };

                /** @class Smoother3D
                Handles the smoothing of a stream of 3D points, using a specific smoothing algorithm
                */
                class Smoother3D : public Base
                {
                public:
                    /* Constants */
                    PXC_CUID_OVERWRITE(PXC_UID('S', 'U', 'M', 3));

                    /**
                    @brief Add a new data sample to the smoothing algorithm
                    @param[in] value the latest data sample
                    @return smoothed value in Point3DF32 format
                    */
                    virtual Point3DF32 PXCAPI SmoothValue(const Point3DF32 & value) = 0;
                    /**
                    @brief Reset smoother algorithm data
                    */
                    virtual void PXCAPI Reset() = 0;
                };

                /** @brief Create Stabilizer smoother instance for single floats
                The stabilizer keeps the smoothed data point stable as long as it has not moved more than a given threshold
                @param[in] stabilizeStrength The stabilizer smoother strength, default value is 0.5f
                @param[in] stabilizeRadius The stabilizer smoother radius in correlation to the input unit value
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother1D*    PXCAPI Create1DStabilizer(float stabilizeStrength, float stabilizeRadius) = 0;
                __inline Smoother1D* Create1DStabilizer(float stabilizeRadius) { return Create1DStabilizer(0.5f, stabilizeRadius); }

                /** @brief Create the Weighted algorithm for single floats
                The Weighted algorithm applies a (possibly) different weight to each of the previous data samples
                If the weights vector is not assigned (NULL) all the weights will be equal (1/numWeights)
                @param[in] numWeights The Weighted smoother number of weights
                @param[in] weights The Weighted smoother weight values
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother1D*    PXCAPI Create1DWeighted(int32_t numWeights, const float* weights) = 0;
                __inline Smoother1D* Create1DWeighted(int32_t numWeights) { return Create1DWeighted(numWeights, 0); }

                /** @brief Create the Quadratic algorithm for single floats
                @param[in] smoothStrength The Quadratic smoother smooth strength, default value is 0.5f
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother1D*    PXCAPI Create1DQuadratic(float smoothStrength) = 0;
                __inline Smoother1D* Create1DQuadratic(void) { return Create1DQuadratic(0.5f); }

                /** @brief Create the Spring algorithm for single floats
                @param[in] smoothStrength The Spring smoother smooth strength, default value is 0.5f
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother1D*    PXCAPI Create1DSpring(float smoothStrength) = 0;
                __inline Smoother1D* Create1DSpring(void) { return Create1DSpring(0.5f); }

                /** @brief Create Stabilizer smoother instance for 2-dimensional points
                The stabilizer keeps the smoothed data point stable as long as it has not moved more than a given threshold
                @param[in] stabilizeStrength The stabilizer smoother strength, default value is 0.5f
                @param[in] stabilizeRadius The stabilizer smoother radius in correlation to the input unit value
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother2D*    PXCAPI Create2DStabilizer(float stabilizeStrength, float stabilizeRadius) = 0;
                __inline Smoother2D* Create2DStabilizer(float stabilizeRadius) { return Create2DStabilizer(0.5f, stabilizeRadius); }

                /** @brief Create the Weighted algorithm for 2-dimensional points
                The Weighted algorithm applies a (possibly) different weight to each of the previous data samples
                If the weights vector is not assigned (NULL) all the weights will be equal (1/numWeights)
                @param[in] numWeights The Weighted smoother number of weights
                @param[in] weights The Weighted smoother weight values
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother2D*    PXCAPI Create2DWeighted(int32_t numWeights, const float* weights) = 0;
                __inline Smoother2D* Create2DWeighted(int32_t numWeights) { return Create2DWeighted(numWeights, 0); }

                /** @brief Create the Quadratic algorithm for 2-dimensional points
                @param[in] smoothStrength The Quadratic smoother smooth strength, default value is 0.5f
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother2D*    PXCAPI Create2DQuadratic(float smoothStrength) = 0;
                __inline Smoother2D* Create2DQuadratic(void) { return Create2DQuadratic(0.5f); }

                /** @brief Create the Spring algorithm for 2-dimensional points
                @param[in] smoothStrength The Spring smoother smooth strength, default value is 0.5f
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother2D*    PXCAPI Create2DSpring(float smoothStrength) = 0;
                __inline Smoother2D* Create2DSpring(void) { return Create2DSpring(0.5f); }

                /** @brief Create Stabilizer smoother instance for 3-dimensional points
                The stabilizer keeps the smoothed data point stable as long as it has not moved more than a given threshold
                @param[in] stabilizeStrength The stabilizer smoother strength, default value is 0.5f
                @param[in] stabilizeRadius The stabilizer smoother radius in correlation to the input unit value
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother3D*    PXCAPI Create3DStabilizer(float stabilizeStrength, float stabilizeRadius) = 0;
                __inline Smoother3D* Create3DStabilizer(float stabilizeRadius) { return Create3DStabilizer(0.5f, stabilizeRadius); }

                /** @brief Create the Weighted algorithm for 3-dimensional points
                The Weighted algorithm applies a (possibly) different weight to each of the previous data samples
                If the weights vector is not assigned (NULL) all the weights will be equal (1/numWeights)
                @param[in] numWeights The Weighted smoother number of weights
                @param[in] weights The Weighted smoother weight values
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother3D*    PXCAPI Create3DWeighted(int32_t numWeights, const float* weights) = 0;
                __inline Smoother3D* Create3DWeighted(int32_t numWeights) { return Create3DWeighted(numWeights, 0); }

                /** @brief Create the Quadratic algorithm for 3-dimensional points
                @param[in] smoothStrength The Quadratic smoother smooth strength, default value is 0.5f
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother3D*    PXCAPI Create3DQuadratic(float smoothStrength) = 0;
                __inline Smoother3D* Create3DQuadratic(void) { return Create3DQuadratic(0.5f); }

                /** @brief Create the Spring algorithm for 3-dimensional points
                @param[in] smoothStrength The Spring smoother smooth strength, default value is 0.5f
                @return a pointer to the created Smoother, or NULL in case of illegal arguments
                */
                virtual Smoother3D*    PXCAPI Create3DSpring(float smoothStrength) = 0;
                __inline Smoother3D* Create3DSpring(void) { return Create3DSpring(0.5f); }

				/**
				@brief    Create an instance of the Smoother interface.
				@return The Smoother instance.
				*/
				__inline static Smoother* CreateInstance(Session* session) {
					Smoother *smoother = 0;
					session->CreateImpl<Smoother>(&smoother);
					return smoother;
				}
            };

            typedef Smoother::Smoother1D Smoother1D;
            typedef Smoother::Smoother2D Smoother2D;
            typedef Smoother::Smoother3D Smoother3D;
        }
    }
}
