
#include "platform/detail.h"
#if defined(IPC_OS_WINDOWS_)
#elif defined(IPC_OS_LINUX_)
#include "platform/linux/a0/err.c"
#include "platform/linux/a0/mtx.c"
#include "platform/linux/a0/strconv.c"
#include "platform/linux/a0/tid.c"
#include "platform/linux/a0/time.c"
#elif defined(IPC_OS_QNX_)
#else/*IPC_OS*/
#   error "Unsupported platform."
#endif
