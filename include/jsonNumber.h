// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.


#ifndef JSON_NUMBER_H
#define JSON_NUMBER_H

#include <cmath> // for modf
#include <sstream>
#include <string>
#include <cassert>
#include <ios>

namespace jsonat {

typedef double Number;

inline bool isInteger(const Number& pt) {
	double tmp;
	return modf(double(pt), &tmp) == double(0);
}

inline void toString(std::ostream& os, const Number& pt) {
	
	// if is integer, then convert to long long and output
	if (isInteger(pt)) {
		if (pt >= 1e16) {
			os.precision(16);
			os << std::scientific << double(pt);
		} else {
			os.precision(0);
			os << std::fixed << std::showpoint << std::noshowpoint << double(pt);
		}
		
	} else {
		
		
		
		if (pt < 1e-6) {
			
			os.precision(16);
			os << std::scientific << double(pt);
			
		} else {
			
			std::stringstream ss;
			std::string str;
			
			ss.precision(13);
			ss << std::fixed << double(pt);
			ss >> str;
			
			size_t pos = str.find_last_not_of('0');
			assert(pos != std::string::npos);
			if (pos + 1 < str.length()) str.erase(pos + 1); // has extra trailing zeros
			
			os << str;
		}
		
		
	}
}

} // namespace Json


#endif // JSON_NUMBER_H