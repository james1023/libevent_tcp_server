/*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1998-2005 Intel Corporation. All Rights Reserved.
//
//  Intel(R) Integrated Performance Primitives Intel(R) JPEG Library -
//        Intel(R) IPP Version for Windows*
//
//  By downloading and installing this sample, you hereby agree that the
//  accompanying Materials are being provided to you under the terms and
//  conditions of the End User License Agreement for the Intel(R) Integrated
//  Performance Primitives product previously accepted by you. Please refer
//  to the file ipplic.htm located in the root directory of your Intel(R) IPP product
//  installation for more information.
//
//  JPEG is an international standard promoted by ISO/IEC and other organizations.
//  Implementations of these standards, or the standard enabled platforms may
//  require licenses from various entities, including Intel Corporation.
//
*/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/*
#ifndef IJL_ALL_WARNINGS
#if defined (_WIN32)
#if _MSC_VER >= 1000

// nonstandard extension used : nameless struct/union
#pragma warning(disable : 4201)
// nonstandard extension used : bit field types other than int
#pragma warning(disable : 4214)
// unreferenced inline function has been removed
#pragma warning(disable : 4514)
// named type definition in parentheses
#pragma warning(disable : 4115)
// conditional expression is constant
#pragma warning(disable:4127)

#endif // _MSC_VER >= 1000
#endif // _WIN32
#endif // IJL_ALL_WARNINGS
*/

#if defined(__cplusplus)
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <iterator>
#include <cctype>
#include <algorithm>
#include <exception>

using namespace std;
#endif // #if defined(__cplusplus)


#if defined(_WIN32)
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <WinBase.h>
#include <process.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#elif defined(LINUX32)
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <dlfcn.h>
#include <net/if.h>
#include <signal.h> 
	#if defined(_ANDROID_LINUX)
		#include <android/log.h>
	#elif defined(_QT_SYMBIAN_DEF)
		#include <QDebug>
	#endif
#elif defined(_ITRON)
#include <includes.h>
#include <libasdb_interface.h>
#include <spook/libhttpd.h>
//#include <ey_types.h>
//#include <ey_sys.h>
#include <auxiliary_fun_cpu1.h>
#endif // _WIN32


#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 


#if defined(_WIN32)
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define strdup _strdup
#define snprintf _snprintf
#define _sscanf sscanf
#define ssize_t int
typedef unsigned char				BOOLEAN;
typedef unsigned char				INT8U;
typedef signed char					INT8S;
typedef unsigned short			INT16U;
typedef signed short				INT16S;
typedef unsigned long				INT32U;
typedef signed long					INT32S;
typedef float							FP32;
typedef double							FP64;
extern char *strtok_r(char *s, const char *delim, char **lasts);
#endif // #if defined(_WIN32)


#if defined(_ITRON)
extern void *calloc(size_t _NumOfElements, size_t _SizeOfElements);
extern void *malloc(size_t _Size);
extern void free(void * _Memory);
extern char *strdup(const char *s);
extern int itron_strncasecmp(const char *str1 , const char *str2, int len);
extern int itron_strcasecmp(const char *str1 , const char *str2);
extern char *strtok_r(char *s, const char *delim, char **lasts);
//extern void *fopen(const char * _Filename, const char * _Mode);

#if defined(__cplusplus)
void *operator new(size_t n);
void *operator new[](size_t n);
void operator delete(void *p);
void operator delete[](void *p);
#endif // #if defined(__cplusplus)

#define strcasecmp itron_strcasecmp
#define strncasecmp itron_strncasecmp
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define _strdup strdup
#define sscanf itron_sscanf
#define _sscanf sscanf
#endif // #if defined(_ITRON)


#if defined(LINUX32)
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define _strdup strdup
#define _snprintf snprintf
#define _sscanf sscanf
typedef unsigned char				BOOLEAN;
typedef unsigned						Boolean;
typedef unsigned char				INT8U;
typedef signed char					INT8S;
typedef unsigned short			INT16U;
typedef signed short				INT16S;
typedef unsigned long				INT32U;
typedef signed long					INT32S;
typedef float							FP32;
typedef double							FP64;

typedef int								BOOL;
typedef int								INT;
typedef unsigned int					UINT;
//typedef unsigned int				size_t;
#endif // #if defined(LINUX32)


#if defined(LINUX32) || defined(_ITRON)
//typedef void VOID;
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef unsigned long				DWORD;
typedef unsigned char				BYTE;
typedef unsigned short				WORD;
typedef float							FLOAT;
typedef FLOAT							*PFLOAT;
typedef BOOL							*PBOOL;
typedef BOOL							*LPBOOL;
typedef BYTE							*PBYTE;
typedef BYTE							*LPBYTE;
typedef int								*PINT;
typedef int								*LPINT;
typedef WORD							*PWORD;
typedef WORD							*LPWORD;
typedef long							*LPLONG;
typedef DWORD						*PDWORD;
typedef DWORD						*LPDWORD;
typedef void							*LPVOID;
typedef const void					*LPCVOID;
typedef int								SOCKET;
typedef unsigned int					*PUINT;
typedef DWORD						ULONG;
typedef unsigned short				USHORT;
typedef const char*					LPCSTR;
typedef char*							LPSTR;
typedef DWORD						COLORREF;
typedef DWORD						*LPCOLORREF;

