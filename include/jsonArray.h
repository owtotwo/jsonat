// Array.h


#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <vector>
#include <iostream>

namespace jsonat {

// Forward declaration
class Value;



class Array : public std::vector<Value> {

	typedef std::vector<Value> SuperClass;
	typedef Value value_type;

public:
	
	Array();
	Array(size_t n);
	
	void addValue(const value_type& val);
	friend std::ostream& operator<<(std::ostream& os, const Array& pt);

};

} // namespace Json


#endif // JSON_ARRAY_H