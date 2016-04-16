// Object.h


#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#if 0
#define __USE_UNORDERED_MAP
#else
#define __USE_MAP
#endif

#ifdef __USE_UNORDERED_MAP
	#include <unordered_map>
	#include "jsonString.h"
	#include "jsonValue.h"
#else
	#include <map>
#endif

#include <iostream>


namespace jsonat {

// Forward declaration
class String;
class Value;

#ifdef __USE_UNORDERED_MAP
	typedef std::unordered_map<String, Value, typename std::hash<std::string>> SuperClass;
#else
	typedef std::map<String, Value> SuperClass;
#endif


class Object : public SuperClass {
	typedef jsonat::SuperClass SuperClass;
public:
	Object();
	Object(const Object& obj);

	void addPair(const String& key, const Value& value);
	friend std::ostream& operator<<(std::ostream& os, const Object& pt);

};

} // namespace Json


#endif // JSON_OBJECT_H