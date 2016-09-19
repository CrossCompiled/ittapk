//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture01/exercise02/SharedPtr.h>



using namespace exercise02;

class Dummy {
public:
    Dummy(size_t* n) : n(n) {}
    virtual ~Dummy() { ++(*n); }
    size_t* n;
};

//region UnsafeCall

void MyCall(SharedPtr<Dummy> sharedPtr) {
    // Doing nothing
}

TEST (NormalConstructor, ) {
    size_t status = 200;
    Dummy* value = new Dummy(&status);
    MyCall(value);
    EXPECT_EQ(201, status);
}

//endregion