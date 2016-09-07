//
// Created by Kalle Møller on 31/08/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture01/exercise01/SharedPtr.h>



using namespace exercise01;

class Dummy {
public:
    Dummy(size_t n) : n(n) {}
    virtual ~Dummy() {}
    size_t n;
};

class Dummier: public Dummy {
public:
    Dummier(size_t n) : Dummy(n) {}
};

//region CompareFunction

class CompareFunction : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->value = new Dummy(this->ORG_VALUE);
    }

    Dummy* value;
    const size_t ORG_VALUE = 200;
};

TEST_F (CompareFunction, CompareTwoSharedPtr) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(uut1);

    EXPECT_EQ(uut1, uut2);
    EXPECT_TRUE(uut2==uut1);
    EXPECT_NE(&uut1, &uut2);
}

TEST_F (CompareFunction, CompareTwoDifferentSharedPtr) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(new Dummy(this->value->n+1));

    EXPECT_NE(uut1, uut2);
    EXPECT_TRUE(uut2!=uut1);
    EXPECT_NE(&uut1, &uut2);
}

TEST_F (CompareFunction, CompareSharedPtrWithInheritance) {
    Dummier* value = new Dummier(300);
    SharedPtr<Dummier> uut1(value);
    SharedPtr<Dummy> uut2(uut1);

    EXPECT_TRUE((uut1 == value));
    EXPECT_EQ(uut1, uut2);
    EXPECT_TRUE(uut2==uut1);
}

//endregion