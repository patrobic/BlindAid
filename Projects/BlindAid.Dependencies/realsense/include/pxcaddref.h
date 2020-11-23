/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "pxcbase.h"
#include "RealSense/Reference.h"

/**
The interface adds a reference count to the supported object.
*/
typedef Intel::RealSense::Reference PXCAddRef;
//template <class T> using PXCAddRefImpl = Intel::RealSense::ReferenceImpl<T>;

///////////////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32
#include <atomic>
#endif
/**
This is the base implementation of the PXCAddRef interface.
*/
template <class T>
class PXCAddRefImpl:public T, public PXCAddRef {
public:

    PXCAddRefImpl()
#ifdef _WIN32
		:m_refCount(*(volatile long *)(((intptr_t)m_blocks + 3) & ~(intptr_t)3))
#endif
	{
        m_refCount = 1;
    }

	virtual ~PXCAddRefImpl(void) {}

    virtual pxcI32 PXCAPI AddRef(void)
    {
#ifdef _WIN32
        return _InterlockedIncrement(&m_refCount);
#else
        return ++m_refCount;
#endif
    }

    virtual void   PXCAPI Release(void)
    {
#ifdef _WIN32
        if (!_InterlockedDecrement(&m_refCount)) ::delete this;
#else
        if (!--m_refCount) ::delete this;
#endif
    }

    virtual void* PXCAPI QueryInstance(pxcUID cuid)
    {
        return (cuid == PXCAddRef::CUID) ? (PXCAddRef*)this : T::QueryInstance(cuid);
    }

    void operator delete(void* pthis) { ((PXCBase*)pthis)->Release(); }

protected:
#ifdef _WIN32
	volatile long &m_refCount;
private:
	pxcBYTE m_blocks[8];
#else
    std::atomic<int>  m_refCount;
#endif
};
