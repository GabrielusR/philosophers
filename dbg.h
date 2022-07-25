#ifndef _DBG_H_
#define _DBG_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>	

	#define STR_ERRNO() (errno == 0 ? "None" : strerror(errno))


	#define LOG_ERR(M, ...) fprintf(stderr, \
			"[ERROR] (%s:%d: errno: %s) " M "\n",\
			__FILE__, __LINE__, STR_ERRNO(), ##__VA_ARGS__)

	#define LOG_WARN(M, ...) fprintf(stderr, \
			"[WARN] (%s:%d: errno: %s) " M "\n",\
			__FILE__, __LINE__, STR_ERRNO(), ##__VA_ARGS__)

	#define LOG_INFO(M, ...) fprintf(stderr, \
			"[INFO] (%s:%d: errno: %s) " M "\n",\
			__FILE__, __LINE__, STR_ERRNO(), ##__VA_ARGS__)


	#define CHECK(A, M, ...) if(!(A)) {\
		LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }

	#define CHECK_MEM(A) CHECK(A, "Out of memory.")
	
	#define SENTINEL(M, ...) { LOG_ERR(M, ##__VA_ARGS__);\
		errno=0; goto error; }


	#ifdef NDEBUG
		#define DEBUG(M, ...)
	#else
		#define DEBUG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
				__FILE__, __LINE__, ##__VA_ARGS__)
	#endif

	#define CHECK_DEBUG(A, M, ...) if(!(A)) { DEBUG(M, ##__VA_ARGS__);\
		errno=0; goto error; }
#endif
