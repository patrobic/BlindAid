/*******************************************************************************

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2014-2016 Intel Corporation. All Rights Reserved.

*******************************************************************************/
#pragma once
#include "RealSense/Base.h"
#include <string>

namespace Intel {
    namespace RealSense {

            namespace Service {

                class LoggingService : public Base {
                public:
                    PXC_CUID_OVERWRITE(0x3870DB28);

                    enum Level {
                        LEVEL_FATAL = 50000,
                        LEVEL_ERROR = 40000,
                        LEVEL_WARN = 30000,
                        LEVEL_INFO = 20000,
                        LEVEL_DEBUG = 10000,
                        LEVEL_TRACE = 5000,
                        LEVEL_VERBOSE = 2500,
                    };

                    enum ConfigMode {
                        CONFIG_DEFAULT = 0x1,
                        CONFIG_PROPERTY_FILE_LOG4J = 0x2,
                        CONFIG_XML_FILE_LOG4J = 0x4,
                    };

                    virtual Status   PXCAPI SetLoggerName(const wchar_t* name) = 0; // name in loggers hierarchy. NULL means root logger. Name may contain dots like class and namespace hierarchy in C#
                    virtual Status   PXCAPI Configure(ConfigMode configMode, const wchar_t* config, int fileWatchDelay) = 0; // if fileWatchDelay non-zero, specifies delay in ms to check if config file changed (only for CONFIG_PROPERTY_FILE_LOG4J and CONFIG_XML_FILE_LOG4J)
                    virtual bool32_t     PXCAPI IsConfigured() = 0; // configuration is process-wide for all loggers, call Configure() once per application
                    virtual Status   PXCAPI SetLevel(Level level) = 0; // overwrite level specified in initial configuration

                    virtual bool32_t     PXCAPI IsLevelEnabled(Level level) = 0;
                    virtual Level       PXCAPI GetLevel() = 0;
                    virtual void        PXCAPI Log(Level level, const char*    message, const char* fileName, int lineNumber, const char* functionName) = 0;
                    virtual void        PXCAPI LogW(Level level, const wchar_t* message, const char* fileName, int lineNumber, const char* functionName) = 0;

                    // performance tracing
                    virtual void        PXCAPI TaskBegin(Level level, const char* taskName) = 0;
                    virtual void        PXCAPI TaskEnd(Level level, const char* taskName) = 0;
                };

                typedef LoggingService::Level LoggingLevel;
                typedef LoggingService::ConfigMode LoggingConfigMode;

                ////////////////////////////////////////////////////////////////////////////////

                // Utility macro for logging
#define PXCLOG(_logger, _level, _message)               \
{                                                       \
    if (_logger->IsLevelEnabled(_level))                \
    {                                                   \
        _logger->Log(_level, _message, __FILE__, __LINE__, __FUNCSIG__); \
    }                                                   \
}

                // Utility class for tasks in performance tracing
                class TraceTask {
                public:

                    TraceTask(LoggingService *logger, LoggingLevel level, const char* taskName)
                    {
                        if (logger->IsLevelEnabled(level) && taskName[0])
                        {
                            this->logger = logger;
                            this->level = level;
                            this->taskName = taskName;
                            logger->TaskBegin(level, taskName);
                        }
                        else
                        {
                            this->logger = NULL;
                            this->level = LoggingLevel::LEVEL_DEBUG;
                            this->taskName = NULL;
                        }
                    }

                    ~TraceTask()
                    {
                        if (this->logger)
                        {
                            logger->TaskEnd(level, taskName);
                        }
                    }

                private:

                    LoggingService* logger;
                    LoggingLevel    level;
                    const char*     taskName;
                };

                /**
                A helper function for bitwise OR of two flags.
                */
                __inline static LoggingLevel operator|(LoggingLevel a, LoggingLevel b) {
                    return (LoggingLevel)((int)a | (int)b);
                }
            }
        }
    }
