#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "lecture05/exercise01/product.h"

using namespace exercise01;

class NormalConstructor : public ::testing::Test {
protected:
    virtual void SetUp() {}
};

TEST_F (NormalConstructor, Initialization) {
	Product uut("TestItem", 10);

	ASSERT_THAT(uut.name(), "TestItem");
	ASSERT_THAT(uut.price(), 10);
	ASSERT_THAT(uut.sold(), 0);
}