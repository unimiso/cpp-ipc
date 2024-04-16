
#include "platform/detail.h"
#if defined(IPC_OS_WINDOWS_)
#include "platform/win/shm_win.cpp"
#elif defined(IPC_OS_LINUX_) || defined(IPC_OS_QNX_)
#include "platform/posix/shm_posix.cpp"
#else/*IPC_OS*/
#   error "Unsupported platform."
#endif
