
#include <stdio.h>
#include <stdlib.h>
#if defined(LINUX32)
#include <signal.h>
#endif

#include "platform.h"
#include "debug_trace.h"

#ifdef WIN32
#define GLOBAL static
#else
#define GLOBAL
#endif

GLOBAL int g_fDebugLog = 1;
GLOBAL char *g_chTempBuf = 0;


#if defined(LINUX32)
#include <execinfo.h>
//#define GOOGLE_COREDUMP
//#if defined(GOOGLE_COREDUMP)
//#include <google/coredumper.h> //WriteCoreDump  
//#endif // #if defined(GOOGLE_COREDUMP)
#endif // #if !defined(_WIN32)

void DebugBacktrace(int);

struct InitDebugTrace
{
	InitDebugTrace() { 
		g_fDebugLog = 0;
#if defined(LINUX32)

#if defined(OSX)
        g_fDebugLog = 1;
#else
		struct stat st;
		int result = 0;
		result = stat("/mnt/mtd/jdebug", &st);
		if (result >= 0) {
			g_fDebugLog = TRUE;
            fprintf(stderr, "find /mnt/mtd/jdebug, open debug. \n\n");
		}
#endif
        
#else
		g_fDebugLog = 1;
#endif

	}

	~InitDebugTrace() {
		if (g_chTempBuf) {
			free(g_chTempBuf);
			g_chTempBuf = NULL;
		}
	}
};
GLOBAL struct InitDebugTrace _InitDebugTrace;

// formatted output string
void dbg_trace(char *fmt, ...)
{
	if (g_fDebugLog)
	{
		int nTempBufLen = 2*1024;

		if (g_chTempBuf == NULL) {
			g_chTempBuf = (char *)malloc(nTempBufLen);
		}

		va_list argptr;
		va_start(argptr, fmt);

		//sprintf(g_chTempBuf, "[james] [%#x/%#x]", &g_chTempBuf, &g_fDebugLog);
		sprintf(g_chTempBuf, "[james] ");
		vsprintf(g_chTempBuf+strlen(g_chTempBuf), fmt, argptr);

		va_end(argptr);

		int nFmtLen = (int)strlen(g_chTempBuf);
		if (nFmtLen > nTempBufLen) {
			strcpy(g_chTempBuf, "??? [james] debug length too big. \n");
			return;
		}

		
		/*if (NULL != strstr(g_chTempBuf, "192.168.5.32") ||
			NULL != strstr(g_chTempBuf, "192.168.5.84") ||
			NULL != strstr(g_chTempBuf, "10.1.9.188")) 
		{
			
		}
		else {
			return;
		}*/


#if defined(_WIN32)
		OutputDebugString(g_chTempBuf);
#elif defined(_MAKE_LIB_ONVIF) /*defined(_GM8126) || defined(_GM8180)*/
		fprintf(stderr, g_chTempBuf);
#elif defined(_ITRON)
		strcat(g_chTempBuf, "\r\n");
		PRINTF(g_chTempBuf);
#elif defined(_ANDROID_LINUX)
		LOGI(g_chTempBuf);
#elif defined(_QT_SYMBIAN_DEF)
		qDebug(g_chTempBuf);
#else
		fprintf(stderr, g_chTempBuf);
		fflush(NULL);
#endif

	}
}

void DebugBacktrace(int signo)
{
#if defined(LINUX32)
#define SIZE 100
	void *array[SIZE];
	int size, i;
	char **strings;

	fprintf(stderr, "\n[james] Seqmentation fault: SIG:%d, %s, %ld.\n", signo, g_stream_debug_function_name, g_stream_debug_line);
    fprintf(stderr, "\n[james] Seqmentation fault: SIG:%d, %s, %ld.\n", signo, g_login_debug_function_name, g_login_debug_line);

/*#if defined(GOOGLE_COREDUMP)
	if (WriteCoreDump("/tmp/google_coredump.log") == 0) {
		fprintf(stderr, "success: WriteCoreDump to /tmp/google_coredump.log. \n");
	} 
	else {  
		fprintf(stderr, "failure: WriteCoreDump to /tmp/google_coredump.log. \n");
	}     

	sleep(3);
	exit(-1);//important, comment the line will lead to dead loop signal  
	return;
#endif // #if defined(GOOGLE_COREDUMP)*/

	size = backtrace(array, SIZE);
	fprintf(stderr, "Backtrace (%d deep): \n", size);
	strings = backtrace_symbols(array, size);
	for (i=0; i < size; i++)
		fprintf(stderr, "%d: %s\n", i, strings[i]);
	free(strings);

    sleep(1);
	exit(-1);
#endif // #if defined(LINUX32) && !defined(_MAKE_LIB_ONVIF)
}