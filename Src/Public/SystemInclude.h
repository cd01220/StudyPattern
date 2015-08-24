
#ifndef _SystemInclude_h_
#define _SystemInclude_h_

#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

/*** OS header. ***/
#ifdef _WIN32
#   include <Winsock2.h>
#   ifdef __MINGW32__
#       include <unistd.h>
#   endif
#   define  __LITTLE_ENDIAN 1234
#   define  __BIG_ENDIAN    4321
#   define  __PDP_ENDIAN    3412
#   define  __BYTE_ORDER    __LITTLE_ENDIAN
#endif

#ifdef __linux
#   include <endian.h>
#   include <unistd.h>
#   include <syslog.h>
#   include <termios.h>
#   include <pthread.h>
#   include <sys/wait.h>   //for wait() function.
#   include <sys/resource.h>
#endif
#include <sys/stat.h>
/* for u_char, u_int ...  on windows platform,  u_char, u_int was defined
 * in <Winsock.h>.
 */
#include <sys/types.h>
#include <fcntl.h>

/*** C++ header. ***/
#if defined(__cplusplus)
#   include <cstdio>
#   include <cstdlib>
#   include <csignal>
#   include <cstddef>
#   include <cassert>
#   include <cstring>
#   include <iostream>
#   include <iomanip>
#   include <sstream>
#   include <fstream>
#   include <iterator>
#   include <list>
#   include <map>
#   include <vector>
#   include <set>
#   include <typeinfo>
#   include <functional>
#   include <algorithm>
#   include <memory>
#   include <climits>
#   include <cerrno>
#   ifdef _WIN32
#       include <cstdint>
#       include <system_error>
#   else
#       if GCC_VERSION > 40600
#           include <cstdint>
#           include <system_error>
#       else
#           include <stdint.h>
#           define nullptr NULL
#       endif
#   endif
#   define CxxBeginNameSpace(X) namespace X {
#   define CxxEndNameSpace }
#else
#   include <stddef.h>
#   include <signal.h>
#   include <stdio.h>
#   include <stdlib.h>
#   include <string.h>
#   include <assert.h>
#   include <errno.h>
#   include <limits.h>
#   ifdef __GNUC__
#       include <stdbool.h>
#   else
#       define BOOL  bool
#       define TRUE  true
#       define FALSE false
#   endif
#endif  //#if defined(__cplusplus)

typedef unsigned char uchar_t;
typedef unsigned int uint_t;

#endif /* _STDAFX_H_ */
