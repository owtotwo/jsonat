// Boolean.h


#ifndef JSON_BOOLEAN_H
#define JSON_BOOLEAN_H

#include <ostream>


namespace jsonat {


#if 0

typedef bool Boolean;

#else

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
	
	friend std::ostream& operator<<(std::ostream& os, Boolean pt);
	
private:
	bool b_ = false;
};

#endif

} // namespace Json


#endif // JSON_BOOLEAN_H