// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include <cctype> // for isdigit()
#include <sstream>
#include <string>
#include <cstdint> // for uint16_t
#include <utility> // for move()
#include <initializer_list>
#include <algorithm> // for all_of()
#include <cassert>
#include <functional> // for function<>()
#include <stdexcept>

#include "jsonJson.h"

#include "jsonValue.h"
#include "jsonObject.h"
#include "jsonNumber.h"
#include "jsonString.h"
#include "jsonArray.h"
#include "jsonBoolean.h"

namespace jsonat {

Json::Json() : Value() {}
Json::Json(const Value& pt) : Value(pt) {}
Json::Json(Value&& pt) : Value(std::move(pt)) {}

// ----------- Json API implement -----------

static Value parse_Json(std::istream& is);

Value Json::parse(const std::string& text) {
	std::istringstream ss(text);
	return Json::parse(ss); // implement by another overload function below
}


Value Json::parse(std::istream& is) {
	Value val; // null
	
	try { val = parse_Json(is); } catch (const std::string& _err) {
		std::cerr << "jsonat error: " << _err << std::endl;
	} catch (const char* _err) {
		std::cerr << "jsonat error: " << _err << std::endl;
	} catch (...) {
		throw "the exception threw from could not be identified";
	}
	
	return val;
}

 
void Json::stringify(std::ostream& os, const Value& val) {
	toString(os, val, 1, "");
}

  
std::string Json::stringify(const Value& val) {
	std::ostringstream ss;
	Json::stringify(ss, val);
	return ss.str();
}
	

void Json::pretty(std::ostream& os, const Value& val,
		const std::string& indent_string) {
	toString(os, val, 1, indent_string);
}

  
std::string Json::pretty(const Value& val, 
		const std::string& indent_string) {
	std::ostringstream ss;
	Json::pretty(ss, val, indent_string);
	return ss.str();
}


Json Json::make_object(std::initializer_list<Value> il) {
	auto is_kv_pair = [](const Value& x) -> bool {
		return (x.isArray() && (x.getArray().size() == 2) && x.getArray().front().isString());
	};
	assert(std::all_of(il.begin(), il.end(), is_kv_pair)); 
	return Object(il); 
}

Json Json::make_array(std::initializer_list<Value> il) { return Array(il); }

const Object& Json::getObject() const {
	if (this->getType() != Value::OBJECT_TYPE)
		throw std::domain_error("type should be value::OBJECT_TYPE");
	return Value::getObject();
}

const Array& Json::getArray() const {
	if (this->getType() != Value::ARRAY_TYPE)
		throw std::domain_error("type should be value::ARRAY_TYPE");
	return Value::getArray();
}



Json makeObject(std::initializer_list<Value> il) { return Json::make_object(il); }
Json makeArray(std::initializer_list<Value> il) { return Json::make_array(il); }

	



// ============================= Detail ============================


using std::string;
using std::istringstream;
using std::cout;
using std::endl;
using std::istream;

static Object parse_Object(istream& is);
static Array parse_Array(istream& is);
static Value parse_Value(istream& is);
static String parse_String(istream& is);
static Number parse_Number(istream& is);



// -------- Aux functions --------

static void debug_printf(const char* s) {
	// std::cout << s << std::endl;
}

static void expected_a_(const string& s) {
	throw "Expected a " + s;
}

static void error_alert(const string& _err) {
	throw _err;
}

static char look_ahead(istream& is) {
	char tmp = '\0';
	(is >> tmp).unget();
	return tmp;
}

static char look_next_char(istream& is) {
	char next_char = '\0';
	is.get(next_char).unget();
	return next_char;
}

static char get_next_char(istream& is) {
	char c = '\0';
	is.get(c);
	return c;
}

static bool identifier_match(istream& is, char _identifier, const string& char_name) {
	char tmp = '\0';
	if (!(is >> tmp) || tmp != _identifier) {
		expected_a_(char_name);
		return false;
	}
	return true;
}

static bool isHexDigit(char hex_digit) {
	return isdigit(hex_digit)
		|| (hex_digit >= 'a' && hex_digit <= 'f')
		|| (hex_digit >= 'A' && hex_digit <= 'F');
}


/**
 * Convert UCS-2 big-endian to UTF-8.
 * @param s: a string in Unicode UCS-2 big-endian code,
 * @ret : a string in Unicode UTF-8 code,
 * i.e. : s = {0x4E, 0x25}; // UCS-2 big-endian
 *   ucs2be_to_utf8(s) return a string {0xE4, 0xB8, 0xA5}. // UTF-8
 */
static std::string ucs2be_to_utf8(const std::string& s) {

	std::string ret;

	for (unsigned i = 0; i < s.length() - 1; i += 2) {

		uint16_t n = (((unsigned char)s[i] << 8) | ((unsigned char)s[i + 1]));

		if (n < 0x0080) { // 0000-007F | 0xxxxxxx

			ret += s[i + 1]; // compatible with ascii

		} else if (n < 0x0800) { // 0080-07FF | 110xxxxx 10xxxxxx

			ret += (0xc0 | ((n >> 6) & 0x1f));
			ret += (0x80 | (n & 0x3f));

		} else { // 0800-FFFF | 1110xxxx 10xxxxxx 10xxxxxx

			ret += (0xe0 | ((n >> 12) & 0x0f));
			ret += (0x80 | ((n >> 6) & 0x3f));
			ret += (0x80 | (n & 0x3f));

		}
	}
	
	return ret;
}


/**
 * Convert four char to a UTF-8 string.
 * i.e. : unicodeToAsciis("4E25") return a string {0xE4, 0xB8, 0xA5}.
 */
static std::string unicodeToAsciis(const char hex_digits[4]) {
	istringstream ss(hex_digits);
	uint16_t n = 0;
	ss >> std::hex >> n;
	return ucs2be_to_utf8(std::string({char(n >> 8), char(n)}));
}




// ---------------- parse_* function (recursive descent method) -----------------


// for parsing "true", "false" and "null" three literal value
static Value parse_Value_aux(istream& is, const string& _literal, const Value& _val) {
	debug_printf("parse_Value_aux()");

	for (unsigned i = 0; i < _literal.length(); i++) {
		if (look_next_char(is) != _literal[i]) {
			error_alert("Do you mean \'" + _literal + "\'?");
			return Value();
		}
		get_next_char(is);
	}

	return _val;
}


// The entrance function, for Json::parse()
static Value parse_Json(istream& is) {
	debug_printf("parse_Json()");
	
	Value val; // null
	
	switch (look_ahead(is)) {
		case '{': {
			val = parse_Object(is);
			break;
		}
		case '[': {
			val = parse_Array(is); 
			break;
		}
		default: 
			error_alert("A Json payload should be an object or array");
	}
	
	if (look_ahead(is) != 0) error_alert("redundant charactors after the Json");
	
	return val;
}


static Object parse_Object(istream& is) {
	debug_printf("parse_Object()");

	Object obj;

	identifier_match(is, '{', "left_brace");

	if (look_ahead(is) != '}') {
		do {

			String obj_key = parse_String(is);
			identifier_match(is, ':', "colon");
			Value obj_value = parse_Value(is);

			obj.addPair(obj_key, obj_value);

		} while (look_ahead(is) == ',' && identifier_match(is, ',', "comma"));
	}

	identifier_match(is, '}', "right_brace");

	return obj;
}


static Array parse_Array(istream& is) {
	debug_printf("parse_Array()");
	Array arr;

	identifier_match(is, '[', "left_bracket");

	if (look_ahead(is) != ']') {
		do {

			Value arr_value = parse_Value(is);
			arr.addValue(arr_value);

		} while (look_ahead(is) == ',' && identifier_match(is, ',', "comma"));
	}

	identifier_match(is, ']', "right_bracket");

	return arr;
}


static Value parse_Value(istream& is) {
	debug_printf("parse_Value()");
	Value val;

	char c = look_ahead(is);

	if (c == '\"') {

		val = parse_String(is);

	} else if (c == '-' || isdigit(c)) {

		val = parse_Number(is);

	} else if (c == '{') {

		val = parse_Object(is);

	} else if (c == '[') {

		val = parse_Array(is);

	} else if (c == 't') {

		val = parse_Value_aux(is, "true", Boolean(true));

	} else if (c == 'f') {

		val = parse_Value_aux(is, "false", Boolean(false));

	} else if (c == 'n') {

		val = parse_Value_aux(is, "null", Value());

	} else {

		error_alert("invalid Value");

	}

	return val;
}



// Support the unicode escape ('\u0123') completely now.
static String parse_String(istream& is) {
	debug_printf("parse_String()");
	String str;

	identifier_match(is, '\"', "opening quotation mark");

	while (look_next_char(is) != '\"') {
		char next_char = get_next_char(is);

		debug_printf((string("next char is ") + next_char).c_str());

		if (is.eof()) {
			error_alert("the string is broken");
		}

		if (next_char == '\\') {
			switch (next_char = get_next_char(is)) {
				case '\"': str.addChar('\"'); break;
				case '\\': str.addChar('\\'); break;
				case '/': str.addChar('/'); break;
				case 'b': str.addChar('\b'); break;
				case 'f': str.addChar('\f'); break;
				case 'n': str.addChar('\n'); break;
				case 'r': str.addChar('\r'); break;
				case 't': str.addChar('\t'); break;
				case 'u': {
					char hex_digits[4];
					for (int i = 0; i < 4; ++i) {
						hex_digits[i] = get_next_char(is);
						if (!isHexDigit(hex_digits[i]))
							error_alert("invalid hexadecimal digits after \'\\u\'");
						if (is.eof()) error_alert("the string is broken");
					}
					std::string ascii_string = unicodeToAsciis(hex_digits);
					for (auto c : ascii_string) str.addChar(c);
					break;
				}
				default: error_alert(
						std::string("unable to identify the escape char \'") 
						+ next_char + '\'');
			}
		} else {
			str.addChar(next_char);
		}
	}

	identifier_match(is, '\"', "close quotation mark");

	return str;
}


static Number parse_Number(istream& is) {
	debug_printf("parse_Number()");
	Number num;

	double d = 0;
	is >> d;
	num = d;

	return num;
}


} // namespace jsonat

