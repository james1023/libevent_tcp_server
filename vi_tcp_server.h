#ifndef __VI_TCP_SERVER_H__
#define __VI_TCP_SERVER_H__

#include "i_vi_tcp_server.h"

#if defined OSX
#include <event2/osx/event-config.h>
#elif defined LINUX32
#include <event2/linux/event-config.h>
#else
#include <event2/win32/event-config.h>
#endif

#include "event2/http.h"
#include "event2/event.h"
#include "event2/event_compat.h"
#include "event2/buffer.h"
#include "event2/buffer_compat.h"
#include "event2/bufferevent.h"
#include "event2/bufferevent_compat.h"
#include "event2/http_struct.h"
#include "event2/http_compat.h"
#include "event2/util.h"
#include "event2/listener.h"
#include "log-internal.h"
#include "util-internal.h"
#include "http-internal.h"
#include "mm-internal.h"
#include "bufferevent-internal.h"
#include "evbuffer-internal.h"
#include "evthread-internal.h"

typedef enum {
	CALCU_STATE_DEC = 0,			// number mode.
	CALCU_STATE_ADD,				// add mode.
	CALCU_STATE_SUBTRACT,		// subtrace mode.
	CALCU_STATE_DIVIDE,			// divide mode.
	CALCU_STATE_MULTIPLY,		// multiply mode.
	CALCU_STATE_INVALID,			// invalid mode.
	CALCU_STATE_EXCEPTION,		// exception mode. ex divide 0.
	CALCU_STATE_EVALUATE			// done mode.
} CALCU_STATE;	

class ViTcpServer: public IViTcpServer
{
private:
	struct event_base *ev_base_;
	struct evhttp *ev_http_;

	struct evbuffer *evbuffer_;

public:
	ViTcpServer();
	virtual ~ViTcpServer();

	BASE_ERR QueryInterface(REFBOMID riid, void **ppv);
	void Release();
	
	BASE_ERR bind(int bind_port);
	void setCb(const char *path, http_cb cb, void *cb_arg);
	void loop();

	struct evbuffer *evbuffer() const {
		return evbuffer_;
	}
	void set_evbuffer(struct evbuffer *in) {
		evbuffer_ = in;
	}
};

#endif // __VI_TCP_SERVER_H__