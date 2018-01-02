/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION                                             
This software is supplied under the terms of a license agreement or nondisclosure     
agreement with Intel Corporation and may not be copied or disclosed except in         
accordance with the terms of that agreement                                           
Copyright(c) 2012-2016 Intel Corporation. All Rights Reserved.                        

*******************************************************************************/ 
#pragma once 

#define PXC_VERSION_MAJOR    11 
#define PXC_VERSION_MINOR    0 
#define PXC_VERSION_BUILD    0 
#define PXC_VERSION_REVISION 420 

#ifndef LSTR
#define LSTR(text) L##text
#endif
#define STR(x) #x

#define RSSDK_REG_DEV           LSTR("Software\\Intel\\RSSDK") 
#define RSSDK_REG_DEV32         LSTR("Software\\Wow6432Node\\Intel\\RSSDK") 

#define RSSDK_REG_RUNTIME       LSTR("Software\\Intel\\RSSDK\\v11") 
#define RSSDK_REG_RUNTIME32     LSTR("Software\\Wow6432Node\\Intel\\RSSDK\\v11") 

#define RSSDK_REG_DISPATCH      RSSDK_REG_RUNTIME   LSTR("\\Dispatch") 
#define RSSDK_REG_DISPATCH32    RSSDK_REG_RUNTIME32 LSTR("\\Dispatch") 

#define RSSDK_REG_DISPATCH_VERSION LSTR("Software\\Intel\\RSSDK\\v%d\\Dispatch") 
#define RSSDK_MIN_CAPTURE_VERSION  2 

#define RSDCM_REG_DEV           LSTR("Software\\Intel\\RSDCM") 
#define RSDCM_REG_DEV32         LSTR("Software\\Wow6432Node\\Intel\\RSDCM") 

#define RS_COPYRIGHT(x) "Copyright(C) " STR(x) "-2016, Intel Corporation. All Rights Reserved." 

#define STR_SDK_VERSION(MAJVER,MINVER,SUBVER,REV) STR(MAJVER) "." STR(MINVER) "." STR(SUBVER) "." STR(REV) 
