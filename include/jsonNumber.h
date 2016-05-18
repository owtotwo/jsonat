// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.


#ifndef JSON_NUMBER_H
#define JSON_NUMBER_H

#include <cmath> // for modf
#include <sstream>
#include <string>

namespace jsonat {

typedef double Number;

inline bool isInteger(const Number& pt) {
	return modf(double(pt), static_cast<double*>(nullptr)) == double(0);
}

inline void toString(std::ostream& os, const Number& pt) {
	// if is integer, then convert to long long and output
	if (isInteger(pt)) {
		os << static_cast<long long>(pt);
	} else {
		std::stringstream ss;
		std::string str;
		ss.precision(15);
		ss << std::fixed << pt;
		ss >> str;
		os << str.erase(str.find_last_not_of('0') + 1);
	}
}

} // namespace Json


#endif // JSON_NUMBER_H