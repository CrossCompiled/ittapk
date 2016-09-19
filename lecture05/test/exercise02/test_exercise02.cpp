#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include "lecture05/exercise02/MyArray.h"

using namespace exercise02;

class NormalConstructor : public ::testing::Test {
protected:
		virtual void SetUp() {}
};

TEST_F (NormalConstructor, stdcopy) {
	MyArray<int, 5> uut;
	uut.fill(5);

	MyArray<int, 5> tmp;
	std::copy(uut.begin(), uut.end(), tmp.begin());

	ASSERT_THAT(tmp[0], 5);
	ASSERT_THAT(tmp[1], 5);
	ASSERT_THAT(tmp[2], 5);
	ASSERT_THAT(tmp[3], 5);
	ASSERT_THAT(tmp[4], 5);
}