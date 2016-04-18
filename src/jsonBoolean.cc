// jsonBoolean.cc
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

std::ostream& operator<<(std::ostream& os, Boolean pt) {
	return os << (pt ? "true" : "false");
}

	
} // namespace jsonat