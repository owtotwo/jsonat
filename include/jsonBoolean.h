// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#ifndef JSON_BOOLEAN_H
#define JSON_BOOLEAN_H

#include <ostream>


namespace jsonat {


class Boolean {
public:
	Boolean();
	Boolean(bool pt);
	Boolean(const Boolean& pt);
	
	Boolean& operator=(const Boolean& pt);
	
	operator bool() const;
	
	Boolean& operator&=(Boolean pt);
	Boolean& operator|=(Boolean pt);
	Boolean& operator^=(Boolean pt);
	
	// friend bool operator==(Boolean a, Boolean b);
	friend std::ostream& operator<<(std::ostream& os, Boolean pt);
	friend void toString(std::ostream& os, const Boolean& pt);
	
private:
	bool b_ = false;
};

} // namespace Json


#endif // JSON_BOOLEAN_H