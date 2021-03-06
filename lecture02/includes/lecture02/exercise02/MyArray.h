//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE02_EXERCISE02_MYARRAY_H
#define LECTURE02_EXERCISE02_MYARRAY_H

#include <utility>
#include <type_traits>

namespace exercise02 {



    template<typename T, size_t N>
    class MyArray {

    public:
        MyArray() {}

        template<typename U, size_t M>
        explicit MyArray(const MyArray<U, M>& other) {
            std::copy(other.begin(), other.end(), this->data);
        }

        template<typename U, size_t M>
        MyArray(MyArray<U,M>&& other) {
            *this = std::move(other);
        }

        template<typename U, size_t M>
        MyArray& operator=(MyArray<U, M>&& other) {
            std::move(other.begin(), other.end(), this->data);
            return *this;
        }


        template<typename U, size_t M>
        MyArray& operator=(const MyArray<U, M>& other) {
            MyArray<T, M> temp(other);
            std::swap(temp, *this);
            return *this;
        }

        void fill(const T& value) {
            std::fill(this->begin(), this->end(), value);
        }

        T* begin() {
            return this->data;
        }

        T const * begin() const {
            return this->data;
        }

        T* end() {
            return this->data + N;
        }

        T const * end() const {
            return this->data + N;
        }

        T &operator[](int i) const {
            return this->data[i];
        }

        T &operator[](int i) {
            return this->data[i];
        }

        size_t size() const {
            return N;
        }

    private:
        T data[N];
    };

    template <typename T, size_t N>
    class MyArray<T*, N> {
    public:
        MyArray() {
            std::fill(this->begin(), this->end(), nullptr);
        }

        T** begin() {
            return this->data;
        }

        T* const * begin() const {
            return this->data;
        }

        T** end() {
            return this->data + N;
        }

        T* const * end() const {
            return this->data + N;
        }

        T* &operator[](int i) const {
            return this->data[i];
        }

        T* &operator[](int i) {
            return this->data[i];
        }

        size_t size() const {
            return N;
        }

        ~MyArray() {
            std::for_each(this->begin(), this->end(), std::default_delete<T>());
        }

    private:
        T* data[N];

    };

    template<typename T, typename U>
    T* myfind(T* first, T* last, const U& v) {
        for(; first != last; ++first) {
            if (*first == v) {
                return first;
            }
        }
        return last;
    }

    template<typename T, typename U>
    T** myfind(T** first, T** last, const U& v) {
        for(; first != last; ++first) {
            if (**first == v) {
                return first;
            }
        }
        return last;
    }


}
#endif //LECTURE02_EXERCISE01_MYARRAY_H
