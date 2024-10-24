#ifndef _RING_H_
#define _RING_H_
#include <vector>
template <typename T>
class Ring {
 private:
    size_t sz;
    size_t head = 0;
    size_t tail = 0;
    std::vector<T> buf;

 public:
    using RING_ERR_E = enum { ERR_OK = 0, ERR_FULL, ERR_EMPTY };
    Ring(size_t s) {
        this->sz = s;
        buf = std::vector<T>(this->sz);
    }
    ~Ring() = default;
    auto size() -> size_t { return sz; }
    auto push(T v) -> RING_ERR_E {
        RING_ERR_E ret = ERR_OK;
        if (this->isFull()) {
            ret = ERR_FULL;
        } else {
            this->buf[this->tail] = v;
            this->tail = (this->tail + 1) % this->sz;
        }
        return ret;
    }
    auto pop(T* v) -> RING_ERR_E {
        RING_ERR_E ret = ERR_OK;
        if (this->head == this->tail) {
            ret = ERR_EMPTY;
        } else {
            *v = this->buf[this->head];
            this->head = (this->head + 1) % this->sz;
        }
        return ret;
    }
    auto isEmpty() -> bool { return this->head == this->tail; }
    auto isFull() -> bool { return (this->tail + 1) % this->sz == this->head; }
    auto getN() -> size_t { return ((this->tail + this->sz) - this->head) % this->sz; }
};
#endif  // _RING_H_
