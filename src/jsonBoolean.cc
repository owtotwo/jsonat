// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <ostream>
#include "jsonBoolean.h"

namespace jsonat {
	
Boolean::Boolean() {}
Boolean::Boolean(bool pt) : b_(pt) {}
Boolean::Boolean(const Boolean& pt) : b_(pt.b_) {}

Boolean& Boolean::operator=(const Boolean& pt) {
	if (this != &pt) this->b_ = bool(pt);
	return *this;
}


Boolean::operator bool() const { return b_; }

Boolean& Boolean::operator&=(Boolean pt) {
	this->b_ &= bool(pt);
	return *this;
}

Boolean& Boolean::operator|=(Boolean pt) {
	this->b_ |= bool(pt);
	return *this;
}

Boolean& Boolean::operator^=(Boolean pt) {
	this->b_ ^= bool(pt);
	return *this;
}

// bool operator==(Boolean a, Boolean b) { return a.b_ == b.b_; }

std::ostream& operator<<(std::ostream& os, Boolean pt) {
	return os << (pt ? "true" : "false");
}

void toString(std::ostream& os, const Boolean& pt) {
	os << pt;
}
	
} // namespace jsonat