/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.

*******************************************************************************/
/** @file base.h
    Defines Base, the base interface for all SDK interfaces
 */
#pragma once
#include "RealSense/Type.h"
#include "RealSense/Status.h"

#if defined(_WIN32) || defined(_WIN64)
#define PXCAPI __stdcall
#else
#define PXCAPI
#endif

namespace Intel {
    namespace RealSense {

        ///////////////////////////////////////////////////////////////////////////////////////
        /**
        This interface forms the base of all SDK interface definitions.
        The interface overrides the class delete operator to work with the SDK
        dispatching mechanism; and exposes a custom (RTTI-free) dynamic casting
        mechanism with the QueryInstance method.  The application that implements
        any Base derived interface must derive from one of the BaseImpl
        class templates.
        */
        class Base {
        public:
            enum { CUID = 0 };
            enum { WORKING_PROFILE = -1 };

            /**
            @brief The function checks if the object instance supports a specific interface.
            If so, return the instance of the interface. Otherwise, returns NULL.
            @param[in] cuid        The interface identifier.
            @return The interface instance, or NULL.
            */
            virtual void* PXCAPI QueryInstance(int32_t cuid) = 0;

            /**
            @brief The function checks if the object instance supports a specific interface.
            If so, return the instance of the interface. Otherwise, returns NULL.
            @return The interface instance, or NULL.
            */
            template <class T> T* QueryInstance(void) { return (T*)this->QueryInstance(T::CUID); }

            /**
            @brief The function releases the object instance. Certain objects are reference
            counted, in which case the function reduces the reference count by 1.
            */
            virtual void PXCAPI Release(void) = 0;

            /**
            @brief The base constructor.
            */
            Base(void) {}

        private:
            /* Call Release() to delele object */
            void operator delete(void* pthis);
            /* Prohibit using copy & assignment constructors */
            Base(Base const &);
            Base& operator = (Base const &);
        };

#define PXC_CUID_OVERWRITE(X) enum { CUID=X }

        ///////////////////////////////////////////////////////////////////////////////////////
        /**
        This template class contains a default implementation of the Base
        interface.  The application that implements any Base derived interface,
        such as a callback handler, should derive the implementation from this
        template class.  See the SDK Interface section (in the sdkcore manual)
        for details.  The BaseImpl template assumes single inheritance.
        The variations, BaseImpl2 and BaseImpl3, implement two or three
        inheritances, respectively.
        */
        template <class T>
        class BaseImpl :public T {
        public:

            virtual ~BaseImpl(void) {}
            enum { CUID = T::CUID + 1 };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T::CUID) return (T*)this;
                if (cuid == Base::CUID) return (Base*)this;
                return 0;
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };

        /** See BaseImpl */
        template <class T1, class T2>
        class BaseImpl2 :public T1, public T2 {
        public:

            virtual ~BaseImpl2(void) {}
            enum { CUID = T1::CUID ^ T2::CUID };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T1::CUID) return (T1*)this;
                if (cuid == T2::CUID) return (T2*)this;
                if (cuid == Base::CUID) return (Base*)(T1*)this;
                return 0;
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };

        /** See BaseImpl */
        template <class T1, class T2>
        class BaseImpl2a :public T1, public T2 {
        public:

            virtual ~BaseImpl2a(void) {}
            enum { CUID = T1::CUID ^ T2::CUID };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T2::CUID) return (T2*)this;
                return T1::QueryInstance(cuid);
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };

        /** See BaseImpl */
        template <class T1, class T2, class T3>
        class BaseImpl3 :public T1, public T2, public T3 {
        public:

            virtual ~BaseImpl3(void) {}
            enum { CUID = T1::CUID ^ T2::CUID ^ T3::CUID };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T1::CUID) return (T1*)this;
                if (cuid == T2::CUID) return (T2*)this;
                if (cuid == T3::CUID) return (T3*)this;
                if (cuid == Intel::RealSense::Base::CUID) return (Intel::RealSense::Base*)(T1*)this;
                return 0;
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };

        /** See BaseImpl */
        template <class T1, class T2, class T3, class T4>
        class BaseImpl4 :public T1, public T2, public T3, public T4 {
        public:

            virtual ~BaseImpl4(void) {}
            enum { CUID = T1::CUID ^ T2::CUID ^ T3::CUID ^ T4::CUID };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T1::CUID) return (T1*)this;
                if (cuid == T2::CUID) return (T2*)this;
                if (cuid == T3::CUID) return (T3*)this;
                if (cuid == T4::CUID) return (T4*)this;
                if (cuid == Base::CUID) return (Base*)(T1*)this;
                return 0;
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };

        /** See BaseImpl */
        template <class T1, class T2, class T3, class T4, class T5>
        class BaseImpl5 :public T1, public T2, public T3, public T4, public T5 {
        public:

            virtual ~BaseImpl5(void) {}
            enum { CUID = T1::CUID ^ T2::CUID ^ T3::CUID ^ T4::CUID ^ T5::CUID };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T1::CUID) return (T1*)this;
                if (cuid == T2::CUID) return (T2*)this;
                if (cuid == T3::CUID) return (T3*)this;
                if (cuid == T4::CUID) return (T4*)this;
                if (cuid == T5::CUID) return (T5*)this;
                if (cuid == Base::CUID) return (Base*)(T1*)this;
                return 0;
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };

        template <class T1, class T2, class T3, class T4, class T5, class T6>
        class BaseImpl6 :public T1, public T2, public T3, public T4, public T5, public T6 {
        public:

            virtual ~BaseImpl6(void) {}
            enum { CUID = T1::CUID ^ T2::CUID ^ T3::CUID ^ T4::CUID ^ T5::CUID ^ T6::CUID };
            virtual void* PXCAPI QueryInstance(int32_t cuid) {
                if (cuid == CUID) return this;
                if (cuid == T1::CUID) return (T1*)this;
                if (cuid == T2::CUID) return (T2*)this;
                if (cuid == T3::CUID) return (T3*)this;
                if (cuid == T4::CUID) return (T4*)this;
                if (cuid == T5::CUID) return (T5*)this;
                if (cuid == T6::CUID) return (T6*)this;
                if (cuid == Base::CUID) return (Base*)(T1*)this;
                return 0;
            }
            virtual void PXCAPI Release(void) { ::delete this; }
            void operator delete(void* pthis) { ::delete(pthis); }
        };
    }
}
