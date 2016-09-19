#ifndef LECTURE02_EXERCISE03_MYARRAY_H
#define LECTURE02_EXERCISE03_MYARRAY_H

#include <utility>
#include <type_traits>

namespace exercise02  {
		template <typename T>
		class MyArrayIterator : public std::iterator<std::random_access_iterator_tag, T> {
		private:
				T* ptr_;
		public:
				MyArrayIterator() : ptr_(nullptr) {}
				MyArrayIterator(T* ptr) : ptr_(ptr) {}

				MyArrayIterator(const MyArrayIterator<T>& it) : ptr_(it.ptr_) {}

				MyArrayIterator operator++() { ++ptr_; return *this; }
				MyArrayIterator operator++(int) { MyArrayIterator tmp(*this); operator++(); return tmp; }

				int operator-(const MyArrayIterator<T>& it) { return ptr_ - it.ptr_; }

				bool operator==(const MyArrayIterator& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const MyArrayIterator& rhs) { return ptr_ != rhs.ptr_; }

				T& operator*() { return *ptr_; }
		};

		template<typename T, size_t N>
		class MyArray {

		public:
				typedef T value_type;

				MyArray() {}

				template<typename U, size_t M>
				explicit MyArray(const MyArray<U, M>& other) { std::copy(other.begin(), other.end(), this->data);	}

				template<typename U, size_t M>
				MyArray(MyArray<U, M>&& other) { *this = std::move(other); }

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

				void fill(const T& value) { std::fill(this->begin(), this->end(), value); }

				MyArrayIterator<T> begin() { return MyArrayIterator<T>(data); }
				MyArrayIterator<const T> begin() const { return MyArrayIterator<T>(data);	}

				MyArrayIterator<T> end() { return MyArrayIterator<T>(data + N);	}
				MyArrayIterator<const T> end() const { return MyArrayIterator<T>(data + N);	}

				T& operator[](int i) const { return this->data[i]; }
				T& operator[](int i) { return this->data[i]; }

				size_t size() const {	return N;	}

		private:
				T data[N];
		};
}
#endif //LECTURE02_EXERCISE03_MYARRAY_H