#include "jsonBoolean.h"
#include "gtest/gtest.h"

TEST(jsonBoolean, Initialization) {
	using jsonat::Boolean;
	Boolean a = false;
	EXPECT_EQ(a, Boolean(0));
	bool aa = false;
	EXPECT_EQ(a, aa);
	aa = 0;
	EXPECT_EQ(a, aa);
	aa = true;
	EXPECT_NE(a, aa);
	aa = 1;
	EXPECT_NE(a, aa);
}

TEST(jsonBoolean, Operation) {
	using jsonat::Boolean;
	Boolean a = 0;
	a |= 1;
	EXPECT_EQ(a, true);
	EXPECT_TRUE(a);
	a &= 0;
	EXPECT_FALSE(a);
}

TEST(jsonBoolean, Output) {
	using jsonat::Boolean;
}


