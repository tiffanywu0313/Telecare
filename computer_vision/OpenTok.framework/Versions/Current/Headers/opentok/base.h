#ifndef BASE_H
#define BASE_H

#include "config.h"

OTC_BEGIN_DECL

OTC_DECL(otc_status_t) otc_init(void *reserved);

OTC_DECL(otc_status_t) otc_destroy();

enum otc_log_levels_
{
    OTC_LOG_LEVEL_ALL = 100,
    OTC_LOG_LEVEL_TRACE = 7,
    OTC_LOG_LEVEL_DEBUG = 6,
    OTC_LOG_LEVEL_INFO  = 5,
    OTC_LOG_LEVEL_WARN  = 4,
    OTC_LOG_LEVEL_ERROR = 3,
    OTC_LOG_LEVEL_FATAL = 2,
    OTC_LOG_LEVEL_DISABLED = 0
};

OTC_DECL(otc_status_t) otc_log_enable(int log_level);

typedef void(*otc_logger_func)(const char* message);

OTC_DECL(otc_status_t) otc_log_set_logger_func(otc_logger_func func);

OTC_DECL(const char *) otc_get_revision();

OTC_END_DECL

#endif // BASE_H
