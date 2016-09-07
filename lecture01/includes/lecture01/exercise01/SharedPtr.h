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

        SharedPtr(T* t, size_t n) : ptr(t), count(new size_t(n)) {}

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

        bool operator==( const SharedPtr<T>& rhs ) const {
            return this->ptr == rhs.ptr;
        }

        bool operator!=( const SharedPtr<T>& rhs ) const {
            return !(*this == rhs);
        }

        template <typename U >
        friend bool operator== (const SharedPtr<T> lhs, const SharedPtr<U> rhs) {
            return rhs == lhs.ptr;
        };


        template <typename U >
        friend bool operator== (const SharedPtr<T> lhs, const U* rhs) {
            return lhs.ptr == rhs;
        };


        /*
        template <typename U >
        friend bool operator!= (const SharedPtr<T> lhs, const SharedPtr<U> rhs) {
            return !(rhs == lhs);
        };

        template <typename U >
        friend bool operator!= (const SharedPtr<T> lhs, const U* rhs) {
            return lhs.ptr != rhs;
        };
         */

    private:
        T* ptr;
        size_t* count;
    };

    /*
    template <typename T, typename U >
    bool operator==( const SharedPtr<T>& rhs, const SharedPtr<U>& lhs )
    {
        return rhs.ptr == lhs.ptr;
    }
     */


 //   template < typename T, typename U >


   // template < typename T, typename U >


}
#endif //LECTURE01_SHAREDPTR_H
