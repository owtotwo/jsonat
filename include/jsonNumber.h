// Number.h


#ifndef JSON_NUMBER_H
#define JSON_NUMBER_H

namespace jsonat {

typedef double Number;

inline void toString(std::ostream& os, const Number& pt) { os << pt; }

} // namespace Json


#endif // JSON_NUMBER_H