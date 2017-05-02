#include "platform.h"

#include "debug_trace.h"

/*
* for vs2015, replaced __iob_func with __acrt_iob_func.
*
*/
#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE *__cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE *__cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */

#ifdef WIN32
struct InitPlatform
{
	InitPlatform()
	{ 
		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD(2, 2);
		int err;
		err = WSAStartup(wVersionRequested, &wsaData);
	}
	~InitPlatform()
	{
		WSACleanup();
	}
} _InitPlatform;
#endif

#if defined(_ITRON)

/*
#if defined(_USE_EYMEM)
struct InitMem
{
	InitMem() { 
		init_memory_mgr();
		ey_memory_stat();
	}
	~InitMem() {
		end_memory_mgr();
	}
} _InitMem;
#endif // #if defined(_USE_EYMEM)
*/

void *calloc(size_t _NumOfElements, size_t _SizeOfElements)
{
	INT8U err;
	INT32U size = _NumOfElements*_SizeOfElements;
/*#if defined(_USE_EYMEM)
	return ey_malloc(size, 0);
#else*/
	return GLOBAL_ALLOC(size, &err);
//#endif // #if defined(_USE_EYMEM)
}

void *malloc(size_t _Size)
{
	INT8U err;
	//DEBUG_TRACE(CHECK_ACTION_DBG, ("#%d GLOBAL_ALLOC: _Size=%d. \n", __LINE__));
/*#if defined(_USE_EYMEM)
	return ey_malloc(size, 0);
#else*/
	return GLOBAL_ALLOC(_Size, &err);
//#endif // #if defined(_USE_EYMEM)
}

void free(void *_Memory)
{
/*#if defined(_USE_EYMEM)
	ey_free(_Memory, 0);
#else*/
	GLOBAL_FREE(_Memory);
//#endif // #if defined(_USE_EYMEM)
}


char *strdup(const char *s) 
{ 
/*#if defined(_USE_EYMEM)
	char *p  = ey_strdup(s, 0);
#else*/
	size_t len; 
	char *p; 
	if ( !s )
		return NULL;

	len = strlen(s); 
	p = malloc(len+1); 
	if (p && len)
	{ 
		memcpy (p, s, len); 
		p[len] = '\0';
	}
//#endif // #if defined(_USE_EYMEM)

	return p; 
}

/*
void *fopen(const char * _Filename, const char * _Mode)
{
	return 0;
}*/

void *operator new(size_t n)
{
	return malloc(n);
}

void *operator new[](size_t n)
{
	return malloc(n);
}

void operator delete(void *p)
{
	free(p);
}

void operator delete[](void *p)
{
	free(p);
}
#endif //_ITRON

/*
int strcasecmp(const char *s1, const char *s2)
{
	unsigned int i;
	unsigned char c1;
	unsigned char c2;

	for (i = 0; s1[i] && s2[i]; i++) {
		c1 = tolower((unsigned char)s1[i]);
		c2 = tolower((unsigned char)s2[i]);

		if (c1 < c2)
			return -1;
		else if (c1 > c2)
			return 1;
	}

	return (!s2[i] - !s1[i]);
}

int strncasecmp(const char *s1, const char *s2, int len)
{
	if (len <= 0)
		return 0;

	while (len-- != 0 && tolower(*s1) == tolower(*s2)) {
		if (len == 0 || *s1 == '\0' || *s2 == '\0')
			break;

		s1++;
		s2++;
	}

	return (tolower(*(unsigned char *)s1) - tolower(*(unsigned char *)s2));
}
*/

#if defined(_WIN32) || defined(_ITRON)
char *strtok_r(char *s, const char *delim, char **lasts)
{
	register char *spanp;
	register int c, sc;
	char *tok;

	if (s == NULL && (s = *lasts) == NULL)
		return (NULL);

	/*
	* Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	*/
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		*lasts = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	* Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	* Note that delim must have one NUL; we stop if we see that, too.
	*/
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					*(s-1) = 0;
				*lasts = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}
#endif // #if defined(_WIN32) || defined(_ITRON)