//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE02_EXERCISE03_SHAREDPTR_H
#define LECTURE02_EXERCISE03_SHAREDPTR_H

#include <utility>
#include <type_traits>

namespace exercise03 {



    template<typename T, size_t N>
    class MyArray {

    public:
        MyArray() {}

        template<typename U, size_t M>
        MyArray(const MyArray<U, M>& other) {
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

        typedef T value_type;


    private:
        T data[N];
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

    template<typename T>
    typename T::value_type myAccumalation(const T& u) {
        typename T::value_type m = typename T::value_type();

        for(auto first = u.begin(); first != u.end(); ++first)
        {
            m += *first;
        }

        return m;
    }


}
#endif //LECTURE02_EXERCISE03_SHAREDPTR_H
