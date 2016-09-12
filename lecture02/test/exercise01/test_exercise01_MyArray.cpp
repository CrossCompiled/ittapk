//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture02/exercise01/MyArray.h>



using namespace exercise01;

//region NormalConstructor

class NormalConstructor : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->size = 200;
    }

    size_t size;
};

TEST_F (NormalConstructor, FillIt) {
    EXPECT_EQ(1,1);
}

//endregion

