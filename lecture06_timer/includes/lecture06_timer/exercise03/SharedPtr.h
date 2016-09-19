//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE01_EXERCISE03_SHAREDPTR_H
#define LECTURE01_EXERCISE03_SHAREDPTR_H

#include <utility>

namespace exercise03 {

    template <typename T>
    class HelperBase {
    public:
        virtual void operator()(T* t) {
            delete t;
        };
        virtual ~HelperBase() {}
    };

    template <typename T, typename U>
    class Helper: public HelperBase<T> {
    public:
        explicit Helper(U deleter) {
            this->deleter = deleter;
        }
        void operator()(T* t) {
            this->deleter(t);
        };
    private:
        U deleter;
    };

    template <typename T>
    class SharedPtr {
    public:

        explicit SharedPtr(T* t) : SharedPtr(t, new HelperBase<T>()) {}

        template <typename U>
        SharedPtr(T* t, U* deleter) : ptr(t), count(new size_t(1)), deleter(deleter) {}

        SharedPtr(const SharedPtr<T>& other): ptr(other.ptr), count(other.count), deleter(other.deleter) {
            if(*this) {
                ++(*this->count);
            }
        }

        template <typename U>
        SharedPtr(const SharedPtr<U>& other): ptr(other.GetPtr()), count(other.GetCount()), deleter(other.GetDeleter()) {
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

        HelperBase<T>* GetDeleter() const {
            return this->deleter;
        }

        SharedPtr(SharedPtr&& other) : ptr(std::move(other.ptr)), count(std::move(other.count)) {
            other.count = nullptr;
        }


        SharedPtr& operator=(SharedPtr&& other) {
            SharedPtr temp = std::move(*this);
            this->count = std::move(other.count);
            this->ptr = std::move(other.ptr);
            this->deleter = std::move(other.deleter);
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
                    (*this->deleter)(this->ptr);
                    delete this->count;
                    delete this->deleter;
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
        HelperBase<T>* deleter;
    };


}
#endif //LECTURE01_EXERCISE03_SHAREDPTR_H
