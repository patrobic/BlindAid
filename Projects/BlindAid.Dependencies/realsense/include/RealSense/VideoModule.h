/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2013-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Sample.h"
#include "RealSense/Projection.h"

class PXCSyncPoint;

namespace Intel {
    namespace RealSense {

        class VideoModule : public Base {
        public:
            PXC_CUID_OVERWRITE(0x69D5B036);
            PXC_DEFINE_CONST(DEVCAP_LIMIT, 40);

            /**
            @structure DeviceCap
            Describes a pair value of device property and its value.
            Use the inline functions to access specific device properties.
            */
            struct DeviceCap {
                Property   label;       /* Property type */
                float      value;       /* Property value */
            };

            /**
            @structure StreamDesc
            Describes the streams requested by a module implementation.
            */
            struct StreamDesc {
                SizeI32    sizeMin;          /* minimum size */
                SizeI32    sizeMax;          /* maximum size */
                RangeF32   frameRate;        /* frame rate   */
                StreamOption options; /* stream options */
                int32_t    propertySet;
                int32_t    reserved[4];
            };

            /**
            @structure StreamDescSet
            A set of stream descriptors accessed by StreamType.
            */
            struct StreamDescSet {
                StreamDesc color;
                StreamDesc depth;
                StreamDesc ir;
                StreamDesc left;
                StreamDesc right;
                StreamDesc auxColor;
                StreamDesc reserved[Capture::STREAM_LIMIT - 6];

                /**
                @brief Access the stream descriptor by the stream type.
                @param[in] type        The stream type.
                @return The stream descriptor instance.
                */
                __inline StreamDesc& operator[](StreamType type) {
                    switch (type) {
                    case StreamType::STREAM_TYPE_COLOR: return color;
                    case StreamType::STREAM_TYPE_DEPTH: return depth;
                    case StreamType::STREAM_TYPE_IR:    return ir;
                    case StreamType::STREAM_TYPE_LEFT:  return left;
                    case StreamType::STREAM_TYPE_RIGHT: return right;
                    case StreamType::STREAM_TYPE_AUX_COLOR: return auxColor;
                    default:
                        for (int i = sizeof(reserved) / sizeof(reserved[0]) - 1, j = (1 << (Capture::STREAM_LIMIT - 1)); i >= 0; i--, j >>= 1)
                            if (type&j) return reserved[i];
                        return reserved[Capture::STREAM_LIMIT - 6];
                    }
                }
            };

            /**
            @structure DataDesc
            Data descriptor to describe the module input needs.
            */
            struct DataDesc {
                StreamDescSet  streams;                         /** requested stream characters */
                DeviceCap      devCaps[DEVCAP_LIMIT];           /** device properties to read */
                DeviceCap      devCapsOptional[DEVCAP_LIMIT];   /** device properties to read optionally */
                DeviceCap      devCapsSet[DEVCAP_LIMIT];        /** device properties to set */
                DeviceInfo     deviceInfo;             /** requested device info */
                bool32_t       receivePartialSample;
                int32_t        reserved[7];
            };

            /**
            @brief Return the available module input descriptors.
            @param[in]  pidx        The zero-based index used to retrieve all configurations.
            @param[out] inputs      The module input descriptor, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No specified input descriptor is not available.
            */
            virtual Status PXCAPI QueryCaptureProfile(int32_t pidx, DataDesc *inputs) = 0;

            /**
            @brief Return the active input descriptor that the module works on.
            @param[out] inputs      The module input descriptor, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            */
            __inline Status QueryCaptureProfile(DataDesc *inputs) {
                return QueryCaptureProfile(WORKING_PROFILE, inputs);
            }

            /**
            @brief Set the active input descriptor with the device information from the capture device.
            @param[in] inputs       The input descriptor with the device information.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual Status PXCAPI SetCaptureProfile(DataDesc *inputs) = 0;

            /**
            @brief Process sample synchronously (in caller thread).
            @param[in]  sample      The sample to process
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            __inline Status ProcessSample(Sample *sample) {
                return ProcessImageAsync(sample, 0);
            }

            virtual Status PXCAPI ProcessImageAsync(Sample *sample, PXCSyncPoint **reserved = 0) = 0;

            /**
            @brief Pass projection object for mappings between color and depth coordinate systems
            @param[in] projection       The projection object.
            */
            virtual void PXCAPI SetProjection(Projection* /*projection*/) { }

            /**
            @brief enables GPU processing controls
            @param[in] enable is a bool that enables a specific taskId on GPU.
            @param[in] taskId provides more fine-grained controls on which task would be enbled on GPU.
            default is enable = true and taskId = -1 (all tasks), meaning enable all tasks are on GPU. 
            */
            virtual void PXCAPI SetGPUExec(bool /*enable*/, int32_t /*taskId - reserved*/) {}
            
            __inline void PXCAPI SetGPUExec(bool enable) {
                int32_t taskId = -1;
                this->SetGPUExec(enable, taskId);
            }
            
            __inline void PXCAPI SetGPUExec() {
                bool enable = true;
                int32_t taskId = -1;
                this->SetGPUExec(enable, taskId);
            }
        };

        typedef VideoModule::DeviceCap DeviceCap;
        typedef VideoModule::StreamDesc StreamDesc;
        typedef VideoModule::StreamDescSet StreamDescSet;
        typedef VideoModule::DataDesc DataDesc;
    }
}
