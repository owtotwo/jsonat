// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include <sstream>
#include "jsonString.h"
#include "gtest/gtest.h"

using jsonat::String;

TEST(jsonString, RelationalOperation) {
	String s("abc"), s_tmp(s);
	EXPECT_EQ(s, "abc");
	EXPECT_EQ("abc", s);
	EXPECT_EQ(s, std::string("abc"));
	EXPECT_EQ(std::string("abc"), s);
	EXPECT_NE(s, std::string("def"));
	EXPECT_EQ(s, s_tmp);
	EXPECT_EQ(s_tmp, s);
}

TEST(jsonString, Initialization) {
	String s1 = "c";
	String s2 = "c_str";
	String s3 = std::string("String");
	String s4 = s3;
	 
	EXPECT_EQ(s1, "c");
	EXPECT_EQ(s2, "c_str");
	EXPECT_EQ(s3, "String");
	EXPECT_NE(s3, "string");
	EXPECT_EQ(s4, s3);
	EXPECT_EQ(s4, "String");
}

TEST(jsonString, Operation) {
	String s1("abc"), s2("f");
	s2 = s1 + ',';
	s2 = s2 + " ";
	s2 += "def";
	EXPECT_EQ(s2, "abc, def");
}

TEST(jsonString, Output) {
	
	String s("hello world\n");
	std::ostringstream sout;
	sout << s;
	
	std::string tmp = "\"hello world\\n\"";
	
	EXPECT_EQ(sout.str(), tmp);
}