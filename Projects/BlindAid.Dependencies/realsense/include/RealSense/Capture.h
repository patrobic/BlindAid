/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxccapture.h
    Defines the PXCCapture interface, which allows a program create and interact
    with video streams.
 */
#pragma once
#include "RealSense/Image.h"
#pragma warning(push)
#pragma warning(disable:4351) /* new behavior of array initialization */
#include <limits.h>
class PXCCaptureDeviceExt;
class PXCSyncPoint;

namespace Intel {
    namespace RealSense {
        struct Sample;
        class Projection;
        class DeviceExt;

		/**
		@enum PresetProfileSR300
		Describes the Presetting Profile.
		*/
		enum PresetProfileSR300
		{
			PRESET_PROFILE_SR300_SHORT_RANGE = 1, /*The short range preset profile*/
			PRESET_PROFILE_SR300_LONG_RANGE = 2, /*The long range preset profile*/
			PRESET_PROFILE_SR300_BACKGROUND_SEGMENTATION = 3, /*The background segmentation preset profile*/
			PRESET_PROFILE_SR300_GESTURE_RECOGNITION = 4, /*The gesture recognition preset profile*/
			PRESET_PROFILE_SR300_OBJECT_SCANNING = 5, /*The object scanning preset profile*/
			PRESET_PROFILE_SR300_FACE_ANALYTICS = 6, /*The face analytics preset profile*/
			PRESET_PROFILE_SR300_GR_CURSOR = 8, /*The GR analytics preset profile*/
			PRESET_PROFILE_SR300_CUSTOM = 9, /*The custom preset profile*/
			PRESET_PROFILE_SR300_DEFAULT = 10, /*The default preset profile*/
			PRESET_PROFILE_SR300_MID_RANGE = 11, /*The mid range preset profile*/
			PRESET_PROFILE_SR300_IR_ONLY = 12, /*The IR only preset profile*/
			PRESET_PROFILE_SR300_BACKGROUND_SEGMENTATION_HDR = 13, /*The backgroung segmentation preset profile for hdr*/
			PRESET_PROFILE_SR300_SHORT_RANGE_HDR = 14, /*The mid short range preset profile for hdr*/
			PRESET_PROFILE_SR300_MID_RANGE_HDR = 15, /*The mid long range preset profile for hdr*/
			PRESET_PROFILE_SR300_LONG_RANGE_HDR = 16 /*The long long range  preset profile for hdr*/
		};


        /**
        This interface provides member functions to create instances of and query stream capture devices.
        */
        class Capture :public Base {
        public:
            PXC_CUID_OVERWRITE(0x83F72A50);
            PXC_DEFINE_CONST(STREAM_LIMIT, 8);
            PXC_DEFINE_CONST(PROPERTY_VALUE_INVALID, SHRT_MAX);
            class Device;

            /**
            This is the PXCCapture callback interface.
            */
            class Handler {
            public:
                /**
                @brief  The Capture calls this function when a capture device is added or removed
                */
                virtual void PXCAPI OnDeviceListChanged() {}
            };

            /**
            @enum StreamType
            Bit-OR'ed values of stream types, physical or virtual streams.
            */
            enum StreamType {
                STREAM_TYPE_ANY = 0,            /* Unknown/undefined type */
                STREAM_TYPE_COLOR = 0x0001,     /* the color stream type  */
                STREAM_TYPE_DEPTH = 0x0002,     /* the depth stream type  */
                STREAM_TYPE_IR = 0x0004,        /* the infrared stream type */
                STREAM_TYPE_LEFT = 0x0008,      /* the stereoscopic left intensity image */
                STREAM_TYPE_RIGHT = 0x0010,     /* the stereoscopic right intensity image */
                STREAM_TYPE_AUX_COLOR = 0x0020, /* the auxiliary (second) color stream type */
            };

            /**
            @brief Get the stream type string representation
            @param[in] type        The stream type
            @return The corresponding string representation.
            **/
            __inline static const wchar_t *StreamTypeToString(StreamType type) {
                switch (type) {
                case STREAM_TYPE_COLOR: return L"Color";
                case STREAM_TYPE_DEPTH: return L"Depth";
                case STREAM_TYPE_IR:    return L"IR";
                case STREAM_TYPE_LEFT:  return L"Left";
                case STREAM_TYPE_RIGHT: return L"Right";
                case STREAM_TYPE_AUX_COLOR: return L"AuxColor";
                }
                return L"Unknown";
            }

            /**
            @brief Get the stream type from an index number
            @param[in] index        The stream index
            @return The corresponding stream type.
            **/
            __inline static StreamType StreamTypeFromIndex(int32_t index) {
                if (index < 0 || index >= STREAM_LIMIT) return STREAM_TYPE_ANY;
                return (StreamType)(1 << index);
            }

            /**
            @brief Get the stream index number
            @param[in] StreamType    The stream type
            @return The stream index number.
            **/
            __inline static int32_t StreamTypeToIndex(StreamType type) {
                int32_t s = 0;
                while (type > 1) type = (StreamType)(type >> 1), s++;
                return s;
            }

            /**
            @brief Get the available stream numbers.
            @return the number of streams.
            */
            __inline static int32_t QueryStreamNumFromScope(StreamType scope) {
                int32_t nstreams = 0;
                for (int32_t i = 0, j = 1; i < STREAM_LIMIT; i++, j <<= 1)
                    if (scope&j) nstreams++;
                return nstreams;
            }

            /**
            @enum DeviceModel
            Describes the device model
            */
            enum DeviceModel {
                DEVICE_MODEL_GENERIC = 0x00000000,    /* a generic device or unknown device */
                DEVICE_MODEL_F200 = 0x0020000E,    /* the Intel(R) RealSense(TM) 3D Camera, model F200 */
                DEVICE_MODEL_IVCAM = 0x0020000E,    /* deprecated: the Intel(R) RealSense(TM) 3D Camera, model F200 */
                DEVICE_MODEL_R200 = 0x0020000F,    /* the Intel(R) RealSense(TM) 3D Camera, model R200 */
                DEVICE_MODEL_DS4 = 0x0020000F,    /* deprecated: the Intel(R) RealSense(TM) 3D Camera, model R200 */
                DEVICE_MODEL_SR300 = 0x00200010,    /* The Intel(R) RealSense(TM) 3D Camera, model SR300 */
                DEVICE_MODEL_R200_ENHANCED = 0x0020001F,   /* The Intel(R) RealSense(TM) 3D Camera, model R200 and Platform Camera */
            };

            /**
            @enum ConnectionType
            Describes the Connection type of the device
            */
            enum ConnectionType {
                CONNECTION_TYPE_UNKNOWN = 0,                /* Any connection type */
                CONNECTION_TYPE_USB_INTEGRATED,              /* USB Integrated Camera */
                CONNECTION_TYPE_USB_PERIPHERAL                /* USB Peripheral Camera */
            };
            /**
            @brief Get the model string representation
            @param[in] model     The camera model
            @return The corresponding string representation.
            **/
            __inline static const wchar_t *DeviceModelToString(DeviceModel model) {
                switch (model) {
                case DEVICE_MODEL_GENERIC: return L"Generic";
                case DEVICE_MODEL_F200:    return L"F200";
                case DEVICE_MODEL_R200:    return L"R200";
                case DEVICE_MODEL_R200_ENHANCED: return L"R200 Enhanced";
                case DEVICE_MODEL_SR300:   return L"SR300";
                }
                return L"Unknown";
            }

            /**
            @enum DeviceOrientation
            Describes the device orientation
            */
            enum DeviceOrientation {
                DEVICE_ORIENTATION_ANY = 0x0,  /* Unknown orientation */
                DEVICE_ORIENTATION_USER_FACING = 0x1,  /* A user facing camera */
                DEVICE_ORIENTATION_FRONT_FACING = 0x1,  /* A front facing camera */
                DEVICE_ORIENTATION_WORLD_FACING = 0x2,  /* A world facing camera */
                DEVICE_ORIENTATION_REAR_FACING = 0x2,  /* A rear facing camera */
            };

