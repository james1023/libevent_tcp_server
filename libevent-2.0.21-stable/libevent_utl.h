#if !defined LIBEVENT_UTL_H
#define LIBEVENT_UTL_H


// libevent
// #ifdef WIN32
// #include <winsock2.h>
// #include <WS2tcpip.h>
// #include <windows.h>
// #else
// #include <sys/socket.h>
// #include <sys/wait.h>
// #include <signal.h>
// #include <unistd.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #endif
#include <sys/types.h>
#include <sys/stat.h>
#include "sys/queue.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "event.h"
#include "evhttp.h"
#include "event-internal.h"
#include "http-internal.h"
#include "log-internal.h"

typedef struct _register_evhttp_cb2 {
	int (*cb2)(void *, void *);
	void *arg1;
} register_evhttp_cb2;

#ifdef __cplusplus
extern "C" {
#endif

extern int httputl_connect(const char *address, u_short port);	
extern struct evhttp *httputl_setup(short *, struct event_base *);
// james: 100222 register_evhttp_cb2 must be alive while event loop.
extern void httputl_setup_set_cb(struct evhttp *, const char *, void (*)(struct evhttp_request *, void *), register_evhttp_cb2 *);
extern int httputl_send_message(const char *ip, short port, const char *uri, const char *post_data);
extern int httputl_loopexit(struct evhttp* http);
extern void httputl_readcb(struct bufferevent *bev, void *arg);
extern void httputl_writecb(struct bufferevent *bev, void *arg);
extern void httputl_errorcb(struct bufferevent *bev, short what, void *arg);

#ifdef __cplusplus
}
#endif

#endif // LIBEVENT_UTL_H