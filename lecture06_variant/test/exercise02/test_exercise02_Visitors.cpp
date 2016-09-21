//
// Created by kaspersk on 9/19/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lecture06_variant/exercise02/Visitor.h>
#include <boost/variant.hpp>


using namespace exercise02;

TEST(Visitor, IntVisit){

    boost::variant<int, double, char> NobodyVisitsMe(10);

    auto gotThis = boost::apply_visitor(ICanVisit(), NobodyVisitsMe);

    EXPECT_EQ(gotThis, "This guy is an integer: 10");

}

TEST(Visitor, DoubleVisit){

    boost::variant<int, double, char> NobodyVisitsMe(2.2);

    auto gotThis = boost::apply_visitor(ICanVisit(), NobodyVisitsMe);

    EXPECT_EQ(gotThis, "This guy is an double: 2.2000000000000002");

}

TEST(Visitor, CharVisit){

boost::variant<int, double, char> NobodyVisitsMe('a');

auto gotThis = boost::apply_visitor(ICanVisit(), NobodyVisitsMe);

EXPECT_EQ(gotThis, "This guy is a char: a");

}

//class Dummy {
//public:
//    Dummy(size_t n) : n(n) {}
//    virtual ~Dummy() {}
//    size_t n;
//};
//
//class Dummier: public Dummy {
//public:
//    Dummier(size_t n) : Dummy(n) {}
//};
//
////region CompareFunction
//
//class CompareFunction : public ::testing::Test {
//protected:
//    virtual void SetUp() {
//        this->value = new Dummy(this->ORG_VALUE);
//    }
//
//    Dummy* value;
//    const size_t ORG_VALUE = 200;
//};
//
//TEST_F (CompareFunction, CompareTwoSharedPtr) {
//    SharedPtr<Dummy> uut1(this->value);
//    SharedPtr<Dummy> uut2(uut1);
//
//    EXPECT_EQ(uut1, uut2);
//    EXPECT_TRUE(uut2==uut1);
//    EXPECT_NE(&uut1, &uut2);
//}
//
//TEST_F (CompareFunction, CompareTwoDifferentSharedPtr) {
//    SharedPtr<Dummy> uut1(this->value);
//    SharedPtr<Dummy> uut2(new Dummy(this->value->n+1));
//
//    EXPECT_NE(uut1, uut2);
//    EXPECT_TRUE(uut2!=uut1);
//    EXPECT_NE(&uut1, &uut2);
//}
//
//TEST_F (CompareFunction, CompareSharedPtrWithValue) {
//    Dummier* value = new Dummier(300);
//    SharedPtr<Dummier> uut1(value);
//
//    EXPECT_EQ(uut1, value);
//    EXPECT_EQ(value, uut1);
//
//    EXPECT_TRUE(value==uut1);
//    EXPECT_TRUE(uut1==value);
//}
//
//TEST_F (CompareFunction, CompareSharedPtrWithInheritance) {
//    Dummier* value = new Dummier(300);
//    SharedPtr<Dummier> uut1(value);
//    SharedPtr<Dummy> uut2(uut1);
//
//    EXPECT_EQ(uut1, uut2);
//    EXPECT_EQ(uut2, uut1);
//
//    EXPECT_TRUE(uut2==uut1);
//    EXPECT_TRUE(uut1==uut2);
//}
//
//TEST_F (CompareFunction, CompareSharedPtrWithInheritanceDifferent) {
//    Dummier* value1 = new Dummier(300);
//    Dummier* value2 = new Dummier(200);
//    SharedPtr<Dummier> uut1(value1);
//    SharedPtr<Dummy> uut2(value2);
//
//    EXPECT_NE(uut1, uut2);
//    EXPECT_NE(uut2, uut1);
//
//    EXPECT_TRUE(uut2!=uut1);
//    EXPECT_TRUE(uut1!=uut2);
//}

//endregion