#define LOWORD(l)					((WORD)((l) & 0xffff))
#define HIWORD(l)					((WORD)((l) >> 16))
#define LOBYTE(w)					((BYTE)((w) & 0xff))
#define HIBYTE(w)					((BYTE)((w) >> 8))

typedef struct tagPOINT
{
	long x;
	long y;
} POINT, *PPOINT;

#if defined(LINUX32)
#define FALSE 0
#define TRUE 1
#elif defined(_ITRON)
#define __FUNCTION__				"??"
#endif // #if defined(LINUX32)
#define GENERIC_READ  1
#define GENERIC_WRITE 2
#define FILE_BEGIN SEEK_SET
#define FILE_CURRENT SEEK_CUR
#define INVALID_HANDLE_VALUE 0xffffffff
#define CREATE_ALWAYS 0
#define OPEN_EXISTING 1
//#define max(a, b) (((a) > (b)) ? (a) : (b))
//#define min(a, b) (((a) < (b)) ? (a) : (b))
#define UNREFERENCED_PARAMETER(a) (void)(a)
#define TEXT(str) str

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif // #if defined(LINUX32) || defined(_ITRON)

typedef unsigned char u_char;



#define CLIP(i) ((i) > 255 ? 255 : ((i) < 0 ? 0 : (i)))

#define CPU_CACHE_LINE      32
#define DCTSIZE             8
#define DCTSIZE2            64
#define IJL_OPAQUE          0xFF
#define MAX_COMMENTS_SIZE   65531
#define MAX_COMP_PER_FRAME  255
#define MAX_COMP_PER_SCAN   4
#define MAX_BLKS_PER_MCU    10
#define MAX_MCU_SIZE        (DCTSIZE2*MAX_BLKS_PER_MCU)
#define MIN_DCT_VAL         (-1023)
#define MAX_DCT_VAL         ( 1023)
#define MAX_MCU_ROWS        8192

#define JFXX_THUMBNAILS_JPEG  0x10
#define JFXX_THUMBNAILS_GRAY  0x11
#define JFXX_THUMBNAILS_RGB   0x13

#define OWN_ALIGN_PTR(ptr,align) \
  ippAlignPtr(ptr,align)


#if defined(_ITRON)
#define SAFE_FREE(x)	{ if (x) { free(x); x = NULL; } }
#define SAFE_MALLOC(x, y) { if (x == NULL) { x = (LPBYTE)malloc(y); } }
#define exit(x)
#else
#define SAFE_FREE(x)	{ if (x) { free(x); x = NULL; } }
#define SAFE_DELETE(x)	{ if (x) { delete x; x = NULL; } }
#define SAFE_DELETEA(x) { if (x) { delete[] x; x = NULL; } }
#define SAFE_MALLOC(x, y) { if (x == NULL) { x = (LPBYTE)malloc(y); } }
#endif // #if defined(_ITRON)

#if defined(_WIN32)
#define SAFE_CLOSEHANDLE(x) { if (x) { 	::CloseHandle(x); x = NULL; } }
#define CLOSESOCKET(x) ::closesocket(x)
#endif // #if defined(_WIN32)

#if defined(LINUX32)
#define CLOSESOCKET(x) ::close(x)
#endif // #if defined(LINUX32)

#define SAFE_CLOSESOCKET(x) { if (x) { CLOSESOCKET(x); 	x = NULL; } }

#define SAFE_RELEASE(PTR) \
if (PTR) \
{ \
	PTR->Release(); \
	PTR = NULL; \
}

#if defined(LINUX32) || defined(_ITRON)
#define GetLastError() -1
#define WSAGetLastError() -1
#endif // #if defined(LINUX32) || defined(_ITRON)

#define MAX(a,b) (a) > (b) ? (a) : (b)
#define MIN(a,b) (a) > (b) ? (b) : (a)

#define TIME_AFTER(a,b)				((long)(b) - (long)(a) < 0)
#define TIME_BEFORE(a,b)			TIME_AFTER(b,a)


#define COMMON_STR_LEN											8
#define COMMON_STR0_LEN										16
#define COMMON_STR1_LEN										32
#define COMMON_STR2_LEN										64
#define COMMON_STR3_LEN										128
#define COMMON_STR4_LEN										256
#define COMMON_STR5_LEN										384
#define COMMON_STR6_LEN										512
#define COMMON_STR7_LEN										1024
#define COMMON_STR8_LEN										(1024*2)
#define COMMON_STR9_LEN										(1024*4)
#define COMMON_STR10_LEN										(1024*8)
#define COMMON_STR11_LEN										(1024*16)
#define COMMON_STR12_LEN										(1024*32)
#define COMMON_STR13_LEN										(1024*64)
#define COMMON_IP_LEN											20
#define SIM_LINUX_STR1_LEN									(1024*4)
#define SIM_LINUX_STR2_LEN									1024*2
#define SIM_LINUX_STR3_LEN									1024
#define SIM_LINUX_STR4_LEN									512
#define SIM_LINUX_STR5_LEN									64


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __PLATFORM_H__
