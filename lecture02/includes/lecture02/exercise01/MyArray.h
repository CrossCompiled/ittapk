//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE02_EXERCISE01_SHAREDPTR_H
#define LECTURE02_EXERCISE01_SHAREDPTR_H

#include <utility>

namespace exercise01 {

    template<typename T, size_t N>
    class MyArray {

    public:
        MyArray() {}

        template<typename U>
        MyArray(const MyArray<U, N>& other) {
            MyArray<T, N> temp(other);
            std::swap(temp, *this);
            return *this;
        }

        template<typename U>
        MyArray(MyArray<U,N>&& other) {
            *this = std::move(other);
        }

        template<typename U>
        MyArray& operator=(MyArray<U, N>&& other) {
            auto dest = this->data;
            for(auto source=other.begin(); source != other.end(); ++source, ++dest) {
                *dest = std::move(*source);
            }
            return *this;
        }


        template<typename U>
        MyArray& operator=(const MyArray<U, N>& other) {
            MyArray<T, N> temp(other);
            std::swap(temp, *this);
            return *this;
        }

        void fill(const T& value) {
            memset(this->data, value, this->end() - this->begin());
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

    template<typename T, typename U>
    T* myfind(T* first, T* last, const U& v) {
        for(; first != last; ++first) {
            if (*first == v) {
                return first;
            }
        }
        return last;
    }


}
#endif //LECTURE02_EXERCISE01_SHAREDPTR_H
