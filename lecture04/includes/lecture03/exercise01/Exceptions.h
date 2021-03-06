//
// Created by Kalle Møller on 05/09/16.
//

#ifndef LECTURE03_EXERCISE01_EXCEPTIONS_H
#define LECTURE03_EXERCISE01_EXCEPTIONS_H

#include <utility>
#include <cstring>
#include <memory>
#include <algorithm>

namespace exercise01_1_2 {

    template <typename T, int N>
    class MyArray
    {

    public:
    T& operator []( size_t i) {
        return data_[i];
    }

    private:
        T data_[N];
    };

    /* Using */
    void fMyArray() {
        MyArray <int , 10> my;
        int t = 0;
        my[5] = t;
    }

    template <typename T>
    class MyVector {
    public:
    MyVector(size_t capacity) : capacity_((capacity == 0 ? 1 : capacity)), count_ (0), data_(new T[capacity]) {}

    bool full() const { return (count_ == capacity_); }

    void push_back(const T& oneMore) {
        if(full()) {
            capacity_ *= 2;
            T* newData = new T[capacity_ ];
            std::copy(data_ , data_+count_ , newData);
            std::swap(data_ , newData);
            delete [] newData;
        }

        data_[count_] = oneMore;
        ++count_;
    }
    private:
        size_t capacity_;
        size_t count_;
        T* data_;
    };

    /* Using */
    void fMyVector(){
        MyVector <int> my(20);
        int t = 0;
        my.push_back(t);
    }

    class String {
    public:

    String () : s_(nullptr) {}

    String(const char* s) : s_(new char[strlen(s)+1]) {
        std::strcpy(s_ , s);
    }

    String(const String& other) : s_(new char[strlen(other.s_)+1])
    {
        std::strcpy(s_ , other.s_);
    }

    String& operator =( const String& other) {
        //delete [] s_;
        //s_ = new char[strlen(other.s_)+1];
        //std:: strcpy(s_ , other.s_);
        String temp(other);
        std::swap(this->s_, temp.s_); //Kalle synes det her er grimt!
        return *this;
    }

    ~String () {
        delete [] s_;
    }
    private:
        char* s_;
    };

    /* Using */
    void fString()
    {
        String s("Hello world");
        String aCopy(s);
        s = "Hello girls";
    }

    struct Key{
        bool isValid(){
            return true;
        };

        int id(){
            return 5;
        }
    };

    struct Blob{};

    struct InvalidKey{
        InvalidKey(int id){}
    };

    class DataSet {
    public:
    DataSet(Key* key , Blob* blob): key_(key), blob_(blob) {
        if(!key ->isValid()) {
            delete key_;
            delete blob_;
            throw InvalidKey(key->id());
        }

    }

    void overWrite(const Key* key , const Blob* blob) {
        *key_ = *key;
        *blob_ = *blob;
    }

    ~DataSet () {
        delete key_;
        delete blob_;
    }

    private:
        Key* key_;
        Blob* blob_;
    };

    /* Using */
  /*  void f() {
        DataSet ds(new Key , new Blob);
        {
        Key k(getKeyValue ());
        Blob b(fetchDBBlobByKey(k));
        ds.overWrite (&k, &b);
        }
    }*/
}

namespace exercise01_3 {

    template <typename T>
    class MyVector {
    public:
        explicit MyVector(size_t capacity = 10) : capacity_(capacity), count_(0), data_(new T[capacity_]) {}

        MyVector(const MyVector& other) : capacity_(other.capacity_), count_(other.count_) {
            std::unique_ptr<T[]> temp(new T[other.capacity_]);
            std::copy(other.begin(), other.end(), temp.get());
            data_ = std::move(temp);
        }

        MyVector(const MyVector&& other) noexcept : capacity_(std::move(other.capacity_)), count_(std::move(other.count_)), data_(std::move(other.data_)) {}

        MyVector& operator=(const MyVector& other){
            MyVector<T> copy(other);
            std::swap(data_, copy.data_);
            std::swap(capacity_, copy.capacity_);
            std::swap(count_, copy.count_);
            return *this;
        }

        ~MyVector() {
        }

        size_t size() const {
            return capacity_;
        }

        size_t count() const {
            return count_;
        }

        T& back() {
            return data_.get()[count_ - 1];
        }

        void push_back(const T& t ) {
            if(count_ == capacity_){
                Resize();
            }
            data_.get()[count_] = t;
            ++count_;
        }

        void pop_back(){
            --count_;
        }

        void insert(const T& t, size_t n) {
            if(n > count_){
                throw std::out_of_range("n size is bigger than count.");
            }

            data_.get()[n] = t;
        }

        T* begin() const {
            return data_.get();
        }

        T* end() const {
            return data_.get() + count_;
        }

        T& operator []( size_t i ){
            return data_.get()[i];
        }

    private:

        void Resize(){
            capacity_ *= 2;
            std::unique_ptr<T[]> temp(new T[capacity_]);
            std::copy(data_.get(), data_.get() + count_, temp.get()); //Notice that the elements should be copyable.
            std::swap(data_, temp);
        }

        size_t capacity_;
        size_t count_;
        std::unique_ptr<T[]> data_;
        //T* data_E; /* Contains the actual elements - data on the heap */
    };
}
#endif //LECTURE02_EXERCISE01_SHAREDPTR_H
