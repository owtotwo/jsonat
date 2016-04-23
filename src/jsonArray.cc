#include <utility> // for move()
#include <ostream>

#include "jsonArray.h"
#include "jsonValue.h"


namespace jsonat {

Array::Array() : Array::SuperClass() {}

Array::Array(const Array& pt) : Array::SuperClass(pt) {}
Array::Array(const Value& pt) : Array::SuperClass() {
	if (pt.getType() != Value::ARRAY) return;
	*this = pt.getArray();
}

Array::Array(Value&& pt) {
	if (pt.getType() != Value::ARRAY) return;
	*this = std::move(*pt.array_ptr);
}

Array& Array::operator=(const Value& pt) {
	if (pt.getType() != Value::ARRAY || this == pt.array_ptr) return *this;
	return *this = pt.getArray();
}

Array& Array::operator=(Value&& pt) {
	if (pt.getType() != Value::ARRAY || this == pt.array_ptr) return *this;
	return *this = std::move(*pt.array_ptr);
}




void Array::addValue(const Array::value_type& val) { 
	this->push_back(val); 
}

std::ostream& operator<<(std::ostream& os, const Array& pt) {
	os << "[";
	if (pt.size() > 0) {
		auto it = pt.begin();
		os << *it;
		for (++it; it != pt.end(); ++it) {
			os << "," << *it;
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
