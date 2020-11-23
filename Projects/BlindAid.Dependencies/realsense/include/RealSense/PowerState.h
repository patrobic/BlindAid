/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcpowerstate.h
    Defines the PXCPowerState interface,  which exposes controls for
    detecting and changing the power state of the runtimes.
  */
#pragma once
#include "RealSense/Session.h"

namespace Intel {
    namespace RealSense {

        /**
        This interface manages the SDK implementation power state.  Any SDK I/O
        or algorithm module implementation that are power aware exposes this
        interface.  Programs may use the QueryInstance function to bind to this
        interface from any module instance.
        */
        class PowerState : public Base {
        public:
            PXC_CUID_OVERWRITE(PXC_UID('P', 'W', 'M', 'G'));

            enum State
            {
                STATE_PERFORMANCE,         /* full feature set/best algorithm */
                STATE_BATTERY,
            };

            /* Query current power state of the device, returns maximal used state */
            virtual State PXCAPI QueryState() = 0;

            /* Try to set power state of all used devices, all streams, application should call
            QueryStream to check if the desired state was set */
            virtual Status PXCAPI SetState(State state) = 0;

            /* Sets inactivity interval */
            virtual Status PXCAPI SetInactivityInterval(int32_t timeInSeconds) = 0;

            /* Returns inactivity interval */
            virtual int32_t PXCAPI QueryInactivityInterval() = 0;

			/**
			@brief Create an instance of the power manager.
			@return The PXCPowerState instance.
			*/
			__inline static PowerState *CreateInstance(Session *session) {
				PowerState *pm = 0;
				session->CreateImpl<PowerState>(&pm);
				return pm;
			}
        };

        typedef PowerState::State PowerStateType;
    }
}
