#ifndef LECTURE02_EXERCISE03_MYARRAY_H
#define LECTURE02_EXERCISE03_MYARRAY_H

#include <utility>
#include <type_traits>

namespace exercise02  {
		template<typename T, size_t N, class A = std::allocator<T>>
		class MyArray {
		public:
				typedef typename A::value_type value_type;

				class iterator {
				public:
						typedef std::random_access_iterator_tag iterator_category;
						typedef typename A::difference_type difference_type;
						typedef typename A::value_type value_type;
						typedef typename A::reference reference;
						typedef typename A::pointer pointer;

						iterator() : ptr_(T()) {}
						iterator(T* ptr) : ptr_(ptr) {}

						iterator(const iterator& it) : ptr_(it.ptr_) {}

						iterator& operator=(iterator& it) { ptr_ = it.ptr_; return this; }

						iterator& operator++() { ++ptr_; return *this; }
						iterator operator++(int) { return iterator(ptr_++); }
						iterator& operator--() { --ptr_; return *this; }
						iterator operator--(int) { return iterator(ptr_--); }

						iterator& operator+=(const difference_type& i) { ptr_ += i; return *this; };
						iterator& operator-=(const difference_type& i) { ptr_ -= i; return *this; };

						iterator operator+(const difference_type i) const { return iterator(ptr_ + i); }
						iterator operator-(const difference_type i) const { return iterator(ptr_ - i); }
						difference_type operator-(const iterator& it) const { return ptr_ - it.ptr_; }

						reference operator*() { return *ptr_; }
						pointer operator->() {	return ptr_; }
						reference operator[](const difference_type i) const { return ptr_[i]; }

						bool operator==(const iterator& rhs) { return ptr_ == rhs.ptr_; }
						bool operator!=(const iterator& rhs) { return ptr_ != rhs.ptr_; }
						bool operator<(const iterator& rhs) { return ptr_ < rhs.ptr_; }
						bool operator<=(const iterator& rhs) { return ptr_ <= rhs.ptr_; }
						bool operator>(const iterator& rhs) { return ptr_ > rhs.ptr_; }
						bool operator>=(const iterator& rhs) { return ptr_ >= rhs.ptr_; }

				private:
						T* ptr_;
				};

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

				iterator begin() { return iterator(data); }
				//MyArrayIterator<const T> begin() const { return MyArrayIterator<T>(data);	}

				iterator end() { return iterator(data + N);	}
				//MyArrayIterator<const T> end() const { return MyArrayIterator<T>(data + N);	}

				T& operator[](int i) { return this->data[i]; }
				T& operator[](int i) const { return this->data[i]; }

				size_t size() const {	return N;	}

		private:
				T data[N];
		};
}
#endif //LECTURE02_EXERCISE03_MYARRAY_H