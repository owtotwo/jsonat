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
	
void toString(std::ostream& os, const Array& pt, 
		int indent = 0, const std::string& indent_string = "    ") {
	os << "[";
	if (pt.size() > 0) {
		os << "\n";
		auto it = pt.begin();
		for (int i = 0; i < indent; i++) os << indent_string;
		
		toString(os, *it, indent + 1, indent_string);
		for (++it; it != pt.end(); ++it) {
			os << ", \n";
			for (int i = 0; i < indent; i++) os << indent_string;
			toString(os, *it, indent + 1, indent_string);
		}
		os << "\n";
		for (int i = 0; i < indent - 1; i++) os << indent_string;
	}
	os << "]";
}

} // namespace jsonat
