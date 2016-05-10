// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include <utility>
#include "jsonArray.h"
#include "jsonValue.h"
#include "gtest/gtest.h"

using jsonat::Array;

TEST(jsonArray, Initialization) {
	Array a;
	Array b = {123, "123", a, 3.14, {}};
	Array c(a);
	Array d = {b};
	EXPECT_EQ(d.size(), size_t(1));
	Array e = Array({b});
	EXPECT_EQ(e, d);
}

TEST(jsonArray, AssignmentOperation) {
	size_t scale = 12345678;
	Array arr1(scale);
	EXPECT_EQ(arr1.size(), scale);
	Array arr2;
	// arr2 = arr1; // slow
	arr2 = std::move(arr1); // fast
	Array arr3 = std::move(arr2); 
	EXPECT_EQ(arr3.size(), scale);
}