            /**
            Describe device details.
            */
            struct DeviceInfo {
                wchar_t             name[224];      /* device name */
                wchar_t             serial[32];     /* serial number */
                wchar_t             did[256];       /* device identifier or the device symbolic name */
                int32_t             firmware[4];    /* firmware version: limit to four parts of numbers */
                PointF32            location;       /* device location in mm from the left bottom of the display panel. */
                DeviceModel         model;          /* device model */
                DeviceOrientation   orientation;    /* device orientation */
                StreamType          streams;        /* bit-OR'ed value of device stream types. */
                int32_t             didx;           /* device index */
                int32_t             duid;           /* device unique identifier within the SDK session */
                ImageRotation       rotation;       /* how the camera device is physically mounted */
                ConnectionType      connectionType; /* how the camera is connected to the platform */
                int32_t             reserved[11];

                /**
                @brief Get the available stream numbers.
                @return the number of streams.
                */
                __inline int32_t QueryStreamNum(void) {
                    return QueryStreamNumFromScope(streams);
                }
            };

            /**
            @brief    Return the number of devices.
            @return the number of available devices
            */
            virtual int32_t PXCAPI QueryDeviceNum(void) = 0;

            /**
            @brief Return the device information structure for a given device.
            @param[in]  didx                The zero-based device index.
            @param[out] dinfo               The pointer to the DeviceInfo structure, to be returned.
            @return PXC_STATUS_NO_ERROR            Successful execution.
            @return PXC_STATUS_ITEM_UNAVAILABLE    The specified index does not exist.
            */
            virtual Status PXCAPI QueryDeviceInfo(int32_t didx, DeviceInfo *dinfo) = 0;

            /**
            @brief    Activate the device and return the video device instance.
            @param[in] didx                        The zero-based device index
            @return The device instance.
            */
            virtual /*PXC_DEPRECATED("Deprecated. Use SampleReader or SenseManager::EnableStreams instead.")*/ Device* PXCAPI CreateDevice(int32_t didx) = 0;

            /**
            @brief    The function subscribes a handler for Capture callbacks. supports subscription of multiple callbacks.
            @param[in] Handler     handler instance for Capture callbacks.
            @return the status of the handler subscription.
            */
            virtual Status PXCAPI SubscribeToCaptureCallbacks(Handler * handler) = 0;

			/**
			@brief    The function subscribes a handler for Capture callbacks. supports subscription of multiple callbacks.
			@param[in] Handler     handler instance for Capture callbacks.
			@return the status of the handler subscription.
			*/
			__inline void AddListener(Handler * handler) {
				SubscribeToCaptureCallbacks(handler);
			}

            /**
            @brief    The function unsubscribes a handler from the Capture callbacks. the rest of the handlers will still be triggered.
            @param[in] handler     handler instance of Capture callbacks to unsubscirbe.
            @return the status of the handler unsubscription.
            */
            virtual Status PXCAPI UnsubscribeToCaptureCallbacks(Handler * handler) = 0;

			/**
			@brief    The function unsubscribes a handler from the Capture callbacks. the rest of the handlers will still be triggered.
			@param[in] handler     handler instance of Capture callbacks to unsubscirbe.
			@return the status of the handler unsubscription.
			*/
			__inline void RemoveListener(Handler * handler) {
				UnsubscribeToCaptureCallbacks(handler);
			}

			/**
            This is the video device interface.
            Use the member functions to interface with the video capture device.
            */
            class Device : public Base {
                friend class PXCCaptureDeviceExt;
                friend class DeviceExt;
            public:
                PXC_CUID_OVERWRITE(0x938401C4);

                /**
                @enum PowerLineFrequency
                Describes the power line compensation filter values.
                */
                enum PowerLineFrequency {
                    POWER_LINE_FREQUENC_INVALID = PROPERTY_VALUE_INVALID, /*Invalid value*/
                    POWER_LINE_FREQUENCY_DISABLED = 0,          /* Disabled power line frequency */
                    POWER_LINE_FREQUENCY_50HZ = 1,         /* 50HZ power line frequency */
                    POWER_LINE_FREQUENCY_60HZ = 2,         /* 60HZ power line frequency */
                };

                /**
                @enum MirrorMode
                Describes the mirroring options.
                */
                enum MirrorMode {
                    MIRROR_MODE_INVALID = PROPERTY_VALUE_INVALID, /*Invalid value*/
                    MIRROR_MODE_DISABLED = 0,          /* Disabled. The images are displayed as in a world facing camera.  */
                    MIRROR_MODE_HORIZONTAL = 1,          /* The images are horizontally mirrored as in a user facing camera. */
                };

                /**
                @enum IVCAMAccuracy
                Describes the IVCAM accuracy.
                */
                enum IVCAMAccuracy {
                    IVCAM_ACCURACY_INVALID = PROPERTY_VALUE_INVALID, /*Invalid value*/
                    IVCAM_ACCURACY_FINEST = 1,         /* The finest accuracy: 9 patterns */
                    IVCAM_ACCURACY_MEDIAN = 2,         /* The median accuracy: 8 patterns (default) */
                    IVCAM_ACCURACY_COARSE = 3,         /* The coarse accuracy: 7 patterns */
                };

                /**
                @enum Property
                Describes the device properties.
                Use the inline functions to access specific device properties.
                */
                enum Property {
                    /* Color Stream Properties */
                    PROPERTY_COLOR_EXPOSURE = 1,                /* int32_t       RW    The color stream exposure, in log base 2 seconds. */
                    PROPERTY_COLOR_BRIGHTNESS = 2,              /* int32_t       RW    The color stream brightness from  -10,000 (pure black) to 10,000 (pure white). */
                    PROPERTY_COLOR_CONTRAST = 3,                /* int32_t       RW    The color stream contrast, from 0 to 10,000. */
                    PROPERTY_COLOR_SATURATION = 4,              /* int32_t       RW    The color stream saturation, from 0 to 10,000. */
                    PROPERTY_COLOR_HUE = 5,                     /* int32_t       RW    The color stream hue, from -180,000 to 180,000 (representing -180 to 180 degrees.) */
                    PROPERTY_COLOR_GAMMA = 6,                   /* int32_t       RW    The color stream gamma, from 1 to 500. */
                    PROPERTY_COLOR_WHITE_BALANCE = 7,           /* int32_t       RW    The color stream balance, as a color temperature in degrees Kelvin. */
                    PROPERTY_COLOR_SHARPNESS = 8,               /* int32_t       RW    The color stream sharpness, from 0 to 100. */
                    PROPERTY_COLOR_BACK_LIGHT_COMPENSATION = 9, /* bool32_t      RW    The color stream back light compensation. */
                    PROPERTY_COLOR_GAIN = 10,                   /* int32_t       RW    The color stream gain adjustment, with negative values darker, positive values brighter, and zero as normal. */
                    PROPERTY_COLOR_POWER_LINE_FREQUENCY = 11,   /* int32_t       RW    The power line frequency in Hz. */
                    PROPERTY_COLOR_FOCAL_LENGTH_MM = 12,        /* float          R    The color-sensor focal length in mm. */
                    PROPERTY_COLOR_FIELD_OF_VIEW = 1000,        /* PXCPointF32    R    The color-sensor horizontal and vertical field of view parameters, in degrees. */
                    PROPERTY_COLOR_FOCAL_LENGTH = 1006,         /* PXCPointF32    R    The color-sensor focal length in pixels. The parameters vary with the resolution setting. */
                    PROPERTY_COLOR_PRINCIPAL_POINT = 1008,      /* PXCPointF32    R    The color-sensor principal point in pixels. The parameters vary with the resolution setting. */

