/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcsession.h
    Defines the PXCSession interface, which maintains the SDK context.  The
    application can query and create instances of I/O and algorithm module
    implementations.
*/
#pragma once
#include "RealSense/Base.h"
#include "pxcversion.h"
#include "RealSense/Image.h"
#include "RealSense/Metadata.h"

namespace Intel {
    namespace RealSense {
        class Session;
        class SenseManager;
        class CaptureManager;
        class Session;
        class PowerState;
        namespace Photography {
            class Photo;
        }
        namespace Speech {
            class Audio;
        }
    }
}

extern "C" class Intel::RealSense::Session* PXCAPI PXCSession_Create(void);
extern "C" class Intel::RealSense::Session* PXCAPI PXCSession_CreateFromPath(const wchar_t* specifiedRuntimePath);

namespace Intel {
    namespace RealSense {

        /**
        This class defines a standard interface for maintaining the SDK context.
        The application can query and create instances of I/O and algorithm module
        implementations.

        The interface extends PXCMetadata. Use QueryMetadata() to access
        the PXCMetadata features.
        */
        class Session :public Base {
        public:

            PXC_CUID_OVERWRITE(PXC_UID('S', 'E', 'S', ' '));

            /**
            Metadata types for feedback information attached to current session
            */
            PXC_DEFINE_UID(METADATA_FEEDBACK_SAMPLE_INFO, 'P', 'H', 'S', 'M');
            PXC_DEFINE_UID(METADATA_FEEDBACK_FRAMEWORK_INFO, 'P', 'H', 'F', 'M');

            /**
            @structure ImplVersion
            Describes the SDK runtime version.
            */
            struct ImplVersion {
                int16_t  major;    /* The major version number */
                int16_t  minor;    /* The minor version number */
            };

            /**
            @enum ImplGroup
            The SDK group I/O and algorithm modules into groups and subgroups.
            This is the enumerator for algorithm groups.
            */
            enum ImplGroup {
                IMPL_GROUP_ANY = 0,             /* Undefine group */
                IMPL_GROUP_OBJECT_RECOGNITION = 0x00000001,    /* Object recognition algorithms */
                IMPL_GROUP_SPEECH_RECOGNITION = 0x00000002,    /* Speech recognition algorithms */
                IMPL_GROUP_SENSOR = 0x00000004,    /* I/O modules */
                IMPL_GROUP_PHOTOGRAPHY = 0x00000008,    /* Photography/Videography algorithms */
                IMPL_GROUP_UTILITIES = 0x00000010,    /* Utility modules */
                IMPL_GROUP_CORE = 0x80000000,    /* Core SDK modules */
                IMPL_GROUP_USER = 0x40000000,    /* User defined algorithms */
            };

            /**
            @enum ImplSubgroup
            The SDK group I/O and algorithm modules into groups and subgroups.
            This is the enumerator for algorithm subgroups.
            */
            enum ImplSubgroup {
                IMPL_SUBGROUP_ANY = 0,            /* Undefined subgroup */

                // object recognition building blocks
                IMPL_SUBGROUP_FACE_ANALYSIS = 0x00000001,    /* face analysis subgroup */
                IMPL_SUBGROUP_GESTURE_RECOGNITION = 0x00000010,    /* gesture recognition subgroup */
                IMPL_SUBGROUP_SEGMENTATION = 0x00000020,    /* segmentation subgroup */
                IMPL_SUBGROUP_PULSE_ESTIMATION = 0x00000040,    /* pulse estimation subgroup */
                IMPL_SUBGROUP_EMOTION_RECOGNITION = 0x00000080,    /* emotion recognition subgroup */
                IMPL_SUBGROUP_OBJECT_TRACKING = 0x00000100,    /* object detection subgroup */
                IMPL_SUBGROUP_3DSEG = 0x00000200,    /* user segmentation subgroup */
                IMPL_SUBGROUP_3DSCAN = 0x00000400,    /* mesh capture subgroup */
                IMPL_SUBGROUP_SCENE_PERCEPTION = 0x00000800,    /* scene perception subgroup */

                // Photography building blocks
                IMPL_SUBGROUP_ENHANCED_PHOTOGRAPHY = 0x00001000,    /* enhanced photography subgroup */
                IMPL_SUBGROUP_ENHANCED_VIDEOGRAPHY = 0x00002000,    /* enhanced videography subgroup */

                // sensor building blocks
                IMPL_SUBGROUP_AUDIO_CAPTURE = 0x00000001,    /* audio capture subgroup */
                IMPL_SUBGROUP_VIDEO_CAPTURE = 0x00000002,    /* video capture subgroup */

