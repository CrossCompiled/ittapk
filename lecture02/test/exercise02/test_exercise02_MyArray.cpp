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
    int y = 10;
    uut.fill(&y);
    EXPECT_EQ(1, uut.flaf());
}

//endregion