                    // Depth Stream Properties
                    PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE = 201,  /* pxcU16         R    The special depth map value to indicate that the corresponding depth map pixel is of low-confidence. */
                    PROPERTY_DEPTH_CONFIDENCE_THRESHOLD = 202,  /* pxcI16        RW    The confidence threshold that is used to floor the depth map values. The range is from  0 to 15. */
                    PROPERTY_DEPTH_UNIT = 204,                  /* int32_t        R    The unit of depth values in micrometer if PIXEL_FORMAT_DEPTH_RAW */
                    PROPERTY_DEPTH_FOCAL_LENGTH_MM = 205,       /* float          R    The depth-sensor focal length in mm. */
                    PROPERTY_DEPTH_FIELD_OF_VIEW = 2000,        /* PXCPointF32    R    The depth-sensor horizontal and vertical field of view parameters, in degrees. */
                    PROPERTY_DEPTH_SENSOR_RANGE = 2002,         /* PXCRangeF32    R    The depth-sensor, sensing distance parameters, in millimeters. */
                    PROPERTY_DEPTH_FOCAL_LENGTH = 2006,         /* PXCPointF32    R    The depth-sensor focal length in pixels. The parameters vary with the resolution setting. */
                    PROPERTY_DEPTH_PRINCIPAL_POINT = 2008,      /* PXCPointF32    R    The depth-sensor principal point in pixels. The parameters vary with the resolution setting. */

                    // Device Properties
                    PROPERTY_DEVICE_ALLOW_PROFILE_CHANGE = 302, /* bool32_t      RW    If true, allow resolution change and throw PXC_STATUS_STREAM_CONFIG_CHANGED */
                    PROPERTY_DEVICE_MIRROR = 304,               /* MirrorMode    RW    The mirroring options. */

                    // Misc. Properties
                    PROPERTY_PROJECTION_SERIALIZABLE = 3003,    /* pxcU32         R    The meta data identifier of the Projection instance serialization data. */

                    // Device Specific Properties - IVCam
                    PROPERTY_IVCAM_LASER_POWER = 0x10000,       /* int32_t        RW    The laser power value from 0 (minimum) to 16 (maximum). */
                    PROPERTY_IVCAM_ACCURACY = 0x10001,          /* IVCAMAccuracy  RW    The IVCAM accuracy value. */
                    PROPERTY_IVCAM_FILTER_OPTION = 0x10003,     /* int32_t        RW    The filter option (smoothing aggressiveness) ranged from 0 (close range) to 7 (far range). */
                    PROPERTY_IVCAM_MOTION_RANGE_TRADE_OFF = 0x10004, /* int32_t   RW    This option specifies the motion and range trade off. The value ranged from 0 (short exposure, range, and better motion) to 100 (long exposure, range). */

                    // Device Specific Properties - DS
                    PROPERTY_DS_CROP = 0x20000,                 /* bool32_t       RW    Indicates whether to crop left and right images to match size of z image*/
                    PROPERTY_DS_EMITTER = 0x20001,              /* bool32_t       RW    Enable or disable DS emitter*/
                    PROPERTY_DS_DISPARITY_OUTPUT = 0x20003,     /* bool32_t       RW    Switches the range output mode between distance (Z) and disparity (inverse distance)*/
                    PROPERTY_DS_DISPARITY_MULTIPLIER = 0x20004, /* int32_t        RW    Sets the disparity scale factor used when in disparity output mode. Default value is 32.*/
                    PROPERTY_DS_DISPARITY_SHIFT = 0x20005,      /* int32_t        RW    Reduces both the minimum and maximum depth that can be computed.
                                                                                        Allows range to be computed for points in the near field which would otherwise be beyond the disparity search range.*/
                    PROPERTY_DS_MIN_MAX_Z = 0x20006,            /* PXCRangeF32    RW    The minimum z and maximum z in Z units that will be output   */
                    PROPERTY_DS_COLOR_RECTIFICATION = 0x20008,  /* bool32_t        R     if true rectification is enabled to DS color*/
                    PROPERTY_DS_DEPTH_RECTIFICATION = 0x20009,  /* bool32_t        R     if true rectification is enabled to DS depth*/
                    PROPERTY_DS_LEFTRIGHT_EXPOSURE = 0x2000A,   /* float          RW    The depth stream exposure, in log base 2 seconds. */
                    PROPERTY_DS_LEFTRIGHT_GAIN = 0x2000B,       /* int32_t        RW    The depth stream gain adjustment, with negative values darker, positive values brighter, and zero as normal. */
                    PROPERTY_DS_Z_TO_DISPARITY_CONSTANT = 0x2000C,      /* float   R     used to convert between Z distance (in mm) and disparity (in pixels)*/
                    PROPERTY_DS_ROBINS_MUNROE_MINUS_INCREMENT = 0x2000D, /* float  RW    Sets the value to subtract when estimating the median of the correlation surface.*/
                    PROPERTY_DS_ROBINS_MUNROE_PLUS_INCREMENT = 0x2000E, /* float   RW    Sets the value to add when estimating the median of the correlation surface. */
                    PROPERTY_DS_MEDIAN_THRESHOLD = 0x2000F,     /* float           RW    Sets the threshold for how much the winning score must beat the median to be judged a reliable depth measurement. */
                    PROPERTY_DS_SCORE_MIN_THRESHOLD = 0x20010,  /* float           RW    Sets the minimum correlation score that is considered acceptable. */
                    PROPERTY_DS_SCORE_MAX_THRESHOLD = 0x20011,  /* float           RW    Sets the maximum correlation score that is considered acceptable. */
                    PROPERTY_DS_TEXTURE_COUNT_THRESHOLD = 0x20012, /* float        RW    Set parameter for determining how much texture in the region is sufficient to be judged a reliable depth measurement. */
                    PROPERTY_DS_TEXTURE_DIFFERENCE_THRESHOLD = 0x20013, /* float   RW    Set parameter for determining whether the texture in the region is sufficient to justify a reliable depth measurement. */
                    PROPERTY_DS_SECOND_PEAK_THRESHOLD = 0x20014, /* float          RW    Sets the threshold for how much the minimum correlation score must differ from the next best score to be judged a reliable depth measurement. */
                    PROPERTY_DS_NEIGHBOR_THRESHOLD = 0x20015,   /* float           RW    Sets the threshold for how much at least one adjacent disparity score must differ from the minimum score to be judged a reliable depth measurement. */
                    PROPERTY_DS_LR_THRESHOLD = 0x20016,         /* float           RW    Determines the current threshold for determining whether the left-right match agrees with the right-left match. */

                    PROPERTY_SR300_COLOR_EXPOSURE_PRIORITY = 0x30000, 	  /* float        RW    Sets the Color Exposure Priority. */
                    PROPERTY_SR300_HDR_MODE = 0x30001,                 	  /* float        RW    Sets the HDR mode (0 = DISABLED). */
                    PROPERTY_SR300_PRESETTING_PROFILE = 0x30002,          /* float        RW    Sets the preset property set. */
					PROPERTY_SR300_EXTERNAL_TRIGGER_DELAY = 0x30003,      /* float        RW    Sets the External Trigger Delay. */
					PROPERTY_SR300_EXTERNAL_TRIGGER_TS_BASE = 0x30004,    /* float        RW    Sets the External Trigger Timestamp initial value. */
					PROPERTY_SR300_EXTERNAL_TRIGGER_CLOCK_UNIT = 0x30006, /* float        RW    Sets the External Trigger Clock Unit. */
                    // Customized properties
                    PROPERTY_CUSTOMIZED = 0x04000000,                        /* CUSTOMIZED properties */
                };

                /**
                @enum StreamOption
                Describes the steam options.
                */
                enum StreamOption
                {
                    STREAM_OPTION_ANY = 0,

                    // Optional options
                    STREAM_OPTION_OPTIONAL_MASK = 0x0000FFFF,       /* The option can be added to any profile, but not necessarily supported for any profile */
                    STREAM_OPTION_DEPTH_PRECALCULATE_UVMAP = 0x00000001,   /* A flag to ask the device to precalculate UVMap */
                    STREAM_OPTION_STRONG_STREAM_SYNC = 0x00000002,  /* A flag to ask the device to perform strong (HW-based) synchronization on the streams with this flag. */
					STREAM_OPTION_EXTERNAL_TRIGGER = 0x00000004,     /* A flag to ask the device to enable the external trigger for depth stream */

                    // Mandatory options
                    STREAM_OPTION_MANDATORY_MASK = 0xFFFF0000,      /* If the option is supported - the device sets this flag in the profile */
                    STREAM_OPTION_UNRECTIFIED = 0x00010000,         /* A mandatory flag to ask the device to stream unrectified images on the stream with this flag */
                    STREAM_OPTION_DEPTH_CONFIDENCE = 0x00020000     /* A mandatory flag to ask the device to attach confidence data to depth images (see PIXEL_FORMAT_DEPTH_CONFIDENCE) */
                };

