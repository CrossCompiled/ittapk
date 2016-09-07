//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE01_SHAREDPTR_H
#define LECTURE01_SHAREDPTR_H

#include <utility>

namespace exercise02 {

    template <typename T>
    class SharedPtr {
    public:

        SharedPtr(T* t) : ptr(t), count(new size_t(1)) {}

        SharedPtr(const SharedPtr& other): ptr(other.ptr), count(other.count) {
            std::cout << "CopyConstructor" << std::endl;
            ++(*this->count);
        }

        SharedPtr(SharedPtr&& other) : ptr(std::move(other.ptr)), count(std::move(other.count)) {
            std::cout << "MoveConstructor" << std::endl;
            other.count = nullptr;
        }


        SharedPtr& operator=(SharedPtr&& other) {
            SharedPtr temp = std::move(*this);
            this->count = std::move(other.count);
            this->ptr = std::move(other.ptr);
            other.count = nullptr;
            return *this;
        }

        SharedPtr& operator=(const SharedPtr& other) {
            SharedPtr temp(other);
            std::swap(temp, *this);
            return *this;
        }

        explicit operator bool() const {
            return this->count != nullptr;
        }

        void Reset() {
            if(*this) {
                if (!--(*this->count)) {
                    delete this->ptr;
                    delete this->count;
                }
                this->count = nullptr;
            }
        }

        ~SharedPtr() {
            this->Reset();
        }

        T& operator*() {
            return *this->ptr;
        }

        T* operator->() {
            return this->ptr;
        }

        size_t Count() {
            return *this->count;
        }

    private:
        T* ptr;
        size_t* count;
    };
}

#endif //LECTURE01_SHAREDPTR_H
