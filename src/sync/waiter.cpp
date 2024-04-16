#include "waiter.h"

#include "platform/detail.h"
#if defined(IPC_OS_WINDOWS_)
#include "platform/win/mutex.h"
#elif defined(IPC_OS_LINUX_)
#include "platform/linux/mutex.h"
#elif defined(IPC_OS_QNX_)
#include "platform/posix/mutex.h"
#else/*IPC_OS*/
#   error "Unsupported platform."
#endif

namespace ipc {
namespace detail {

void waiter::init() {
    ipc::detail::sync::mutex::init();
}

} // namespace detail
} // namespace ipc
