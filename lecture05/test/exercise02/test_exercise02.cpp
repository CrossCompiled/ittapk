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

TEST_F (NormalConstructor, iterator) {
	MyArray<int, 5> uut;

	uut[0] = 0;
	uut[1] = 1;
	uut[2] = 2;
	uut[3] = 3;
	uut[4] = 4;

	auto it = uut.begin();
	ASSERT_THAT(it[3], 3);

}