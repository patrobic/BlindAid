/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2014 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Base.h"
#include <stdint.h>

#ifndef _WIN32
#include <atomic>
#endif

namespace Intel {
    namespace RealSense {

        /**
        The interface adds a reference count to the supported object.
        */
        class Reference {
        public:

            PXC_CUID_OVERWRITE(PXC_UID('B', 'A', 'S', 'S'));

            /**
            @brief Increase the reference counter of the underlying object.
            @return The increased reference counter value.
            */
            virtual int32_t PXCAPI AddRef(void) = 0;

        private:
            /* Prohibit using delete operator */
            void operator delete(void* pthis);
        };

        ///////////////////////////////////////////////////////////////////////////////////////

        /**
        This is the base implementation of the PXCAddRef interface.
        */
        template <class T>
        class ReferenceImpl :public T, public Reference {
        public:

            ReferenceImpl()
#ifdef _WIN32
				:m_refCount(*(volatile long *)(((intptr_t)m_blocks + 3) & ~(intptr_t)3))
#endif
			{
                m_refCount = 1;
            }

            virtual ~ReferenceImpl(void) {}

            virtual int32_t PXCAPI AddRef(void)
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

            virtual void* PXCAPI QueryInstance(int32_t cuid)
            {
                return (cuid == Reference::CUID) ? (Reference*)this : T::QueryInstance(cuid);
            }

            void operator delete(void* pthis) { ((Base*)pthis)->Release(); }

        protected:

#ifdef _WIN32
			volatile long &m_refCount;
		private:
			int8_t m_blocks[8];
#else
            std::atomic<int>  m_refCount;
#endif
        };
    }
}
