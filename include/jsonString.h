// String.h


#ifndef JSON_STRING_H
#define JSON_STRING_H

#include <string>
#include <iostream>

namespace jsonat {

class Value;

class String : public std::string {
public:

	using std::string::string;

	String();
	String(const String& str);
	String(String&& pt) = default;
	String(const Value& pt);
	String(Value&& pt);

	String& operator=(const String& pt) = default;
	String& operator=(String&& pt) = default;
	String& operator=(const Value& pt);
	String& operator=(Value&& pt);
	
	void addChar(char c);

	friend std::ostream& operator<<(std::ostream& os, const String& s);
	friend void toString(std::ostream& os, const String& pt);
	
};

} // namespace Json


#endif // JSON_STRING_H