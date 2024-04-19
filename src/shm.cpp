
#include <string>
#include <utility>

#include "libipc/shm.h"

#include "utility/pimpl.h"
#include "utility/log.h"
#include "memory/resource.h"

namespace ipc {
namespace shm {

IPC_EXPORT shm_seg::id_t         acquire(char const * name, std::size_t size, unsigned mode = shm_seg::create | shm_seg::open);
IPC_EXPORT void *       get_mem( shm_seg::id_t id, std::size_t * size);
IPC_EXPORT std::int32_t release( shm_seg::id_t id);
IPC_EXPORT void         remove ( shm_seg::id_t id);
IPC_EXPORT void         remove (char const * name);
IPC_EXPORT std::int32_t get_ref( shm_seg::id_t id);
IPC_EXPORT void sub_ref( shm_seg::id_t id);

class shm_seg::handle_ : public pimpl<handle_> {
public:
    id_t id_ = nullptr;
    void*     m_  = nullptr;

    ipc::string n_;
    std::size_t s_ = 0;
};

shm_seg::shm_seg()
    : p_(p_->make()) {
}

shm_seg::shm_seg(char const * name, std::size_t size, unsigned mode)
    : shm_seg() {
    acquire(name, size, mode);
}

shm_seg::shm_seg(shm_seg&& rhs)
    : shm_seg() {
    swap(rhs);
}

shm_seg::~shm_seg() {
    release();
    p_->clear();
}

void shm_seg::swap(shm_seg& rhs) {
    std::swap(p_, rhs.p_);
}

shm_seg& shm_seg::operator=(shm_seg rhs) {
    swap(rhs);
    return *this;
}

bool shm_seg::valid() const noexcept {
    return impl(p_)->m_ != nullptr;
}

std::size_t shm_seg::size() const noexcept {
    return impl(p_)->s_;
}

char const * shm_seg::name() const noexcept {
    return impl(p_)->n_.c_str();
}

std::int32_t shm_seg::ref() const noexcept {
    return shm::get_ref(impl(p_)->id_);
}

void shm_seg::sub_ref() noexcept {
    shm::sub_ref(impl(p_)->id_);
}

bool shm_seg::acquire(char const * name, std::size_t size, unsigned mode) {
    if (!is_valid_string(name)) {
        ipc::error("fail acquire: name is empty\n");
        return false;
    }
    if (size == 0) {
        ipc::error("fail acquire: size is 0\n");
        return false;
    }
    release();
    impl(p_)->n_  = name;
    impl(p_)->id_ = shm::acquire(name, size, mode);
    impl(p_)->m_  = shm::get_mem(impl(p_)->id_, &(impl(p_)->s_));
    return valid();
}

std::int32_t shm_seg::release() {
    if (impl(p_)->id_ == nullptr) return -1;
    return shm::release(detach());
}

void* shm_seg::get_ptr() const {
    return impl(p_)->m_;
}

void shm_seg::attach(id_t id) {
    if (id == nullptr) return;
    release();
    impl(p_)->id_ = id;
    impl(p_)->m_  = shm::get_mem(impl(p_)->id_, &(impl(p_)->s_));
}

shm_seg::id_t shm_seg::detach() {
    auto old = impl(p_)->id_;
    impl(p_)->id_ = nullptr;
    impl(p_)->m_  = nullptr;
    impl(p_)->s_  = 0;
    impl(p_)->n_.clear();
    return old;
}

} // namespace shm
} // namespace ipc
