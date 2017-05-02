#ifndef IBASE_C_H
#define IBASE_C_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

#define __b_in
#define __b_in_opt
#define __b_out
#define __b_out_opt
#define __b_inout
#define __b_inout_opt

typedef enum _BASE_ERR
{
	BASE_OK																= 1,
    BASE_CONNECT_FAILED										= 0,
    BASE_HTTP_401_Unauthorized							= -1,
    BASE_PARAM_ERROR											= -2,
    BASE_USERLIMIT_ERROR										= -3,
	BASE_IMGRES_NOSUPT										= -4,
    BASE_FRAME_OVERFLOW_ERROR						= -5,
    BASE_ENCODING_NOSUPT									= -6,
    BASE_SERVER_OVER											= -7,
	BASE_MEMORY_ERROR											= -8,
	BASE_FRAME_ERROR											= -9,
	BASE_IO_ERROR													= -10,
	BASE_RECV_ERROR												= -11,
	BASE_RECV_AGAIN_ERROR									= -12,
	BASE_INIT_ERROR												= -13,
	BASE_HTTP_404_Not_Found								= -14,
    BASE_STREAM_WARNING_TIMEOUT						= -20,
} BASE_ERR;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// IBASE_C_H
