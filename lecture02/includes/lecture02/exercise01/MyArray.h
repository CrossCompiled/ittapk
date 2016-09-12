//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE02_EXERCISE01_SHAREDPTR_H
#define LECTURE02_EXERCISE01_SHAREDPTR_H

#include <utility>

namespace exercise01 {

    template<typename T>
    class MyArray {

    public:
        MyArray() : MyArray(10) {}

        explicit MyArray(size_t size) : size_(size) {
            this->data = new T[this->size_];
            this->begin_ = &this->data;
            this->end_ = this->begin_ + this->size_;
        }

        ~MyArray() {
            delete this->data;
        };

        void fill(const T& value) {
            memset(this->data, value, this->begin() - this->end());
        }

        T* begin() const {
            return this->begin_;
        }

        T* end() const {
            return this->end_;

        }

        T &operator[](int i) const {
            return this->data[i];
        }

        T &operator[](int i) {
            return this->data[i];
        }

        size_t size() {}

    private:
        size_t size_;
        T* begin_;
        T* end_;
        T* data;
    };

}
#endif //LECTURE02_EXERCISE01_SHAREDPTR_H
