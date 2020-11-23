/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcimage.h
Defines the PXCImage interface, which manages image buffer access.
*/
#pragma once
#include "RealSense/Base.h"
#include "RealSense/Reference.h"
#include "RealSense/Metadata.h"
#pragma warning(push)
#pragma warning(disable:4201) /* nameless structs/unions */

namespace Intel {
    namespace RealSense {

        /**
        This class defines a standard interface for image buffer access.

        The interface extends PXCAddRef. Use QueryInstance<PXCAddRef>(), or the helper
        function AddRef() to access the PXCAddRef features.

        The interface extends PXCMetadata. Use QueryMetadata() to access
        the PXCMetadata features.
        */
        class Image :public Base {
        public:
            PXC_CUID_OVERWRITE(0x24740F76);
            PXC_DEFINE_CONST(NUM_OF_PLANES, 4);
            PXC_DEFINE_CONST(METADATA_DEVICE_ROTATION, 0x3904a1fc);
            PXC_DEFINE_CONST(METADATA_DEVICE_PROPERTIES, 0x61516733);
            PXC_DEFINE_CONST(METADATA_DEVICE_PROJECTION, 0x3546785a);

            /**
            @enum PixelFormat
            Describes the image sample pixel format
            */
            enum PixelFormat {
                PIXEL_FORMAT_ANY = 0,                    /* Unknown/undefined */

                // STREAM_TYPE_COLOR
                PIXEL_FORMAT_YUY2 = 0x00010000,         /* YUY2 image  */
                PIXEL_FORMAT_NV12 = 0x00010001,         /* NV12 image */
                PIXEL_FORMAT_BGRA = 0x00010002,         /* BGRA image */
                PIXEL_FORMAT_BGR  = 0x00010003,         /* BGR image */
                PIXEL_FORMAT_Y8   = 0x00010004,         /* 8-Bit Gray Image, or IR 8-bit */
                PIXEL_FORMAT_RGBA = 0x00010202,         /* RGBA image */
                PIXEL_FORMAT_RGB  = 0x00010203,         /* RGB image */
                /* deprecated */ PIXEL_FORMAT_RGB32 = PIXEL_FORMAT_BGRA,
                /* deprecated */ PIXEL_FORMAT_RGB24 = PIXEL_FORMAT_BGR,

                // STREAM_TYPE_DEPTH
                PIXEL_FORMAT_DEPTH = 0x00020000,        /* 16-bit unsigned integer with precision mm. */
                PIXEL_FORMAT_DEPTH_RAW,                 /* 16-bit unsigned integer with device specific precision (call device->QueryDepthUnit()) */
                PIXEL_FORMAT_DEPTH_F32,                 /* 32-bit float-point with precision mm. */
                PIXEL_FORMAT_DEPTH_CONFIDENCE = 0x40000004, /* Additional plane with 8-bits depth confidence (MSB) */

                // STREAM_TYPE_IR
                PIXEL_FORMAT_Y16 = 0x00040000,          /* 16-Bit Gray Image */
                PIXEL_FORMAT_Y8_IR_RELATIVE = 0x00080000    /* Relative IR Image */
            };

            /**
            @brief Convert pixel format to a string representation
            @param[in]  format        pixel format.
            @return string presentation.
            */
            static __inline const wchar_t *PixelFormatToString(PixelFormat format) {
                switch (format) {
				case PIXEL_FORMAT_BGRA:         return (const wchar_t*)L"BGRA";
				case PIXEL_FORMAT_BGR:          return (const wchar_t*)L"BGR";
				case PIXEL_FORMAT_RGBA:         return (const wchar_t*)L"RGBA";
				case PIXEL_FORMAT_RGB:          return (const wchar_t*)L"RGB";
                case PIXEL_FORMAT_YUY2:         return (const wchar_t*)L"YUY2";
                case PIXEL_FORMAT_NV12:         return (const wchar_t*)L"NV12";
                case PIXEL_FORMAT_Y8:           return (const wchar_t*)L"Y8";
                case PIXEL_FORMAT_Y8_IR_RELATIVE:  return (const wchar_t*)L"Y8_REL";
                case PIXEL_FORMAT_Y16:          return (const wchar_t*)L"Y16";
                case PIXEL_FORMAT_DEPTH:        return (const wchar_t*)L"DEPTH";
                case PIXEL_FORMAT_DEPTH_F32:    return (const wchar_t*)L"DEPTH(FLOAT)";
                case PIXEL_FORMAT_DEPTH_RAW:    return (const wchar_t*)L"DEPTH(NATIVE)";
                case PIXEL_FORMAT_DEPTH_CONFIDENCE: return (const wchar_t*)L"DEPTH(CONF)";
                }
                return (const wchar_t*)L"Unknown";
            }

            /**
            @struct ImageInfo
            Describes the image sample detailed information.
            */
            struct ImageInfo {
                int32_t      width;              /* width of the image in pixels */
                int32_t      height;             /* height of the image in pixels */
                PixelFormat  format;             /* image pixel format */
                int32_t      reserved;
            };

            /**
            @struct ImageData
            Describes the image storage details.
            */
            struct ImageData {
                PixelFormat     format;                     /* image pixel format */
                int32_t         reserved[3];
                int32_t         pitches[NUM_OF_PLANES];     /* image pitches */
                uint8_t*        planes[NUM_OF_PLANES];      /* image buffers */
            };

            /**
            @enum Access
            Describes the image access mode.
            */
            enum Access {
                ACCESS_READ = 1,                            /* read only access     */
                ACCESS_WRITE = 2,                           /* write only access    */
                ACCESS_READ_WRITE = ACCESS_READ | ACCESS_WRITE,   /* read write access    */
            };

