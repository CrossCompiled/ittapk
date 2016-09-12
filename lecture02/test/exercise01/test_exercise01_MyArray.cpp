//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture02/exercise01/MyArray.h>



using namespace exercise01;

//region NormalConstructor

TEST (NormalConstructor, FillIt) {
    MyArray<char, 50> uut;
    uut.fill('Z');
    for(size_t i=0; i < 50; ++i){
        EXPECT_EQ('Z', uut[i]);
    }
    EXPECT_EQ(&uut[0], uut.begin());
    EXPECT_EQ(&uut[50], uut.end());

    uut[10] = 'A';
    EXPECT_EQ('Z', uut[9]);
    EXPECT_EQ('A', uut[10]);
    EXPECT_EQ('Z', uut[11]);

}

//endregion

//region Find

TEST (FindMethod, FindSingle) {
    MyArray<char, 50> uut;
    uut.fill('Z');
    uut[30] = 'A';
    char* location = myfind(uut.begin(), uut.end(), 'A');
    EXPECT_EQ('A', *location);
    EXPECT_EQ(30, location - uut.begin());

}

TEST (FindMethod, FindImplicit) {
    MyArray<double, 50> uut;
    uut.fill(1.0);
    uut[10] = 3;
    double* location = myfind(uut.begin(), uut.end(), 3);
    EXPECT_EQ(3, *location);
    EXPECT_EQ(10, location - uut.begin());

}

//endregion

//region CopyConst

TEST (CopyConst, CopyConstImplicit) {
    MyArray<int, 50> uut1;
    MyArray<double, 50> uut2;

    uut1.fill(3);
    uut2 = uut1;

    for(size_t i=0; i < 50; ++i){
        EXPECT_EQ(3, uut2[i]);
    }

}

TEST (CopyConst, CopyAssignImplicit) {
    MyArray<int, 50> uut1;
    uut1.fill(3);

    MyArray<double, 50> uut2(uut1);

    for(size_t i=0; i < 50; ++i){
        EXPECT_EQ(3, uut2[i]);
    }

}

TEST (CopyConst, DifferentSize) {
    MyArray<int, 50> uut1;
    uut1.fill(3);

    MyArray<double, 100> uut2(uut1);

    for(size_t i=0; i < 50; ++i){
        EXPECT_EQ(3, uut2[i]);
    }

}



//endregion



