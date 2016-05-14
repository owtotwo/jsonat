// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include "Json.h"
#include "gtest/gtest.h"

using jsonat::Json;

TEST(jsonObject, Specialization) {
	Json j = Json::make_object();
	j["hello"] = "world";
	j["number"] = 2;
	std::cout << j << '\n';
	
}