            /**
            @enum Rotation
            Image rotation options.
            */
            enum Rotation {
                ROTATION_0_DEGREE   = 0x0,   /* 0 Degree rotation */
                ROTATION_90_DEGREE  = 90,    /* 90 degree clockwise rotation */
                ROTATION_180_DEGREE = 180,   /* 180 degree clockwise rotation */
                ROTATION_270_DEGREE = 270,   /* 270 degree clockwise rotation */
            };

            /**
            @enum Option
            Describes the image options.
            */
            enum Option {
                OPTION_ANY = 0,
            };

            /**
            @brief Return the image sample information.
            @return the image sample information in the ImageInfo structure.
            */
            virtual ImageInfo PXCAPI QueryInfo(void) = 0;


            virtual int64_t PXCAPI QueryTimeStamp(void) = 0;

            /**
            @brief Return the image stream type. The application should cast the
            returned type to PXCCapture::StreamType.
            @return the stream type.
            */
            virtual int32_t PXCAPI QueryStreamType(void) = 0;

            /**
            @brief Get the image option flags.
            @return the option flags.
            */
            virtual Option PXCAPI QueryOptions(void) = 0;

            /**
            @brief Set the sample time stamp.
            @param[in] ts        The time stamp value, in 100ns.
            */
            virtual void PXCAPI SetTimeStamp(int64_t ts) = 0;

            /**
            @brief Set the sample stream type.
            @param[in] streamType    The sample stream type.
            */
            virtual void PXCAPI SetStreamType(int32_t streamType) = 0;

            /**
            @brief Set the sample options. This function overrides any previously set options.
            @param[in] options      The image options.
            */
            virtual void PXCAPI SetOptions(Option options) = 0;

            /**
            @brief Copy image data from another image sample.
            @param[in] src_image        The image sample to copy data from.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI CopyImage(Image *src_image) = 0;

            /**
            @brief Copy image data to the specified external buffer.
            @param[in] data             The ImageData structure that describes the image buffer.
            @param[in] flags            Reserved.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI ExportData(ImageData *data, int32_t flags = 0) = 0;

            /**
            @brief Copy image data from the specified external buffer.
            @param[in] data             The ImageData structure that describes the image buffer.
            @param[in] flags            Reserved.
            @return PXC_STATUS_NO_ERROR     Successful execution.
            */
            virtual Status PXCAPI ImportData(ImageData *data, int32_t flags = 0) = 0;

            /**
            @brief Lock to access the internal storage of a specified format. The function will perform format conversion if unmatched.
            @param[in] access           The access mode.
            @param[in] format           The requested smaple format.
            @param[in] options          The option flags.
            @param[out] data            The sample data storage, to be returned.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual Status PXCAPI AcquireAccess(Access access, PixelFormat format, Option options, ImageData *data) = 0;
            __inline Status AcquireAccess(Access access, PixelFormat format, Rotation rotation, Option options, ImageData *data) {
                return AcquireAccess(access, format, (Option)(rotation | options), data);
            }

            /**
            @brief Lock to access the internal storage of a specified format. The function will perform format conversion if unmatched.
            @param[in] access           The access mode.
            @param[in] format           The requested smaple format.
            @param[out] data            The sample data storage, to be returned.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            __inline Status AcquireAccess(Access access, PixelFormat format, ImageData *data) {
                return AcquireAccess(access, format, OPTION_ANY, data);
            }

            /**
            @brief Lock to access the internal storage of a specified format.
            @param[in] access           The access mode.
            @param[out] data            The sample data storage, to be returned.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            __inline Status AcquireAccess(Access access, ImageData *data) {
                return AcquireAccess(access, PIXEL_FORMAT_ANY, OPTION_ANY, data);
            }

            /**
            @brief Unlock the previously acquired buffer.
            @param[in] data             The sample data storage previously acquired.
            @return PXC_STATUS_NO_ERROR    Successful execution.
            */
            virtual Status   PXCAPI  ReleaseAccess(ImageData *data) = 0;

            /**
            @brief Increase a reference count of the sample.
            */
            __inline void AddRef(void) {
                QueryInstance<Reference>()->AddRef();
            }

            /**
            @brief Query rotation data.
            */
            __inline Rotation QueryRotation(void) {
                Rotation rotation = ROTATION_0_DEGREE;
                QueryInstance<Metadata>()->QueryBuffer(METADATA_DEVICE_ROTATION, (uint8_t*)&rotation, sizeof(rotation));
                return rotation;
            }

            /**
            @brief    A helper function to access PXCMetadata instance
            */
            __inline Metadata* QueryMetadata(void) {
                return QueryInstance<Metadata>();
            }

#ifdef _WIN32
			/**
			@brief Create an instance of the PXCImage interface with data. The application must
			maintain the life cycle of the image data for the PXCImage instance.
			@param[in]  session         The Session instance
			@param[in]  info            The format and resolution of the image.
			@param[in]  data            Optional image data.
			@return The PXCImage instance.
			*/
			template <typename T> __inline static Image* CreateInstance(T *session, ImageInfo *info, ImageData *data=0) {
				return session->CreateImage(info, data);
			}
#endif
		};

        typedef Image::PixelFormat PixelFormat;
        typedef Image::Option ImageOption;
        typedef Image::ImageInfo ImageInfo;
        typedef Image::ImageData ImageData;
        typedef Image::Rotation ImageRotation;
        typedef Image::Access ImageAccess;

        /**
        A helper function for bitwise OR of two flags.
        */
        static __inline ImageOption operator | (ImageOption a, ImageOption b) {
            return (ImageOption)((int)a | (int)b);
        }
    }
}

#pragma warning(pop)
