#include "libevent_utl.h"

int httputl_connect(const char *address, u_short port)
{	
	/* Stupid code for connecting */
#if defined(WIN32) || defined(_QT_SYMBIAN_DEF)
	struct hostent *he;
	struct sockaddr_in sin;
#else
	struct addrinfo ai, *aitop;
	char strport[NI_MAXSERV];
#endif
	struct sockaddr *sa;
	int slen;
	int fd;
	
#if defined(WIN32) || defined(_QT_SYMBIAN_DEF)
	if (!(he = gethostbyname(address))) {
		event_warn("gethostbyname");
	}
	memcpy(&sin.sin_addr, he->h_addr_list[0], he->h_length);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	slen = sizeof(struct sockaddr_in);
	sa = (struct sockaddr*)&sin;
#else
	memset(&ai, 0, sizeof (ai));
	ai.ai_family = AF_INET;
	ai.ai_socktype = SOCK_STREAM;
	snprintf(strport, sizeof (strport), "%d", port);
	if (getaddrinfo(address, strport, &ai, &aitop) != 0) {
		event_warn("getaddrinfo");
		return (-1);
	}
	sa = aitop->ai_addr;
	slen = aitop->ai_addrlen;
#endif

	do 
	{
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd == -1)
		{
			break;
		}

		if (connect(fd, sa, slen) == -1)
		{
			fd = -1;
			break;
		}
	} while (0);

#if !defined(WIN32) && !defined(_QT_SYMBIAN_DEF)
	freeaddrinfo(aitop);
#endif

	return (fd);
}


void httputl_setup_set_cb(struct evhttp *http, const char *uri, void (*cb)(struct evhttp_request *, void *), register_evhttp_cb2 *regcb2)
{
	/* Register a callback for certain types of requests */
	evhttp_set_cb(http, uri, cb, regcb2);
}

struct evhttp *httputl_setup(short *pport, struct event_base *base)
{
	int i;
	struct evhttp *myhttp;
	short port = -1;

	// james: 100219 modify port if bind port failed.
	if (*pport > 0 && *pport < 65536) port = *pport;

	/* Try a few different ports */
	myhttp = evhttp_new(base);
	for (i = 0; i < 50; ++i) {
		if (evhttp_bind_socket(myhttp, NULL, port + i) != -1) {
			port = port + i;
			break;
		}
	}

	if (port < 0)
	{
		//"Could not start web server"
		return NULL;
	}

	*pport = port;
	return (myhttp);
}

int httputl_send_message(const char *ip, short port, const char *uri, const char *post_data)
{
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;

	evcon = evhttp_connection_new(ip, port);
	if (evcon == NULL) {
		fprintf(stdout, "FAILED\n");
		return (-1);
	}

	/*
	* At this point, we want to schedule an HTTP POST request
	* server using our make request method.
	*/
	req = evhttp_request_new(NULL, NULL);
	if (req == NULL) {
		fprintf(stdout, "FAILED\n");
		return (-1);
	}

	/* Add the information that we care about */
	evhttp_add_header(req->output_headers, "Host", ip);
	if (post_data)
		evbuffer_add_printf(req->output_buffer, post_data);

	if (evhttp_make_request(evcon, req, EVHTTP_REQ_POST, uri) == -1) {
		fprintf(stdout, "FAILED\n");
		return (-1);
	}

	return (0);
}

int httputl_loopexit(struct evhttp* http)
{
	int fd;
	struct evhttp_bound_socket *bound;

	if (http == NULL) return 0;

	if ((bound = TAILQ_FIRST(&http->sockets)) != NULL) {
		fd = bound->bind_ev.ev_fd;
		EVUTIL_CLOSESOCKET(fd);
	}

	//event_loopexit(NULL);

	return (0);
}

void httputl_readcb(struct bufferevent *bev, void *arg)
{
	int ret = 1;
	struct evhttp_request *req = evhttp_request_new(NULL, NULL);
	enum message_read_status done;

	do 
	{
		req->kind = EVHTTP_RESPONSE;
		done = evhttp_parse_firstline(req, bev->input);
		if (done != ALL_DATA_READ)
		{
			ret = 0;
			break;
		}

		done = evhttp_parse_headers(req, bev->input);
		if (done != ALL_DATA_READ)
		{
			ret = 0;
			break;
		}

		if (done == 1 &&
			evhttp_find_header(req->input_headers,
			"Content-Type") == NULL)
		{
			ret = 0;
			break;
		}

		bev->input->head_len = bev->input->misalign;
		bev->input->body_len = bev->input->off;
		bev->input->src_buffer = (u_char *)malloc(bev->input->head_len+bev->input->body_len+10);
		bev->input->src_buffer[bev->input->head_len+bev->input->body_len] = 0;
		memcpy(bev->input->src_buffer, bev->input->orig_buffer, bev->input->head_len+bev->input->body_len);
		event_debug(("libevent.%s, bev->input->src_buffer=%s. \n", __func__, bev->input->src_buffer));
	} while (0);

	evhttp_request_free(req);
	bufferevent_disable(bev, EV_READ);
	event_loopexit(NULL);
}

void httputl_writecb(struct bufferevent *bev, void *arg)
{
	if (EVBUFFER_LENGTH(bev->output) == 0) {
		/* enable reading of the reply */
		bufferevent_enable(bev, EV_READ);
		//test_ok++;
	}
}

void httputl_errorcb(struct bufferevent *bev, short what, void *arg)
{
	//test_ok = -2;
	event_loopexit(NULL);
}
