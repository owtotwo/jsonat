// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include <utility>
#include <initializer_list>
#include "jsonArray.h"
#include "jsonValue.h"
#include "gtest/gtest.h"

using jsonat::Array;

TEST(jsonArray, Initialization) {
	Array a;
	Array b = {123, "123", a, 3.14, {}};
	Array c(a);
	/* 
	   Array d = {b}; 
	   Clang++ has bug for this. GCC and VC will call Array(initializer_list<Value> il);
	   while Clang calls Array(const Array& pt), that is the copy constructor.
	   https://llvm.org/bugs/show_bug.cgi?id=23812
	*/
	Array d = {b, 15331120};
	EXPECT_EQ(d.size(), size_t(2));
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

TEST(jsonArray, OtherOperations) {
	Array arr = {1, 2, 3, 4, 5};
	jsonat::Value k = 0;
	for (auto x : arr) {
		++k;
		EXPECT_EQ(k, x);
	}
	EXPECT_EQ(arr[4], arr.size());
	EXPECT_EQ(1, arr[0]);
	EXPECT_EQ(short(2), arr[1]);
	EXPECT_EQ(arr[2], (unsigned long long)(arr[arr[2] - 2] + 1));
}