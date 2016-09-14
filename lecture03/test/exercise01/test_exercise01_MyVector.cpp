//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture03/exercise01/Exceptions.h>

using namespace exercise01_3;

//region NormalConstructor

class NormalConstructor : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->size = 200;
    }

    size_t size;
};

TEST_F (NormalConstructor, FillIt) {
    MyVector<int> uut(5);

    EXPECT_EQ(5, uut.size());
}


TEST_F (NormalConstructor, PushBack) {
    MyVector<int> uut(5);
    uut.push_back(1);
    EXPECT_EQ(2,uut.size());
}
//endregion

