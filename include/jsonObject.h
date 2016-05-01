// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

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
#include <initializer_list>


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

	using SuperClass::SuperClass;

	Object();
	Object(const Object& obj) = default;
	Object(Object&& pt) = default;
	Object(const Value& pt);
	Object(Value&& pt); 
	Object(std::initializer_list<Value> il);
	
	Object& operator=(const Object& pt) = default;
	Object& operator=(Object&& pt) = default;
	Object& operator=(const Value& pt);
	Object& operator=(Value&& pt);

	void addPair(const String& key, const Value& value);
	
	friend std::ostream& operator<<(std::ostream& os, const Object& pt);
	friend void toString(std::ostream& os, const Object& pt, 
		int indent, const std::string& indent_string);
	
};

} // namespace Json


#endif // JSON_OBJECT_H