/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcmetadata.h
    Defines the PXCMetadata interface, which is used for managing
    metadata storage.
 */
#pragma once
#include "RealSense/Base.h"

namespace Intel {
    namespace RealSense {

        /**
        This interface manages metadata storage.  The PXCSession, PXCImage
        and PXCAudio implementations expose the PXCMetadata interface.
        */
        class Metadata :public Base {
        public:
            PXC_CUID_OVERWRITE(0x62398423);

            /**
            @brief The function returns a unique identifier for the meta data storage.
            @return the unique identifier.
            */
            virtual int32_t PXCAPI QueryUID(void) = 0;

            /**
            @brief The function retrieves the identifiers of all available meta data.
            @param[in] idx          The zero-based index to retrieve all identifiers.
            @return the metadata identifier, or zero if not available.
            */
            virtual int32_t PXCAPI QueryMetadata(int32_t idx) = 0;

            /**
            @brief The function detaches the specified metadata.
            @param[in] id           The metadata identifier.
            @return PXC_STATUS_NO_ERROR                Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE        The metadata is not found.
            */
            virtual Status PXCAPI DetachMetadata(int32_t id) = 0;

            /**
            @brief The function attaches the specified metadata.
            @param[in] id           The metadata identifier.
            @param[in] buffer       The metadata buffer.
            @param[in] size         The metadata buffer size, in bytes.
            @return PXC_STATUS_NO_ERROR                Successful execution.
            */
            virtual Status PXCAPI AttachBuffer(int32_t id, uint8_t *buffer, int32_t size) = 0;

            /**
            @brief The function returns the specified metadata buffer size.
            @param[in] id           The metadata identifier.
            @return the metadata buffer size, or zero if the metadata is not available.
            */
            virtual int32_t PXCAPI QueryBufferSize(int32_t id) = 0;

            /**
            @brief The function retrieves the specified metadata.
            @param[in] id           The metadata identifier.
            @param[in] buffer       The buffer pointer to retrieve the metadata.
            @param[in] size         The buffer size in bytes.
            @return PXC_STATUS_NO_ERROR         Successful execution.
            */
            virtual Status PXCAPI QueryBuffer(int32_t id, uint8_t *buffer, int32_t size) = 0;

            /**
            @brief The function attaches an instance of a serializeable interface to be metadata storage.
            @param[in] id           The metadata identifier.
            @param[in] instance     The serializable instance.
            @return PXC_STATUS_NO_ERROR         Successful execution.
            */
            virtual Status PXCAPI AttachSerializable(int32_t id, Base *instance) = 0;

            /**
            @brief The function creates an instance of a serializeable interface from the metadata storage.
            @param[in] id           The metadata identifier.
            @param[in] cuid         The interface identifier.
            @param[out] instance    The serializable instance, to be returned.
            @return PXC_STATUS_NO_ERROR         Successful execution.
            */
            virtual Status PXCAPI CreateSerializable(int32_t id, int32_t cuid, void **instance) = 0;

            /**
            @brief The function creates an instance of a serializeable interface from the metadata storage.
            @param[in] id           The metadata identifier.
            @param[out] instance    The serializable instance, to be returned.
            @return PXC_STATUS_NO_ERROR         Successful execution.
            */
            template <class T> Status __inline CreateSerializable(int32_t id, T **instance) {
                return CreateSerializable(id, T::CUID, (void**)instance);
            }
        };
    }
}
