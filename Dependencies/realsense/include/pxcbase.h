/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2013 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file pxcbase.h
    Defines PXCBase, the base interface for all SDK interfaces
 */
#pragma once
#include "pxcdefs.h"
#include "pxcstatus.h"
#include "RealSense/Base.h"

///////////////////////////////////////////////////////////////////////////////////////
/**
   This interface forms the base of all SDK interface definitions.
   The interface overrides the class delete operator to work with the SDK
   dispatching mechanism; and exposes a custom (RTTI-free) dynamic casting
   mechanism with the QueryInstance method.  The application that implements
   any PXCBase derived interface must derive from one of the PXCBaseImpl
   class templates.
 */
typedef Intel::RealSense::Base PXCBase;

template <class T> class PXCBaseImpl : public Intel::RealSense::BaseImpl<T> {};
template <class T1, class T2> class PXCBaseImpl2 : public Intel::RealSense::BaseImpl2<T1,T2> {};
template <class T1, class T2, class T3> class PXCBaseImpl3 : public Intel::RealSense::BaseImpl3<T1,T2,T3> {};
template <class T1, class T2, class T3, class T4> class PXCBaseImpl4 : public Intel::RealSense::BaseImpl4<T1,T2,T3,T4> {};
template <class T1, class T2, class T3, class T4, class T5> class PXCBaseImpl5 : public Intel::RealSense::BaseImpl5<T1,T2,T3,T4,T5> {};
template <class T1, class T2, class T3, class T4, class T5, class T6> class PXCBaseImpl6 : public Intel::RealSense::BaseImpl6<T1,T2,T3,T4,T5,T6> {};
