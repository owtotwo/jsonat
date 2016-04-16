#include "jsonArray.h"
#include "jsonValue.h"

namespace jsonat {

Array::Array() : Array::SuperClass() {}
Array::Array(size_t n) : Array::SuperClass(n) {}

void Array::addValue(const Array::value_type& val) { 
	this->push_back(val); 
}

std::ostream& operator<<(std::ostream& os, const Array& pt) {
	os << "[";
	if (pt.size() > 0) {
		auto it = pt.begin();
		os << *it;
		for (++it; it != pt.end(); ++it) {
			os << ", " << *it;
		}
	}
	os << "]";
	return os;
}
	


} // namespace jsonat
