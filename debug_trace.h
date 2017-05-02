#ifndef __DEBUG_TRACE_HPP__
#define __DEBUG_TRACE_HPP__

#if defined(_WIN32) && defined(_DEBUG)
#define _DEBUG_TRACE
#endif

//#if defined(_QT_SYMBIAN_DEF)
//#undef _DEBUG_TRACE
//#endif

#ifdef _DEBUG_TRACE
#define DEBUG_ON			0x01
#else
#define DEBUG_ON			0x00
#endif
#define DEBUG_OFF			0x00

// 
// AVCLive
//
#define COMMON_DBG							DEBUG_ON
#define LOGIN_DBG							DEBUG_OFF
#define HOUND_DBG							DEBUG_OFF
#define SOCKET_DBG							DEBUG_OFF
#define COMMAND_DBG							DEBUG_OFF
#define USERRECORD_DBG						DEBUG_OFF
#define ALARMRECORD_DBG						DEBUG_OFF
#define SCHRECORD_DBG						DEBUG_OFF
#define SETINI_DBG							DEBUG_OFF
// Thread
#define GETIMAGE_DBG						DEBUG_OFF
#define GETAUDIO_DBG						DEBUG_OFF
#define COMPOSE_DBG							DEBUG_OFF
#define SHOWIMAGE_DBG						DEBUG_OFF
#define PLAYAUDIO_DBG						DEBUG_OFF
// Simple
#define AVC_DBG								DEBUG_ON
// Test
#define TEST_DBG							DEBUG_OFF
#define TEST1_DBG							DEBUG_OFF
#define TEST2_DBG							DEBUG_OFF
#define TEST3_DBG							DEBUG_OFF
#define COUNTER_DBG							DEBUG_OFF
#define TIMEING_DBG							DEBUG_OFF
#define GRACE_DBG							DEBUG_OFF
#define LOSSPRO_DBG							DEBUG_ON
#define ADDR_DBG							DEBUG_OFF
#define RELOGIN_DBG							DEBUG_OFF
#define CALLBACK_BITS_STOP_DGB				DEBUG_OFF
#define CALLBACK_RAW_STOP_DGB				DEBUG_OFF
#define GETBITS_DGB							DEBUG_OFF
#define MICROPHONE_DBG						DEBUG_OFF
#define CHECK_GETRAW_INFO_DBG				DEBUG_OFF
#define DECODE_TRACE_DBG					DEBUG_OFF
#define CHECK_H264_DBG						DEBUG_OFF
#define CHECK_RTP_INFO_DBG					DEBUG_OFF
#define FRAMING_DBG							DEBUG_OFF
#define GETFRAME_DBG						DEBUG_OFF
#define RTP_HANDSHAKE_DBG					DEBUG_ON
#define CHECK_RTSP_SPEED_DBG				DEBUG_ON

//
// ONVIF
//
#define CHECK_ACTION_DBG					DEBUG_OFF
#define PARSING_PARAM_DBG				DEBUG_OFF
#define CHECK_COUNT_DBG					DEBUG_OFF

//
// Android
//
#define CHECK_ANDROID_LIVE_DBG		DEBUG_OFF

//
// QT SYMBIAN
//
#define CHECK_QTSYMBIAN_DBG			DEBUG_OFF

//
// LIVE555
//
#define CHECK_RTSP_CONNECT				DEBUG_ON

//
// gSOAP
//
#define CHECK_GSOAP_DBG					DEBUG_OFF

//
// NVR
//
#define CHECK_NVR_1_DBG					DEBUG_OFF
#define CHECK_NVR_2_DBG					DEBUG_ON
#define CHECK_NVR_3_DBG					DEBUG_OFF
#define CHECK_PLAYTHREAD_DBG			DEBUG_OFF
#define CHECK_RES_1_DBG					DEBUG_OFF
#define CHECK_NVR_HC_DBG				DEBUG_OFF
#define CHECK_NVR_SA_DBG				DEBUG_OFF
#define CHECK_NVR_RTCP_DBG				DEBUG_OFF
#define CHECK_NVR_FIRST_LIVE			DEBUG_OFF
#define CHECK_NVR_FMRATE				DEBUG_OFF
#define CHECK_FD_RELEASE				DEBUG_OFF
#define CHECK_PEOC_DBG					DEBUG_OFF

// Check bug
#define GETBUG_DBG						DEBUG_ON
#define TESTBUG_DBG						DEBUG_ON
// Channel Check
#define CH(x) ((x>1)?(1<<(x-1)):x)


// Check bug
#define GETBUG_PB_DBG					DEBUG_ON

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

void dbg_trace(char *fmt, ...);
#define TRACE_D				dbg_trace

#define DEBUG_TRACE(DebugOption,x) do { if (((DebugOption) & DEBUG_ON)) {TRACE_D x;} } while (0)


#ifndef _T
#define _T(x) x
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

//
// Debug write file
//
#define MAX_STRING_LINE (1024*1024)
#ifndef MAX_PATH 
#define MAX_PATH 260
#endif

#endif