                /**
                @brief Return the device information
                @param[in] pointer to the DeviceInfo structure, to be returned.
                */
                virtual void      PXCAPI QueryDeviceInfo(DeviceInfo *dinfo) = 0;

                /**
                @brief Return the instance of the Projection interface. Must be called after initialization.
                @return the Projection instance.
                */
                virtual Projection* PXCAPI CreateProjection(void) = 0;

                /**
                @structure StreamProfile
                Describes the video stream configuration parameters
                */
                struct StreamProfile {
                    ImageInfo       imageInfo;        /* resolution and color format */
                    RangeF32        frameRate;        /* frame rate range. Set max when configuring FPS */
                    StreamOption    options;          /* bit-mask of stream options */
                    int32_t         reserved[5];
                };

                /**
                @structure StreamProfileSet
                The set of StreamProfile that describes the configuration parameters of all streams.
                */
                struct StreamProfileSet {
                    StreamProfile color;
                    StreamProfile depth;
                    StreamProfile ir;
                    StreamProfile left;
                    StreamProfile right;
                    StreamProfile auxColor;
                    StreamProfile reserved[STREAM_LIMIT - 6];
 
                    /**
                    @brief Access the configuration parameters by the stream type.
                    @param[in] type        The stream type.
                    @return The StreamProfile instance.
                    */
                    __inline StreamProfile &operator[](StreamType type) {
                        if (type == STREAM_TYPE_COLOR) return color;
                        if (type == STREAM_TYPE_DEPTH) return depth;
                        if (type == STREAM_TYPE_IR)    return ir;
                        if (type == STREAM_TYPE_LEFT)  return left;
                        if (type == STREAM_TYPE_RIGHT) return right;
                        if (type == STREAM_TYPE_AUX_COLOR) return auxColor;
                        for (int i = sizeof(reserved) / sizeof(reserved[0]) - 1, j = (1 << (STREAM_LIMIT - 1)); i >= 0; i--, j >>= 1)
                            if (type&j) return reserved[i];
                        return reserved[sizeof(reserved) / sizeof(reserved[0]) - 1];
                    }
                };

                /**
                @struct PropertyInfo
                Describe the property value range and attributes.
                */
                struct PropertyInfo {
                    RangeF32 range;            /* The value range */
                    float    step;            /* The value step */
                    float    defaultValue;    /* Teh default value */
                    bool32_t automatic;        /* Boolean if this property supports automatic */
                    int32_t  reserved[11];
                };

                /**
                @brief Return the number of valid stream configurations for the streams of interest.
                @param[in] scope            The bit-OR'ed value of stream types of interest.
                @return the number of valid profile combinations.
                */
                virtual int32_t PXCAPI QueryStreamProfileSetNum(StreamType scope) = 0;

                /**
                @brief Return the unique configuration parameters for the selected video streams (types).
                @param[in] scope            The bit-OR'ed value of stream types of interest.
                @param[in] index            Zero-based index to retrieve all valid profiles.
                @param[out] profiles        The stream profile set.
                @return PXC_STATUS_NO_ERROR successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE index out of range.
                */
                virtual Status PXCAPI QueryStreamProfileSet(StreamType scope, int32_t index, StreamProfileSet *profiles) = 0;

                /**
                @brief Return the active stream configuration parameters (during streaming).
                @param[out] profiles        The stream profile set, to be returned.
                @return PXC_STATUS_NO_ERROR successful execution.
                */
                __inline Status QueryStreamProfileSet(StreamProfileSet *profiles) {
                    return QueryStreamProfileSet(StreamType::STREAM_TYPE_ANY, WORKING_PROFILE, profiles);
                }

                /**
                @brief Check if stream profile set is valid.
                @param[in] profiles         The stream profile set to check
                @return true     stream profile is valid.
                @return false    stream profile is invalid.
                */
                virtual bool32_t PXCAPI IsStreamProfileSetValid(StreamProfileSet *profiles) = 0;

                /**
                @brief Set the active profile for the all video streams. The application must configure all streams before streaming.
                @param[in] profiles            The stream profile set.
                @return PXC_STATUS_NO_ERROR successful execution.
                */
                virtual /*PXC_DEPRECATED("Deprecated. Use SampleReader or SenseManager::EnableStreams instead.")*/ Status PXCAPI SetStreamProfileSet(StreamProfileSet *profiles) = 0;

                /**
                @brief Read the selected streams asynchronously. The function returns immediately. The application must
                synchronize sync point to get the stream samples. The application can read more than a single stream using
                the scope parameter, provided that all streams have the same frame rate. Otherwise, the function will return error.
                @param[in] scope                The bit-OR'ed value of stream types of interest.
                @param[in] sample               The output sample.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_DEVICE_LOST          the device is disconnected.
                @return PXC_STATUS_PARAM_UNSUPPORTED    the streams are of different frame rates.
                */
                virtual /*Deprecated. Use SampleReader or SenseManager::EnableStreams instead.*/ Status PXCAPI ReadStreamsAsync(StreamType scope, Sample *sample, PXCSyncPoint **reserved) = 0;

                /**
                @brief Read the all configured streams asynchronously. The function returns immediately. The application must
                synchronize sync point to get the stream samples. The configured streams must have the same frame rate or
                the function will return error.
                @param[in] sample               The output sample.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_DEVICE_LOST          the device is disconnected.
                @return PXC_STATUS_PARAM_UNSUPPORTED    the streams are of different frame rates.
                */
                __inline /*PXC_DEPRECATED("Deprecated. Use SampleReader or SenseManager::EnableStreams instead.")*/ Status ReadStreamsAsync(Sample *sample, PXCSyncPoint **reserved) {
                    return ReadStreamsAsync(STREAM_TYPE_ANY, sample, reserved);
                }

                /**
                @brief Read the selected streams synchronously. The function blocks until all stream samples are ready.
                The application can read more than a single stream using the scope parameter, provided that all streams
                have the same frame rate. Otherwise, the function will return error.
                @param[in] scope                The bit-OR'ed value of stream types of interest.
                @param[in] sample               The output sample.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_DEVICE_LOST          the device is disconnected.
                @return PXC_STATUS_PARAM_UNSUPPORTED    the streams are of different frame rates.
                */
                __inline /*PXC_DEPRECATED("Deprecated. Use SampleReader or SenseManager::EnableStreams instead.")*/ Status PXCAPI ReadStreams(StreamType scope, Sample *sample) {
                    PXCSyncPoint *sp;
                    class SyncPoint : public Base {
                    public:
                        virtual Status PXCAPI Synchronize(int32_t timeout) = 0;
                    };
                    Status sts = ReadStreamsAsync(scope, sample, &sp);
                    if (sts < Status::STATUS_NO_ERROR) return sts;
                    sts = ((SyncPoint*)sp)->Synchronize(-1);
                    ((SyncPoint*)sp)->Release();
                    return sts;
                }

                __inline /*PXC_DEPRECATED("Deprecated. Use SampleReader or SenseManager::EnableStreams instead.")*/ Status PXCAPI ReadAnyStream(Sample *sample) {
                    return ReadStreamsAsync((StreamType)0x80000000, sample, nullptr);
                }

protected:
                /**
                @reserved
                Internal function. Do not use.
                */
                virtual Status PXCAPI QueryProperty(Property /*label*/, float * /*value*/) = 0;

                /**
                @reserved
                Internal function. Do not use.
                */
                virtual Status PXCAPI SetPropertyAuto(Property /*pty*/, bool32_t /*ifauto*/) = 0;

                /**
                @reserved
                Internal function. Do not use.
                */
                virtual Status PXCAPI SetProperty(Property /*pty*/, float /*value*/) = 0;

                /**
                @reserved
                Internal function. Do not use.
                */
                virtual Status PXCAPI QueryPropertyInfo(Property /*label*/, PropertyInfo* /*propertyInfo*/) = 0;

