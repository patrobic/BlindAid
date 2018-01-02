/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Session.h"

class PXCSchedulerService;

namespace Intel {
    namespace RealSense {

            namespace Service {
                class Accelerator;

                class SessionService :public Base {
                public:
                    PXC_CUID_OVERWRITE(PXC_UID('S', 'E', 'S', '2'));
                    PXC_DEFINE_UID(SUID_DLL_EXPORT_TABLE, 'D', 'L', 'E', 2);

                    /* algorithms in this group are core services */
                    PXC_DEFINE_CONST(IMPL_SUBGROUP_ACCELERATOR, 0x80000000);
                    PXC_DEFINE_CONST(IMPL_SUBGROUP_SCHEDULER, 0x40000000);
                    PXC_DEFINE_CONST(IMPL_SUBGROUP_POWER_MANAGEMENT, 0x20000000);

                    struct DLLExportTable {
                        DLLExportTable  *next;
                        Status (PXCAPI *createInstance)(Session *session, PXCSchedulerService *reserved, Accelerator *reserved2, DLLExportTable *table, int32_t cuid, Base **instance);
                        int32_t          suid;
                        ImplDesc         desc;
                    };

                    virtual Status PXCAPI QueryImplEx(ImplDesc *templat, int32_t idx, DLLExportTable **table, void ***instance) = 0;

                    virtual Status PXCAPI LoadImpl(DLLExportTable *table) = 0;
                    virtual Status PXCAPI UnloadImpl(DLLExportTable *table) = 0;

                    virtual void   PXCAPI TraceEvent(const wchar_t* /*event_name*/) {}
                    virtual void   PXCAPI TraceBegin(const wchar_t* /*task_name*/) {}
                    virtual void   PXCAPI TraceEnd(void) {}
                    virtual void   PXCAPI TraceParam(const wchar_t* /*param_name*/, const wchar_t* /*param_value*/) {}
                };

                typedef SessionService::DLLExportTable DLLExportTable;
            }
        }
    }
