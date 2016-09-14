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

    EXPECT_EQ(0, uut.count());
}


TEST_F (NormalConstructor, PushBack) {
    MyVector<int> uut(5);
    uut.push_back(1);
    EXPECT_EQ(1,uut.count());
}

TEST_F (NormalConstructor, PushBack_Resize) {
    MyVector<int> uut(2);
    uut.push_back(1);
    uut.push_back(2);
    uut.push_back(3);

    EXPECT_EQ(4,uut.size());
}

TEST_F (NormalConstructor, PushBack_Resize_ElementsSurvive) {
    MyVector<int> uut(2);
    uut.push_back(1);
    uut.push_back(2);
    uut.push_back(3);

    EXPECT_EQ(1,uut[0]);
    EXPECT_EQ(2,uut[1]);
    EXPECT_EQ(3,uut[2]);
}
//endregion

