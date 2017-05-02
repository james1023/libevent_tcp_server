#ifndef IVI_TCP_SERVER_H
#define IVI_TCP_SERVER_H

#include "i_base.h"


#ifdef VI_TCP_SERVER_EXPORTS
	#ifndef IVI_TCP_SERVER_API	
		#define IVI_TCP_SERVER_API   __declspec( dllexport ) 
	#endif
#elif defined(VI_TCP_SERVER_IMPORTS)
	#ifndef IVI_TCP_SERVER_API
		#define IVI_TCP_SERVER_API   __declspec( dllimport )
	#endif
#else
//#pragma message("xxx.lib")
//#pragma comment(lib, "xxx.lib")
	#ifndef IVI_TCP_SERVER_API
		#define IVI_TCP_SERVER_API
	#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

typedef void(*http_cb)(struct evhttp_request *, void *);

//
// Interface.
//
static BOMID BOID_ISTREAM_CLIENT = {0x89c91234, 0x91f6, 0xaaaa, 0x11, 0xab, 0xcd, 0xef, 0x99, 0x88, 0x77, 0xb9}; 

class IVI_TCP_SERVER_API IViTcpServer: public IBase
{
public:
	virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv) = 0;
	virtual void Release() = 0;

	virtual BASE_ERR bind(__b_in int bind_port) = 0;
	virtual void setCb(__b_in const char *path, __b_in http_cb cb, __b_in void *cb_arg) = 0;
	virtual void loop() = 0;
};

IVI_TCP_SERVER_API IViTcpServer *CreateIViTcpServer();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// IVI_TCP_SERVER_H
