#ifndef _STRLCPY_INTERNAL_H_
#define _STRLCPY_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined OSX
#include <event2/osx/event-config.h>
#elif defined LINUX32
#include <event2/linux/event-config.h>
#else
#include <event2/event-config.h>
#endif

#ifndef _EVENT_HAVE_STRLCPY
#include <string.h>
size_t _event_strlcpy(char *dst, const char *src, size_t siz);
#define strlcpy _event_strlcpy
#endif

#ifdef __cplusplus
}
#endif

#endif

