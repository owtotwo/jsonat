// Object.h


#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <map>
#include "String.h"
#include "Value.h"

namespace Json {

typedef std::map<String, Value> Object;

} // namespace Json


#endif // JSON_OBJECT_H