                // speech recognition building blocks
                IMPL_SUBGROUP_SPEECH_RECOGNITION = 0x00000001,  /* speech recognition subgroup */
                IMPL_SUBGROUP_SPEECH_SYNTHESIS = 0x00000002,    /* speech synthesis subgroup */
            };

            /**
            @enum CoordinateSystem
            SDK supports several 3D coordinate systems for front and rear facing cameras.
            */
            enum CoordinateSystem {
                COORDINATE_SYSTEM_REAR_DEFAULT = 0x100,    /* Right-hand system: X right, Y up, Z to the user */
                COORDINATE_SYSTEM_REAR_OPENCV = 0x200,    /* Right-hand system: X right, Y down, Z to the world */
                COORDINATE_SYSTEM_FRONT_DEFAULT = 0x001,    /* Left-hand system: X left, Y up, Z to the user */
            };

            /**
            @structure ImplDesc
            The module descriptor lists details about the module implementation.
            */
            struct ImplDesc {
                ImplGroup           group;              /* implementation group */
                ImplSubgroup        subgroup;           /* implementation sub-group */
                int32_t              algorithm;          /* algorithm identifier */
                int32_t              iuid;               /* implementation unique id */
                ImplVersion         version;            /* implementation version */
                int32_t              reserved2;
                int32_t              merit;              /* implementation merit */
                int32_t              vendor;             /* vendor */
                int32_t              cuids[4];           /* interfaces supported by implementation */
                wchar_t             friendlyName[256];  /* friendly name */
                int32_t              reserved[12];
            };

            /**
            @brief Return the SDK version.
            @return the SDK version.
            */
            virtual ImplVersion PXCAPI QueryVersion(void) = 0;

            /**
            @brief Search a module implementation.
            @param[in]    templat           The template for the module search. Zero field values match any.
            @param[in]    idx               The zero-based index to retrieve multiple matches.
            @param[out]   desc              The matched module descriptor, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            virtual Status PXCAPI QueryImpl(ImplDesc *templat, int32_t idx, ImplDesc *desc) = 0;

            /**
            @brief Create an instance of the specified module.
            @param[in]    desc              Optional module descriptor.
            @param[in]    iuid              Optional module implementation identifier.
            @param[in]    cuid              Optional interface identifier.
            @param[out]   instance          The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            virtual Status PXCAPI CreateImpl(ImplDesc *desc, int32_t iuid, int32_t cuid, void **instance) = 0;

            /**
            @brief Create an instance of the specified module.
            @param[in]    desc              The module descriptor.
            @param[in]    cuid              Optional interface identifier.
            @param[out]   instance          The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            Status __inline CreateImpl(ImplDesc *desc, int32_t cuid, void **instance) {
                return CreateImpl(desc, 0, cuid, instance);
            }

            /**
            @brief Create an instance of the specified module.
            @param[in]   cuid               Optional interface identifier.
            @param[out]  instance           The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            Status __inline CreateImpl(int32_t cuid, void **instance) {
                return CreateImpl(0, cuid, instance);
            }

            /**
            @brief Create an instance of the specified module of the specified type.
            @param[in]   desc               The module descriptor.
            @param[in]   iuid               Optional module implementation identifier.
            @param[out]  instance           The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            template <class T> Status __inline CreateImpl(ImplDesc *desc, int32_t iuid, T **instance) {
                return CreateImpl(desc, iuid, T::CUID, (void**)instance);
            }

            /**
            @brief Create an instance of the specified module of the specified type.
            @param[in]   desc               The module descriptor.
            @param[out]  instance           The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            template <class T> Status __inline CreateImpl(ImplDesc *desc, T **instance) {
                return CreateImpl(desc, T::CUID, (void**)instance);
            }

            /**
            @brief Create an instance of the specified module of the specified type.
            @param[in]   iuid               Optional module implementation identifier.
            @param[out]  instance           The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            template <class T> Status __inline CreateImpl(int32_t iuid, T **instance) {
                return CreateImpl(0, iuid, T::CUID, (void**)instance);
            }

            /**
            @brief Create an instance of the specified module of the specified type.
            @param[out]  instance           The created instance, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    No matched module implementation.
            */
            template <class T> Status __inline CreateImpl(T **instance) {
                return CreateImpl(T::CUID, (void**)instance);
            }

            /**
            @brief Create an instance of the PXCSenseManager interface.
            @return The PXCSenseManager instance.
            */
            __inline SenseManager *CreateSenseManager(void) {
                SenseManager *sm = 0;
                CreateImpl(0, PXC_UID('P', 'P', 'U', 'T'), 0, (void**)&sm);
                return sm;
            }

