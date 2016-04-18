#include "jsonBoolen.h"
#include "gtest/gtest.h"

TEST(jsonBoolen, Initialization) {
	using jsonat::Boolen;
	Boolen a = false;
	EXPECT_EQ(a, Boolen(0));
	bool aa = false;
	EXPECT_EQ(a, aa);
	aa = 0;
	EXPECT_EQ(a, aa);
	aa = true;
	EXPECT_NE(a, aa);
	aa = 1;
	EXPECT_NE(a, aa);
}

TEST(jsonBoolen, Operation) {
	using jsonat::Boolen;
	Boolen a = 0;
	a |= 1;
	EXPECT_EQ(a, true);
	EXPECT_TRUE(a);
	a &= 0;
	EXPECT_FALSE(a);
}

TEST(jsonBoolen, Output) {
	using jsonat::Boolen;
}


