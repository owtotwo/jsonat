// Array.h


#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <vector>
#include <ostream>

namespace jsonat {

// Forward declaration
class Value;



class Array : public std::vector<Value> {

	typedef std::vector<Value> SuperClass;
	typedef Value value_type;

public:
	
	Array();
	Array(size_t n);
	Array(const Array& pt);
	Array(const Value& pt);
	
	Array& operator=(const Array& pt) = default;
	
	void addValue(const value_type& val);
	friend std::ostream& operator<<(std::ostream& os, const Array& pt);
	friend void toString(std::ostream& os, const Array& pt, 
		int indent, const std::string& indent_string);
};

} // namespace Json


#endif // JSON_ARRAY_H