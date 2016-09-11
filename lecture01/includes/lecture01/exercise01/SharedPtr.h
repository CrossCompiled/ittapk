//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE01_SHAREDPTR_H
#define LECTURE01_SHAREDPTR_H

#include <utility>

namespace exercise01 {

    template <typename T>
    class SharedPtr {
    public:

        explicit SharedPtr(T* t) : ptr(t), count(new size_t(1)) {}

        SharedPtr(const SharedPtr<T>& other): ptr(other.ptr), count(other.count) {
            if(*this) {
                ++(*this->count);
            }
        }

        template <typename U>
        SharedPtr(const SharedPtr<U>& other): ptr(other.GetPtr()), count(other.GetCount()) {
            if(*this) {
                ++(*this->count);
            }
        }

        size_t* GetCount() const {
            return this->count;
        }

        T* GetPtr() const {
            return this->ptr;
        }

        SharedPtr(SharedPtr&& other) : ptr(std::move(other.ptr)), count(std::move(other.count)) {
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

        // Compare SharedPtr to a pointer
        //
        // We compare the value of lhs.ptr with the pointer.
        // Thereby comparing two pointers as normal
        //
        template <typename U >
        friend bool operator== (const SharedPtr<T> lhs, const U* rhs) {
            return lhs.ptr == rhs;
        };

        // Compare pointer with SharedPtr
        //
        // Doing the lazy switch compare
        //
        template <typename U >
        friend bool operator== (const U* lhs, const SharedPtr<T> rhs) {
            return rhs == lhs;
        };

        // Compare two SharedPtr's
        //
        // We have access to lhs.ptr but not rhs.ptr
        // Therefor we compare rhs with lhs.ptr
        // This in turns calls the SharedPtr == pointer above
        // And now we have access to both pointers and can compare
        template <typename U >
        friend bool operator== (const SharedPtr<T> lhs, const SharedPtr<U> rhs) {
            return rhs == lhs.ptr;
        };


        // See compare
        template <typename U >
        friend bool operator!= (const SharedPtr<T> lhs, const SharedPtr<U> rhs) {
            return !(lhs == rhs);
        };

        // See compare
        template <typename U >
        friend bool operator!= (const SharedPtr<T> lhs, const U* rhs) {
            return !(lhs == rhs);
        };

        // See compare
        template <typename U >
        friend bool operator!= (const U* lhs, const SharedPtr<T> rhs) {
            return !(lhs == rhs);
        };

    private:
        T* ptr;
        size_t* count;
    };


}
#endif //LECTURE01_SHAREDPTR_H