                /**
                @reserved
                Internal function. Do not use.
                */
                virtual Status PXCAPI QueryPropertyAuto(Property /*label*/, bool32_t* /*ifauto*/) = 0;

public:
                /**
                @brief Reset the device properties to their factory default values
                @param[in] streamType    The stream type to reset properties, or STREAM_TYPE_ANY for all streams.
                **/
                virtual void PXCAPI ResetProperties(StreamType streams) = 0;

                /**
                @brief Restore all device properties to what the application sets. Call this function upon receiving windows focus.
                **/
                virtual void PXCAPI RestorePropertiesUponFocus(void) = 0;

                /**
                @brief Get the color stream exposure value.
                @return The color stream exposure, in log base 2 seconds.
                */
                __inline int32_t    QueryColorExposure(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_EXPOSURE, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream exposure property information.
                @return The color stream exposure property information
                */
                __inline PropertyInfo    QueryColorExposureInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0, PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_EXPOSURE, &value);
                    return value;
                }

                /**
                @brief Set the color stream exposure value.
                @param[in] value    The color stream exposure value, in log base 2 seconds.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorExposure(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_EXPOSURE, (float)value);
                }

                /**
                @brief Set the color stream auto exposure value.
                @param[in] auto1    True to enable auto exposure.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorAutoExposure(bool32_t auto1) {
                    return SetPropertyAuto(PROPERTY_COLOR_EXPOSURE, auto1 ? 1 : 0);
                }

                /**
                @brief Query the color stream auto exposure value.
                @return exposure isAuto value
                */
                __inline bool QueryColorAutoExposure() {
                    int32_t auto1 = 0;
                    QueryPropertyAuto(PROPERTY_COLOR_EXPOSURE, &auto1);
                    return auto1 != 0;
                }

                /**
                @brief Get the color stream brightness value.
                @return The color stream brightness from  -10,000 (pure black) to 10,000 (pure white).
                */
                __inline int32_t    QueryColorBrightness(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_BRIGHTNESS, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream brightness property information.
                @return The color stream brightness property information
                */
                __inline PropertyInfo    QueryColorBrightnessInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_BRIGHTNESS, &value);
                    return value;
                }

                /**
                @brief Set the color stream brightness value.
                @param[in] value    The color stream brightness from  -10,000 (pure black) to 10,000 (pure white).
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorBrightness(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_BRIGHTNESS, (float)value);
                }

                /**
                @brief Get the color stream contrast value.
                @return The color stream contrast, from 0 to 10,000.
                */
                __inline int32_t    QueryColorContrast(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_CONTRAST, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream contrast property information.
                @return The color stream contrast property information
                */
                __inline PropertyInfo    QueryColorContrastInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_CONTRAST, &value);
                    return value;
                }


