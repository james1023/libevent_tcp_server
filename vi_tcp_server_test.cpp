#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "i_base.h"
#include "platform.h"
#include "vi_tcp_server.h"

using namespace std;

CALCU_STATE HandleCalcuType(char *in, CALCU_STATE state, int *total)
{
	int cal_num = 0;

	do {
		if (NULL == in) {
			state = CALCU_STATE_INVALID;
			DEBUG_TRACE(GETBUG_DBG, ("???#%d %s: state=%d, error. \n", __LINE__, __FUNCTION__, state));
			break;
		}

		if (CALCU_STATE_DEC == state) {
			if (0 == strcmp(in, "add")) {
				state = CALCU_STATE_ADD;
				break;
			}
			else if (0 == strcmp(in, "subtract")) {
				state = CALCU_STATE_SUBTRACT;
				break;
			}
			else if (0 == strcmp(in, "multiply")) {
				state = CALCU_STATE_MULTIPLY;
				break;
			}
			else if (0 == strcmp(in, "divide")) {
				state = CALCU_STATE_DIVIDE;
				break;
			}
			else if (0 == strcmp(in, "evaluate")) {
				state = CALCU_STATE_EVALUATE;
				break;
			}
			else {
				state = CALCU_STATE_INVALID;
				DEBUG_TRACE(GETBUG_DBG, ("???#%d %s: state=%d, error. \n", __LINE__, __FUNCTION__, state));
				break;
			}
		}
		else {
			try { cal_num = boost::lexical_cast<int>(in); }
			catch (const boost::bad_lexical_cast &) {
				state = CALCU_STATE_INVALID;
				DEBUG_TRACE(GETBUG_DBG, ("???#%d %s: state=%d, error. \n", __LINE__, __FUNCTION__, state));
				break;
			}

			if (NULL == total) {
				state = CALCU_STATE_INVALID;
				DEBUG_TRACE(GETBUG_DBG, ("???#%d %s: state=%d, error. \n", __LINE__, __FUNCTION__, state));
				break;
			}
			if (state == CALCU_STATE_ADD)
				*total += cal_num;
			else if (state == CALCU_STATE_SUBTRACT)
				*total -= cal_num;
			else if (state == CALCU_STATE_MULTIPLY)
				*total *= cal_num;
			else if (state == CALCU_STATE_DIVIDE) {
				if (cal_num == 0) {
					state = CALCU_STATE_EXCEPTION;
					DEBUG_TRACE(GETBUG_DBG, ("???#%d %s: state=%d, error. \n", __LINE__, __FUNCTION__, state));
					break;
				}
				*total /= cal_num;
			}

			state = CALCU_STATE_DEC;
		}
	} while (0);

	return state;
}

CALCU_STATE HandleEvaluate(char *msg, int *total)
{
	CALCU_STATE state = CALCU_STATE_DEC;
	char *lasts = NULL;
	char *token = NULL;

	do {
		if (NULL == msg || NULL == total) {
			state = CALCU_STATE_INVALID;
			DEBUG_TRACE(GETBUG_DBG, ("???#%d %s: state=%d, error. \n", __LINE__, __FUNCTION__, state));
			break;
		}

		token = strtok_r(msg, ",\n", &lasts);
		while (token != NULL) {
			state = HandleCalcuType(token, state, total);
			if (CALCU_STATE_INVALID == state ||
				CALCU_STATE_EXCEPTION == state ||
				CALCU_STATE_EVALUATE == state)
				break;

			token = strtok_r(NULL, ",\n", &lasts);
		}
	} while (0);

	return state;
}

void evaluate_cb(struct evhttp_request *req, void *arg)
{
	int ret = TRUE;
	
	ViTcpServer *server = (ViTcpServer *)arg;
	CALCU_STATE state = CALCU_STATE_DEC;
	
	int total = 0;
	char *msg = NULL;
	string reply_msg;

	do {
		if (NULL == server || 
			NULL == req ||
			NULL == req->uri) {
			DEBUG_TRACE(AVC_DBG, ("#%d evaluate_cb: param=NULL, error. \n", __LINE__));
			break;
		}

		if (NULL != (msg = strstr(req->uri, "/evaluate.cgi?"))) {
			msg += strlen("/evaluate.cgi?");
		}
		else {
			DEBUG_TRACE(AVC_DBG, ("#%d evaluate_cb: no evaluate.cgi?, error. \n", __LINE__));
			break;
		}

		state = HandleEvaluate(msg, &total);
		
		if (CALCU_STATE_EVALUATE == state) {
			reply_msg = boost::lexical_cast<std::string>(total);
		}
		else if (state == CALCU_STATE_EXCEPTION) {
			reply_msg = "Exception";
		}
		else {
			reply_msg = "Invalid";
		}
		
		if (NULL == server->evbuffer())
			server->set_evbuffer(evbuffer_new());

		evbuffer_add_printf(server->evbuffer(), "%s", reply_msg.c_str());
		evhttp_send_reply(req, HTTP_OK, "OK", server->evbuffer());
	} while (0);

	return;
}

int main()
{
	IViTcpServer *i_vi_server = CreateIViTcpServer();
	
	i_vi_server->bind(88);
	i_vi_server->setCb("/evaluate.cgi", evaluate_cb, i_vi_server);

	i_vi_server->loop();

	i_vi_server->Release();

	return 1;
}
