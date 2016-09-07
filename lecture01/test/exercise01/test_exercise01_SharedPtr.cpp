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

//region NormalConstructor

class NormalConstructor : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->value = new Dummy(this->ORG_VALUE);
    }

    Dummy* value;
    const size_t ORG_VALUE = 200;
};

TEST_F (NormalConstructor, SameValue) {
    SharedPtr<Dummy> uut(this->value);
    EXPECT_EQ(this->ORG_VALUE, uut->n) << "Values doesn't match";
}

TEST_F (NormalConstructor, SameAddress) {
    SharedPtr<Dummy> uut(this->value);
    EXPECT_EQ(value, &(*uut)) << "Addresses doesn't match";
}

TEST_F (NormalConstructor, OnlyOneCopy) {
    SharedPtr<Dummy> uut(this->value);
    EXPECT_EQ(1, uut.Count()) << "There should only be one copy of the SharedPtr";
}

TEST_F (NormalConstructor, ShouldBeValid) {
    SharedPtr<Dummy> uut(this->value);
    EXPECT_TRUE((bool)uut) << "Uut should be true / valid";
}

//endregion

//region CopyConstructor

class CopyConstructor : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->value = new Dummy(this->ORG_VALUE);
    }

    Dummy* value;
    const size_t ORG_VALUE = 200;
};

TEST_F (CopyConstructor, SameValue) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(uut1);
    EXPECT_EQ(this->ORG_VALUE, uut1->n) << "Values doesn't match";
    EXPECT_EQ(this->ORG_VALUE, uut2->n) << "Values doesn't match";
}

TEST_F (CopyConstructor, SameAddress) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(uut1);
    EXPECT_EQ(value, &(*uut1)) << "Addresses doesn't match";
    EXPECT_EQ(value, &(*uut2)) << "Addresses doesn't match";
}

TEST_F (CopyConstructor, OnlyOneCopy) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(uut1);
    EXPECT_EQ(2, uut1.Count()) << "There should be two copies of the SharedPtr";
    EXPECT_EQ(2, uut2.Count()) << "There should be two copies of the SharedPtr";
}

TEST_F (CopyConstructor, ShouldBeValid) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(uut1);
    EXPECT_TRUE((bool)uut1) << "Uut should be true / valid";
    EXPECT_TRUE((bool)uut2) << "Uut should be true / valid";
}

//endregion

//region CopyAssignment

class CopyAssignment : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->value = new Dummy(this->ORG_VALUE);
    }

    Dummy* value;
    const size_t ORG_VALUE = 200;
};

TEST_F (CopyAssignment, SameValue) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(NULL);
    uut2 = uut1;
    EXPECT_EQ(this->ORG_VALUE, uut1->n) << "Values doesn't match";
    EXPECT_EQ(this->ORG_VALUE, uut2->n) << "Values doesn't match";
}

TEST_F (CopyAssignment, SameAddress) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(NULL);
    uut2 = uut1;
    EXPECT_EQ(value, &(*uut1)) << "Addresses doesn't match";
    EXPECT_EQ(value, &(*uut2)) << "Addresses doesn't match";
}

TEST_F (CopyAssignment, TwoCopies) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(NULL);
    uut2 = uut1;
    EXPECT_EQ(2, uut1.Count()) << "There should be two copies of the SharedPtr";
    EXPECT_EQ(2, uut2.Count()) << "There should be two copies of the SharedPtr";
}

TEST_F (CopyAssignment, ShouldBeValid) {
    SharedPtr<Dummy> uut1(this->value);
    SharedPtr<Dummy> uut2(NULL);
    uut2 = uut1;
    EXPECT_TRUE((bool)uut1) << "Uut should be true / valid";
    EXPECT_TRUE((bool)uut2) << "Uut should be true / valid";
}



//endregion



//region NormalDestructor

class NormalDestructor : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->value = new Dummy(this->ORG_VALUE);
    }

    Dummy* value;
    const size_t ORG_VALUE = 200;
};

TEST_F (NormalDestructor, OutOfScope) {
    {
        SharedPtr<Dummy> uut(this->value);
    }
    EXPECT_DEATH(delete(this->value), "");
}

TEST_F (NormalDestructor, OutOfScopeAfterReset) {
    {
        SharedPtr<Dummy> uut(value);
        uut.Reset();
    }
    EXPECT_DEATH(delete(this->value), "");
}

TEST_F (NormalDestructor, SingleOfTwoOutOfScope) {
    SharedPtr<Dummy> uut1(value);
    {
        SharedPtr<Dummy> uut2(uut1);
        EXPECT_EQ(2, uut1.Count()) << "There should be two copies of the SharedPtr";
    }
    EXPECT_TRUE((bool)uut1);
    EXPECT_EQ(1, uut1.Count()) << "There should only be one copy left of the SharedPtr";
}

TEST_F (NormalDestructor, TwoOfTwoOutOfScope) {

    {
        SharedPtr<Dummy> uut1(value);
        SharedPtr<Dummy> uut2(uut1);
    }
    EXPECT_DEATH(delete(this->value), "");
}

TEST_F (NormalDestructor, OldPointerShouldDieOnAssignment) {
    SharedPtr<Dummy> uut1(this->value);
    Dummy* other = new Dummy(this->ORG_VALUE);
    SharedPtr<Dummy> uut2(other);
    uut2 = uut1;
    EXPECT_DEATH(delete(other), "");
}

//endregion


//region ResetFunction

class ResetFunction : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->value = new Dummy(this->ORG_VALUE);
    }

    Dummy* value;
    const size_t ORG_VALUE = 200;
};

TEST_F (ResetFunction, IsInvalidAfterReset) {
        SharedPtr<Dummy> uut(this->value);
        uut.Reset();
        EXPECT_FALSE((bool)uut) << "Uut should be false / invalid";
}

//endregion