                /**
                @brief Set the color stream contrast value.
                @param[in] value    The color stream contrast, from 0 to 10,000.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorContrast(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_CONTRAST, (float)value);
                }

                /**
                @brief Get the color stream saturation value.
                @return The color stream saturation, from 0 to 10,000.
                */
                __inline int32_t    QueryColorSaturation(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_SATURATION, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream saturation property information.
                @return The color stream saturation property information
                */
                __inline PropertyInfo    QueryColorSaturationInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_SATURATION, &value);
                    return value;
                }

                /**
                @brief Set the color stream saturation value.
                @param[in] value    The color stream saturation, from 0 to 10,000.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorSaturation(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_SATURATION, (float)value);
                }

                /**
                @brief Get the color stream hue value.
                @return The color stream hue, from -180,000 to 180,000 (representing -180 to 180 degrees.)
                */
                __inline int32_t    QueryColorHue(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_HUE, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream Hue property information.
                @return The color stream Hue property information
                */
                __inline PropertyInfo    QueryColorHueInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_HUE, &value);
                    return value;
                }

                /**
                @brief Set the color stream hue value.
                @param[in] value    The color stream hue, from -180,000 to 180,000 (representing -180 to 180 degrees.)
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorHue(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_HUE, (float)value);
                }

                /**
                @brief Get the color stream gamma value.
                @return The color stream gamma, from 1 to 500.
                */
                __inline int32_t    QueryColorGamma(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_GAMMA, &value);
                    return (int32_t)value;
                }


                /**
                @brief Get the color stream gamma property information.
                @return The color stream gamma property information
                */
                __inline PropertyInfo    QueryColorGammaInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_GAMMA, &value);
                    return value;
                }

                /**
                @brief Set the color stream gamma value.
                @param[in] value    The color stream gamma, from 1 to 500.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorGamma(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_GAMMA, (float)value);
                }

                /**
                @brief Get the color stream white balance value.
                @return The color stream balance, as a color temperature in degrees Kelvin.
                */
                __inline int32_t    QueryColorWhiteBalance(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_WHITE_BALANCE, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream  white balance property information.
                @return The color stream  white balance property information
                */
                __inline PropertyInfo    QueryColorWhiteBalanceInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_WHITE_BALANCE, &value);
                    return value;
                }

                /**
                @brief Set the color stream white balance value.
                @param[in] value    The color stream balance, as a color temperature in degrees Kelvin.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorWhiteBalance(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_WHITE_BALANCE, (float)value);
                }

                /**
                @brief Set the color stream auto white balance mode.
                @param[in] auto1    The flag if the auto is enabled or not.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorAutoWhiteBalance(bool32_t auto1) {
                    return SetPropertyAuto(PROPERTY_COLOR_WHITE_BALANCE, auto1 ? 1 : 0);
                }



                /**
                @brief Get the color stream auto white balance mode.
                @return White Balance isAuto value.
                */
                __inline bool QueryColorAutoWhiteBalance() {
                    int32_t auto1 = 0;
                    QueryPropertyAuto(PROPERTY_COLOR_WHITE_BALANCE, &auto1);
                    return auto1 != 0;
                }

                /**
                @brief Get the color stream sharpness value.
                @return The color stream sharpness, from 0 to 100.
                */
                __inline int32_t    QueryColorSharpness(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_SHARPNESS, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream Sharpness property information.
                @return The color stream  Sharpness property information
                */
                __inline PropertyInfo    QueryColorSharpnessInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_SHARPNESS, &value);
                    return value;
                }

                /**
                @brief Set the color stream sharpness value.
                @param[in] value    The color stream sharpness, from 0 to 100.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorSharpness(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_SHARPNESS, (float)value);
                }

                /**
                @brief Get the color stream back light compensation status.
                @return The color stream back light compensation status from 0 to 4.
                */
                __inline int32_t QueryColorBackLightCompensation(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_BACK_LIGHT_COMPENSATION, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream back light compensation property information.
                @return The color stream  back light compensation property information
                */
                __inline PropertyInfo    QueryColorBackLightCompensationInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_BACK_LIGHT_COMPENSATION, &value);
                    return value;
                }

                /**
                @brief Set the color stream back light compensation status.
                @param[in] value    The color stream back light compensation from 0 to 4.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorBackLightCompensation(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_BACK_LIGHT_COMPENSATION, (float)value);
                }

                /**
                @brief Get the color stream gain value.
                @return The color stream gain adjustment, with negative values darker, positive values brighter, and zero as normal.
                */
                __inline int32_t    QueryColorGain(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_GAIN, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the color stream gain property information.
                @return The color stream  gain property information
                */
                __inline PropertyInfo    QueryColorGainInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_GAIN, &value);
                    return value;
                }

                /**
                @brief Set the color stream gain value.
                @param[in] value    The color stream gain adjustment, with negative values darker, positive values brighter, and zero as normal.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorGain(int32_t value) {
                    return SetProperty(PROPERTY_COLOR_GAIN, (float)value);
                }

                /**
                @brief Get the color stream power line frequency value.
                @return The power line frequency in Hz.
                */
                __inline PowerLineFrequency QueryColorPowerLineFrequency(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_POWER_LINE_FREQUENCY, &value);
                    return (PowerLineFrequency)(int32_t)value;
                }


                /**
                @brief Get the color stream power line frequency auto value.
                @param[out] value    The power line frequency auto mode.
                @return PowerLineFrequency isAuto value
                */
                __inline bool QueryColorAutoPowerLineFrequency() {
                    int32_t auto1 = 0;
                    QueryPropertyAuto(PROPERTY_COLOR_POWER_LINE_FREQUENCY, &auto1);
                    return auto1 != 0;
                }


                /**
                @brief Get the color stream power line frequency Property Info.
                @return The power line frequency default value.
                */
                __inline PowerLineFrequency QueryColorPowerLineFrequencyDefaultValue(void) {
                    PropertyInfo info = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_COLOR_POWER_LINE_FREQUENCY, &info);
                    return (PowerLineFrequency)(int32_t)info.defaultValue;
                }

                /**
                @brief Set the color stream power line frequency value.
                @param[in] value    The power line frequency in Hz.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorPowerLineFrequency(PowerLineFrequency value) {
                    return SetProperty(PROPERTY_COLOR_POWER_LINE_FREQUENCY, (float)value);
                }


                /**
                @brief Set the color stream auto power line frequency.
                @param[in] value    The power line frequency auto mode.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetColorAutoPowerLineFrequency(bool32_t auto1) {
                    return SetPropertyAuto(PROPERTY_COLOR_POWER_LINE_FREQUENCY, auto1);
                }

                /**
                @brief Get the color stream field of view.
                @return The color-sensor horizontal and vertical field of view parameters, in degrees.
                */
                __inline PointF32 QueryColorFieldOfView(void) {
                    PointF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_COLOR_FIELD_OF_VIEW, &value.x);
                    QueryProperty((Property)(PROPERTY_COLOR_FIELD_OF_VIEW + 1), &value.y);
                    return value;
                }

                /**
                @brief Get the color stream focal length.
                @return The color-sensor focal length in pixels. The parameters vary with the resolution setting.
                */
                __inline PointF32 QueryColorFocalLength(void) {
                    PointF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_COLOR_FOCAL_LENGTH, &value.x);
                    QueryProperty((Property)(PROPERTY_COLOR_FOCAL_LENGTH + 1), &value.y);
                    return value;
                }

                /**
                @brief Get the color stream focal length in mm.
                @return The color-sensor focal length in mm.
                */
                __inline float QueryColorFocalLengthMM(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_COLOR_FOCAL_LENGTH_MM, &value);
                    return value;
                }

                /**
                @brief Get the color stream principal point.
                @return The color-sensor principal point in pixels. The parameters vary with the resolution setting.
                */
                __inline PointF32 QueryColorPrincipalPoint(void) {
                    PointF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_COLOR_PRINCIPAL_POINT, &value.x);
                    QueryProperty((Property)(PROPERTY_COLOR_PRINCIPAL_POINT + 1), &value.y);
                    return value;
                }

                /**
                @brief Get the depth stream low confidence value.
                @return The special depth map value to indicate that the corresponding depth map pixel is of low-confidence.
                */
                __inline uint16_t QueryDepthLowConfidenceValue(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DEPTH_LOW_CONFIDENCE_VALUE, &value);
                    return (uint16_t)value;
                }

                /**
                @brief Get the depth stream confidence threshold.
                @return The confidence threshold that is used to floor the depth map values. The range is from 0 to 15.
                */
                __inline int16_t QueryDepthConfidenceThreshold(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DEPTH_CONFIDENCE_THRESHOLD, &value);
                    return (int16_t)value;
                }

                /**
                @brief Get the depth stream confidence threshold information.
                @return The property information for the confidence threshold that is used to floor the depth map values. The range is from 0 to 15.
                */
                __inline PropertyInfo QueryDepthConfidenceThresholdInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_DEPTH_CONFIDENCE_THRESHOLD, &value);
                    return value;
                }

                /**
                @brief Set the depth stream confidence threshold.
                @param[in] value    The confidence threshold that is used to floor the depth map values. The range is from 0 to 15.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDepthConfidenceThreshold(int16_t value) {
                    return SetProperty(PROPERTY_DEPTH_CONFIDENCE_THRESHOLD, (float)value);
                }

                /**
                @brief Get the depth stream unit value.
                @return The unit of depth values in micrometre.
                */
                __inline float QueryDepthUnit(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DEPTH_UNIT, &value);
                    return value;
                }

                /**
                @brief Set the depth stream unit value.
                @param[in] The unit of depth values in micrometre
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDepthUnit(float value) {
                    return SetProperty(PROPERTY_DEPTH_UNIT, value);
                }

                /**
                @brief Get the depth stream field of view.
                @return The depth-sensor horizontal and vertical field of view parameters, in degrees.
                */
                __inline PointF32 QueryDepthFieldOfView(void) {
                    PointF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_DEPTH_FIELD_OF_VIEW, &value.x);
                    QueryProperty((Property)(PROPERTY_DEPTH_FIELD_OF_VIEW + 1), &value.y);
                    return value;
                }

                /**
                @brief Get the depth stream sensor range.
                @return The depth-sensor, sensing distance parameters, in millimeters.
                */
                __inline RangeF32 QueryDepthSensorRange(void) {
                    RangeF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_DEPTH_SENSOR_RANGE, &value.min);
                    QueryProperty((Property)(PROPERTY_DEPTH_SENSOR_RANGE + 1), &value.max);
                    return value;
                }

                /**
                @brief Get the depth stream focal length.
                @return The depth-sensor focal length in pixels. The parameters vary with the resolution setting.
                */
                __inline PointF32 QueryDepthFocalLength(void) {
                    PointF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_DEPTH_FOCAL_LENGTH, &value.x);
                    QueryProperty((Property)(PROPERTY_DEPTH_FOCAL_LENGTH + 1), &value.y);
                    return value;
                }

                /**
                @brief Get the depth stream focal length in mm.
                @return The depth-sensor focal length in mm.
                */
                __inline float QueryDepthFocalLengthMM(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DEPTH_FOCAL_LENGTH_MM, &value);
                    return value;
                }

                /**
                @brief Get the depth stream principal point.
                @return The depth-sensor principal point in pixels. The parameters vary with the resolution setting.
                */
                __inline PointF32 QueryDepthPrincipalPoint(void) {
                    PointF32 value = { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_DEPTH_PRINCIPAL_POINT, &value.x);
                    QueryProperty((Property)(PROPERTY_DEPTH_PRINCIPAL_POINT + 1), &value.y);
                    return value;
                }

                /**
                @brief Get the device allow profile change status.
                @return If true, allow resolution change and throw PXC_STATUS_STREAM_CONFIG_CHANGED.
                */
                __inline bool QueryDeviceAllowProfileChange(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DEVICE_ALLOW_PROFILE_CHANGE, &value);
                    return value != 0;
                }



                /**
                @brief Set the device allow profile change status.
                @param[in] value    If true, allow resolution change and throw PXC_STATUS_STREAM_CONFIG_CHANGED.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDeviceAllowProfileChange(bool32_t value) {
                    return SetProperty(PROPERTY_DEVICE_ALLOW_PROFILE_CHANGE, (float)value);
                }

                /**
                @brief Get the mirror mode.
                @return The mirror mode
                */
                __inline MirrorMode QueryMirrorMode(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DEVICE_MIRROR, &value);
                    return (MirrorMode)(int32_t)value;
                }

                /**
                @brief Set the mirror mode.
                @param[in] value    The mirror mode
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetMirrorMode(MirrorMode value) {
                    if (value != MIRROR_MODE_DISABLED && value != MIRROR_MODE_HORIZONTAL)
                        return PXC_STATUS_DEVICE_FAILED;
                    return SetProperty(PROPERTY_DEVICE_MIRROR, (float)value);
                }

                /**
                @brief Get the IVCAM laser power.
                @return The laser power value from 0 (minimum) to 16 (maximum).
                */
                __inline int32_t QueryIVCAMLaserPower(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_IVCAM_LASER_POWER, &value);
                    return (int32_t)value;
                }


                /**
                @brief Get the IVCAM laser power property information.
                @return The laser power proeprty information.
                */
                __inline PropertyInfo QueryIVCAMLaserPowerInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_IVCAM_LASER_POWER, &value);
                    return value;
                }

                /**
                @brief Set the IVCAM laser power.
                @param[in] value    The laser power value from 0 (minimum) to 16 (maximum).
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetIVCAMLaserPower(int32_t value) {
                    return SetProperty(PROPERTY_IVCAM_LASER_POWER, (float)value);
                }

                /**
                @brief Get the IVCAM accuracy.
                @return The accuracy value
                */
                __inline IVCAMAccuracy QueryIVCAMAccuracy(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_IVCAM_ACCURACY, &value);
                    return (IVCAMAccuracy)(int32_t)value;
                }


                /**
                @brief Get the IVCAM accuracy property Information.
                @return The accuracy value property Information
                */
                __inline IVCAMAccuracy QueryIVCAMAccuracyDefaultValue(void) {
                    PropertyInfo info = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_IVCAM_ACCURACY, &info);
                    return (IVCAMAccuracy)(int32_t)info.defaultValue;
                }

                /**
                @brief Set the IVCAM accuracy.
                @param[in] value    The accuracy value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetIVCAMAccuracy(IVCAMAccuracy value) {
                    return SetProperty(PROPERTY_IVCAM_ACCURACY, (float)value);
                }

                /**
                @brief Get the IVCAM filter option (smoothing aggressiveness) ranged from 0 (close range) to 7 (far range).
                @return The filter option value.
                */
                __inline int32_t QueryIVCAMFilterOption(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_IVCAM_FILTER_OPTION, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get the IVCAM Filter Option property information.
                @return The IVCAM Filter Option property information.
                */
                __inline PropertyInfo QueryIVCAMFilterOptionInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_IVCAM_FILTER_OPTION, &value);
                    return value;
                }

                /**
                @brief Set the IVCAM filter option (smoothing aggressiveness) ranged from 0 (close range) to 7 (far range).
                @param[in] value    The filter option value
                @return PXC_STATUS_NO_ERROR            successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE the device property is not supported.
                */
                __inline Status SetIVCAMFilterOption(int32_t value) {
                    Status sts = SetProperty(PROPERTY_IVCAM_FILTER_OPTION, (float)value);
                    return sts;
                }

                /**
                @brief Get the IVCAM motion range trade off option, ranged from 0 (short range, better motion) to 100 (far range, long exposure).
                @return The motion range trade option.
                */
                __inline int32_t QueryIVCAMMotionRangeTradeOff(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_IVCAM_MOTION_RANGE_TRADE_OFF, &value);
                    return (int32_t)value;
                }


                /**
                @brief Get the IVCAM Filter Option property information.
                @return The IVCAM Filter Option property information.
                */
                __inline PropertyInfo QueryIVCAMMotionRangeTradeOffInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_IVCAM_MOTION_RANGE_TRADE_OFF, &value);
                    return value;
                }

                /**
                @brief Set the IVCAM motion range trade off option, ranged from 0 (short range, better motion) to 100 (far range, long exposure).
                @param[in] value        The motion range trade option.
                @return PXC_STATUS_NO_ERROR            successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE the device property is not supported.
                */
                __inline Status SetIVCAMMotionRangeTradeOff(int32_t value) {
                    Status sts = SetProperty(PROPERTY_IVCAM_MOTION_RANGE_TRADE_OFF, (float)value);
                    return sts;
                }

                /**
                @brief Get the DS Left Right Cropping status.
                @return true if enabled
                */
                __inline bool QueryDSLeftRightCropping(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_CROP, &value);
                    return value != 0;
                }

                /**
                @brief enable\disable the DS Left Right Cropping.
                @param[in] value    The setting value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSLeftRightCropping(bool32_t value) {
                    return SetProperty(PROPERTY_DS_CROP, (float)value);
                }

                /**
                @brief Get the DS emitter status
                @return true if enabled
                */
                __inline bool QueryDSEmitterEnabled(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_EMITTER, &value);
                    return value != 0;
                }

                /**
                @brief enable\disable the DS Emitter
                @param[in] value    The setting value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSEnableEmitter(bool32_t value) {
                    return SetProperty(PROPERTY_DS_EMITTER, (float)value);
                }

                /**
                @brief Get the DS Disparity (inverse distance) Output status
                @return true if enabled
                */
                __inline bool QueryDSDisparityOutputEnabled(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_DISPARITY_OUTPUT, &value);
                    return value != 0;
                }

                /**
                @brief enable\disable DS Disparity Output, Switches the range output mode between distance (Z) and disparity (inverse distance)
                @param[in] value    The setting value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSEnableDisparityOutput(bool32_t value) {
                    return SetProperty(PROPERTY_DS_DISPARITY_OUTPUT, (float)value);
                }

                /**
                @brief Gets the disparity scale factor used when in disparity output mode. Default value is 32.
                @return the disparity scale factor.
                */
                __inline int32_t QueryDSDisparityMultiplier(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_DISPARITY_MULTIPLIER, &value);
                    return (int32_t)value;
                }

                /**
                @brief Sets the disparity scale factor used when in disparity output mode.
                @param[in] value  the disparity scale factor.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSDisparityMultiplier(int32_t value) {
                    return SetProperty(PROPERTY_DS_DISPARITY_MULTIPLIER, (float)value);
                }

                /**
                @brief Gets the disparity shift used when in disparity output mode.
                @return the disparity shift.
                */
                __inline int32_t QueryDSDisparityShift(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_DISPARITY_SHIFT, &value);
                    return (int32_t)value;
                }

                /**
                @brief Sets the disparity shift used when in disparity output mode.
                @param[in] value  the disparity shift.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSDisparityShift(int32_t value) {
                    return SetProperty(PROPERTY_DS_DISPARITY_SHIFT, (float)value);
                }

                /**
                @brief When in a rectified mode, ZToDisparityConstant = baseline * focalLengthX,
                where baseline is measured in mm, and focalLengthX is measured in pixels.
                Used to convert between Z distance (in mm) and disparity (in pixels), where ZToDisparityConstant / Z = disparity.
                @return the z to disparity constant
                */
                __inline float QueryDSZToDisparityConstant(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_Z_TO_DISPARITY_CONSTANT, &value);
                    return value;
                }

                /**
                @brief Get the current min & max limits of the z.
                @return min, max z.
                */
                __inline RangeF32 QueryDSMinMaxZ(void) {
                    RangeF32 value = { PROPERTY_VALUE_INVALID, PROPERTY_VALUE_INVALID };
                    QueryProperty(PROPERTY_DS_MIN_MAX_Z, &value.min);
                    QueryProperty((Property)(PROPERTY_DS_MIN_MAX_Z + 1), &value.max);
                    return value;
                }

                /**
                @brief Set the min & max limits of the z units.
                @param[in] value    The setting value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSMinMaxZ(RangeF32 value) {
                    Status sts = SetProperty(PROPERTY_DS_MIN_MAX_Z, (float)value.min);
                    if (sts == PXC_STATUS_NO_ERROR)
                        sts = SetProperty((Property)(PROPERTY_DS_MIN_MAX_Z + 1), (float)value.max);
                    return sts;
                }

                /**
                @brief Get the color rectification status
                @return true if enabled
                */
                __inline bool QueryDSColorRectificationEnabled(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_COLOR_RECTIFICATION, &value);
                    return value != 0;
                }

                /**
                @brief Get the depth rectification status
                @return true if enabled
                */
                __inline bool QueryDSDepthRectificationEnabled(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_DEPTH_RECTIFICATION, &value);
                    return value != 0;
                }

                /**
                @brief Get DS left & right streams exposure value.
                @return DS left & right streams exposure, in milliseconds.
                */
                __inline float    QueryDSLeftRightExposure(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_LEFTRIGHT_EXPOSURE, &value);
                    return value;
                }

                /**
                @brief Get DS left & right streams exposure property information.
                @return The DS left & right streams exposure property information
                */
                __inline PropertyInfo    QueryDSLeftRightExposureInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_DS_LEFTRIGHT_EXPOSURE, &value);
                    return value;
                }

                /**
                @brief Set DS left & right streams exposure value.
                @param[in] value    DS left & right streams exposure value, in milliseconds.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSLeftRightExposure(float value) {
                    return SetProperty(PROPERTY_DS_LEFTRIGHT_EXPOSURE, value);
                }

                /**
                @brief Query the DS left & right streams auto exposure value.
                @return The DS left & right exposure isAuto value
                */
                __inline bool QueryDSLeftRightAutoExposure() {
                    int32_t auto1 = 0;
                    QueryPropertyAuto(PROPERTY_DS_LEFTRIGHT_EXPOSURE, &auto1);
                    return auto1 != 0;
                }

                /**
                @brief Set DS left & right streams exposure value.
                @param[in] auto1    True to enable auto exposure.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSLeftRightAutoExposure(bool32_t auto1) {
                    return SetPropertyAuto(PROPERTY_DS_LEFTRIGHT_EXPOSURE, auto1 ? 1 : 0);
                }

                /**
                @brief Get DS left & right streams gain value.
                @return DS left & right streams gain adjustment, with negative values darker, positive values brighter, and zero as normal.
                */
                __inline int32_t    QueryDSLeftRightGain(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_DS_LEFTRIGHT_GAIN, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get DS left & right streams gain property information.
                @return DS left & right streams  gain property information
                */
                __inline PropertyInfo    QueryDSLeftRightGainInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_DS_LEFTRIGHT_GAIN, &value);
                    return value;
                }

                /**
                @brief Set DS left & right streams gain value.
                @param[in] value    DS left & right streams gain adjustment, with negative values darker, positive values brighter, and zero as normal.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetDSLeftRightGain(int32_t value) {
                    return SetProperty(PROPERTY_DS_LEFTRIGHT_GAIN, (float)value);
                }




                /**
                @brief Query SR300 Color Exposure Priority
                @param[in] value    Color Exposure Priority Value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline int32_t QuerySR300ColorExposurePriority() {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_SR300_COLOR_EXPOSURE_PRIORITY, &value);
                    return (int32_t)value;
                }

                /**
                @brief Get SR300 Color Exposure Priority property information.
                @return  SR300Color Exposure Priority property information
                */
                __inline PropertyInfo    QuerySR300ColorExposurePriorityInfo(void) {
                    PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
                    QueryPropertyInfo(PROPERTY_SR300_COLOR_EXPOSURE_PRIORITY, &value);
                    return value;
                }


                /**
                @brief Set SR300 Color Exposure Priority
                @param[in] value    Color Exposure Priority Value
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetSR300ColorExposurePriority(int32_t value) {
                    return SetProperty(PROPERTY_SR300_COLOR_EXPOSURE_PRIORITY, (float)value);
                }

                /**
                @brief Get the current preset mode.
                @return The preset profile value.
                */
                __inline PresetProfileSR300    QuerySR300PresetProperty(void) {
                    float value = PROPERTY_VALUE_INVALID;
                    QueryProperty(PROPERTY_SR300_PRESETTING_PROFILE, &value);
                    return (PresetProfileSR300)(int32_t)value;
                }
                
                /**
                @brief Set the preset profile mode.
                @param[in] value    The preset profile value.
                @return PXC_STATUS_NO_ERROR             successful execution.
                @return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
                */
                __inline Status SetSR300PresetProperty(PresetProfileSR300 value) {
                    return SetProperty(PROPERTY_SR300_PRESETTING_PROFILE, (float)value);
                }
				
				/**
				@brief Query SR300 External Trigger Delay.
				@return value    The delay value in ms.
				*/
				__inline int32_t QuerySR300ExternalTriggerDelay(void) {
					float value = PROPERTY_VALUE_INVALID;
					QueryProperty(PROPERTY_SR300_EXTERNAL_TRIGGER_DELAY, &value);
					return static_cast<int32_t>(value);
				}

				/**
				@brief Get SR300 External Trigger Delay property information.
				@return SR300 External Trigger Delay property information.
				*/
				__inline PropertyInfo QuerySR300ExternalTriggerDelayInfo(void) {
					PropertyInfo value = { { PROPERTY_VALUE_INVALID,PROPERTY_VALUE_INVALID },0,PROPERTY_VALUE_INVALID };
					QueryPropertyInfo(PROPERTY_SR300_EXTERNAL_TRIGGER_DELAY, &value);
					return value;
				}

				/**
				@brief Set SR300 External Trigger Delay.
				@param[in] value    The delay value in ms.
				@return PXC_STATUS_NO_ERROR             successful execution.
				@return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
				*/
				__inline Status SetSR300ExternalTriggerDelay(int32_t value) {
					return SetProperty(PROPERTY_SR300_EXTERNAL_TRIGGER_DELAY, static_cast<float>(value));
				}

				/**
				@brief Set SR300 External Trigger timestamp initial value.
				@param[in] value    The timestamp initial value.
				@return PXC_STATUS_NO_ERROR             successful execution.
				@return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
				*/
				__inline Status SetSR300ExternalTriggerTSBase(uint64_t value) {
					int32_t msb = value >> 32;
					int32_t lsb = value & 0xFFFFFFFF;
					Status sts = SetProperty(PROPERTY_SR300_EXTERNAL_TRIGGER_TS_BASE, *(reinterpret_cast<float*>(&msb)));
					if (sts == PXC_STATUS_NO_ERROR)
						sts = SetProperty((Property)(PROPERTY_SR300_EXTERNAL_TRIGGER_TS_BASE + 1), *(reinterpret_cast<float*>(&lsb)));
					return sts;
				}

				/**
				@brief Query SR300 External Trigger clock unit.
				@return The clock unit value.
				*/
				__inline int32_t QuerySR300ExternalTriggerClockUnit(void) {
					float value = PROPERTY_VALUE_INVALID;
					QueryProperty(PROPERTY_SR300_EXTERNAL_TRIGGER_CLOCK_UNIT, &value);
					return *(reinterpret_cast<int32_t*>(&value));
				}

				/**
				@brief Set the External Trigger timestamp clock unit.
				@param[in] value    The clock unit value.
				@return PXC_STATUS_NO_ERROR             successful execution.
				@return PXC_STATUS_ITEM_UNAVAILABLE     the device property is not supported.
				*/
				__inline Status SetSR300ExternalTriggerClockUnit(int32_t value) {
					return SetProperty(PROPERTY_SR300_EXTERNAL_TRIGGER_CLOCK_UNIT, *(reinterpret_cast<float*>(&value)));
				}

			};

            typedef Intel::RealSense::Sample Sample;
        };

        typedef Capture::StreamType StreamType;
        typedef Capture::DeviceModel DeviceModel;
        typedef Capture::ConnectionType ConnectionType;
        typedef Capture::DeviceOrientation DeviceOrientation;
        typedef Capture::DeviceInfo DeviceInfo;
        typedef Capture::Device Device;
        typedef Capture::Device::PowerLineFrequency PowerLineFrequency;
        typedef Capture::Device::MirrorMode MirrorMode;
        typedef Capture::Device::IVCAMAccuracy IVCAMAccuracy;
        typedef Capture::Device::Property Property;
        typedef Capture::Device::StreamOption StreamOption;
        typedef Capture::Device::StreamProfile StreamProfile;
        typedef Capture::Device::StreamProfileSet StreamProfileSet;
        typedef Capture::Device::PropertyInfo PropertyInfo;

        /**
        A helper function for bitwise OR of two flags.
        */
        __inline static StreamType operator|(StreamType a, StreamType b) {
            return (StreamType)((int)a | (int)b);
        }

        /**
        A helper function for traversing the stream types: ++stream_type
        */
        __inline static StreamType& operator++(StreamType &a) {
            a = (StreamType)((a << 1)&((1 << (Capture::STREAM_LIMIT)) - 1));
            return a;
        }

        /**
        A helper function for traversing the stream types: stream_type++
        */
        __inline static StreamType operator++(StreamType &a, int) {
            return ++a;
        }

        /**
        A helper function for bitwise OR of two stream options.
        */
        __inline static StreamOption operator | (StreamOption a, StreamOption b) {
            return (StreamOption)((int)a | (int)b);
        }

        /**
        A helper function for bitwise AND of two stream options.
        */
        __inline static StreamOption operator & (StreamOption a, StreamOption b) {
            return (StreamOption)((int)a&(int)b);
        }
    }
}

#pragma warning(pop)
