
#include "platform.h"

#include "vi_tcp_server.h"

ViTcpServer::ViTcpServer():
ev_base_(NULL),
ev_http_(NULL),
evbuffer_(NULL)
{
#if defined(EVTHREAD_USE_PTHREADS_IMPLEMENTED)
	evthread_use_pthreads();
#elif defined(EVTHREAD_USE_WINDOWS_THREADS_IMPLEMENTED)
	evthread_use_windows_threads();
#endif

#if defined(WIN32)
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	ev_base_ = event_base_new();
	if (NULL == ev_base_) {
		DEBUG_TRACE(GETBUG_DBG, ("???#%d ViTcpServer(): BASE_INIT_ERROR. \n", __LINE__));
	}

	ev_http_ = evhttp_new(ev_base_);
	if (NULL == ev_http_) {
		DEBUG_TRACE(GETBUG_DBG, ("???#%d ViTcpServer(): BASE_INIT_ERROR. \n", __LINE__));
	}
}

ViTcpServer::~ViTcpServer()
{
	if (ev_http_) { evhttp_free(ev_http_); ev_http_ = NULL; }
	if (ev_base_) { event_base_free(ev_base_); ev_base_ = NULL; }

	if (evbuffer_) { evbuffer_free(evbuffer_); evbuffer_ = NULL; }
}

IViTcpServer *CreateIViTcpServer()
{
	return static_cast<IViTcpServer *> (new ViTcpServer);
}

void ViTcpServer::Release()
{
	delete this;
}

BASE_ERR ViTcpServer::QueryInterface(REFBOMID riid, void **ppv)
{
	/*if (IsEqualBOMID(riid, BOID_IAV_LIBEVENT)) {
		*ppv = (IAvLibEvent *)this;
		return BASE_OK;
	}
	else*/ {
		return BASE_PARAM_ERROR;
	}
}

BASE_ERR ViTcpServer::bind(int bind_port)
{
	BASE_ERR err = BASE_OK;

	do
	{
		if (!ev_base_ || !ev_http_ || bind_port <= 1) {
			err = BASE_INIT_ERROR;
			DEBUG_TRACE(GETBUG_DBG, ("???#%d LibEvent.Run: BASE_INIT_ERROR. \n", __LINE__));
			break;
		}

		if (!evhttp_bind_socket_with_handle(ev_http_, "0.0.0.0", (short)bind_port)) {
			err = BASE_INIT_ERROR;
			DEBUG_TRACE(GETBUG_DBG, ("?#%d LibEvent::bind: evhttp_bind_socket_with_handle bind_port=%d, err%d. \n", __LINE__, bind_port, err));
			break;
		}
		else {
			DEBUG_TRACE(AVC_DBG, ("#%d LibEvent::bind: bind_port=%d. \n", __LINE__, bind_port));
			break;
		}

	} while (0);

	return err;
}

void ViTcpServer::setCb(const char *path, http_cb cb, void *cb_arg)
{
	if (strlen(path) == 0) {
		evhttp_set_gencb(ev_http_, cb, cb_arg);
		//_http_cb_info http_cb_info = {cb, cb_arg};
		//m_http_cb_map[path] = http_cb_info;
	}
	else {
		if (evhttp_set_cb(ev_http_, path, cb, cb_arg) < 0) {
			DEBUG_TRACE(AVC_DBG, ("#%d evhttp_set_cb failed. \n", __LINE__));
		}
	}

	//for (_http_cb_map::iterator iter = m_http_cb_map.begin(); iter != m_http_cb_map.end(); iter++)
	//	evhttp_set_cb(m_http, iter->first.c_str(), iter->second.cb, iter->second.arg);
}

void ViTcpServer::loop()
{
	event_base_dispatch(ev_base_);
}