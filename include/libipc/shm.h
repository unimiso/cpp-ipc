#pragma once

#include <cstddef>
#include <cstdint>

#include "libipc/export.h"

namespace ipc::shm {

class IPC_EXPORT shm_seg
{
public:
    using id_t = void*;

    enum: unsigned
    {
        create = 0x01,
        open = 0x02
    };

public:
    shm_seg();
    shm_seg(char const * name, std::size_t size, unsigned mode = create | open);
    shm_seg(shm_seg&& rhs);

    ~shm_seg();

    void swap(shm_seg& rhs);
    shm_seg& operator=(shm_seg rhs);

    bool         valid() const noexcept;
    std::size_t  size () const noexcept;
    char const * name () const noexcept;

    std::int32_t ref() const noexcept;
    void sub_ref() noexcept;

    bool acquire(char const * name, std::size_t size, unsigned mode = create | open);
    std::int32_t release();

    void* get_ptr() const;

    void attach(id_t);
    id_t detach();

private:
    class handle_;
    handle_* p_;
};

}
