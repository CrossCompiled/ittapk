//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture01/exercise02/SharedPtr.h>



using namespace exercise02;

class Dummy {
public:
    Dummy(size_t n) : n(n) {}
    virtual ~Dummy() {}
    size_t n;
};

//region UnsafeCall

void MyCall(SharedPtr<Dummy> sharedPtr) {
    // Doing nothing
}

TEST (NormalConstructor, ) {
    Dummy* value = new Dummy(200);
    MyCall(value);
    EXPECT_DEATH(delete value, "");
}

//endregion