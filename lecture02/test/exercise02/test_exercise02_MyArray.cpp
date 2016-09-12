//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture02/exercise02/MyArray.h>



using namespace exercise02;

//region NormalConstructor

TEST (NormalConstructor, FillIt) {
    MyArray<int*, 50> uut;
    uut[0] = new int(10);
    EXPECT_EQ(10, *uut[0]);
    auto location = myfind(uut.begin(), uut.end(), 10);
    EXPECT_EQ(10, **location);
}

//endregion