            /**
            @brief Create an instance of the PXCCaptureManager interface.
            @return The PXCCaptureManager instance.
            */
            __inline CaptureManager* CreateCaptureManager(void) {
                CaptureManager *cm = 0;
                CreateImpl(0, PXC_UID('C', 'P', 'U', 'T'), 0, (void**)&cm);
                return cm;
            }

            /**
            @brief Create an instance of the power manager.
            @return The PXCPowerState instance.
            */
            __inline PowerState *CreatePowerManager(void) {
                PowerState *pm = 0;
                CreateImpl(0, PXC_UID('P', 'M', 'G', 'G'), PXC_UID('P', 'W', 'M', 'G'), (void**)&pm);
                return pm;
            }

            /**
            @brief Return the module descriptor
            @param[in]  module          The module instance
            @param[out] desc            The module descriptor, to be returned.
            @return PXC_STATUS_NO_ERROR         Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE Failed to identify the module instance.
            */
            virtual Status PXCAPI QueryModuleDesc(Base *module, ImplDesc *desc) = 0;

            /**
            @brief Create an instance of the PXCImage interface with data. The application must
            maintain the life cycle of the image data for the PXCImage instance.
            @param[in]  info            The format and resolution of the image.
            @param[in]  data            Optional image data.
            @return The PXCImage instance.
            */
            virtual Image* PXCAPI CreateImage(Image::ImageInfo *info, Image::ImageData *data) = 0;

            /**
            @brief Create an instance of the PXCImage interface.
            @param[in]  info            The format and resolution of the image.
            @return The PXCImage instance.
            */
            __inline Image* CreateImage(Image::ImageInfo *info) {
                return CreateImage(info, 0);
            }

            /**
            @brief Create an instance of the PXCPhoto interface.
            @return The PXCPhoto instance.
            */
            __inline Photography::Photo* CreatePhoto(void) {
                Photography::Photo *photo = 0;
                Status sts = CreateImpl(PXC_UID('G', 'D', 'V', '2'), (void**)&photo);
                return sts < Status::STATUS_NO_ERROR ? 0 : photo;
            }

            virtual /*PXC_DEPRECATED("Deprecated")*/ Speech::Audio* PXCAPI CreateAudio(void *info, void *data) = 0;
            __inline Speech::Audio* CreateAudio(void *info) {
                return CreateAudio(info, 0);
            }

            /**
            @brief Load the module from a file.
            @param[in]  moduleName      The module file name.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual Status PXCAPI LoadImplFromFile(wchar_t *moduleName) = 0;

            /**
            @brief Unload the specified module.
            @param[in]  moduleName      The module file name.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual Status PXCAPI UnloadImplFromFile(wchar_t *moduleName) = 0;

            /**
            @brief Set the camera coordinate system.
            @param[in]  cs          The coordinate system.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual Status PXCAPI SetCoordinateSystem(CoordinateSystem cs) = 0;

            /**
            @brief Return current camera coordinate system (bit-mask of coordinate systems for front and rear cameras)
            @param[in]  cs          The coordinate system.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual CoordinateSystem PXCAPI QueryCoordinateSystem() = 0;

            /**
            @brief Create an instance of the PXCSession interface.
            @return The PXCSession instance
            */
            __inline static Session* CreateInstance(const wchar_t* specifiedRuntimePath = nullptr) {
                return PXCSession_CreateFromPath(specifiedRuntimePath);
            }

            /**
            @brief    A helper function to access PXCMetadata instance
            */
            __inline Metadata* QueryMetadata(void) {
                return QueryInstance<Metadata>();
            }

        };

        typedef Session::ImplGroup ImplGroup;
        typedef Session::ImplSubgroup ImplSubgroup;
        typedef Session::ImplDesc ImplDesc;
        typedef Session::ImplVersion ImplVersion;
        typedef Session::CoordinateSystem CoordinateSystem;

        /**
        A helper function for bitwise OR of two flags.
        */
        __inline static ImplGroup operator|(ImplGroup a, ImplGroup b) {
            return (ImplGroup)((int)a | (int)b);
        }

        /**
        A helper function for bitwise OR of two flags.
        */
        __inline static ImplSubgroup operator|(ImplSubgroup a, ImplSubgroup b) {
            return (ImplSubgroup)((int)a | (int)b);
        }

        /**
        A helper function for bitwise OR of two flags.
        */
        __inline static CoordinateSystem operator|(CoordinateSystem a, CoordinateSystem b) {
            return (CoordinateSystem)((int)a | (int)b);
        }
    }
}
