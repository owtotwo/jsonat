// parser.cpp

#include <iostream>
#include <vector>
#include <regex>
#include <cctype>
#include <climits>

#include "Json.h"


void debug_printf(const char* s) {
	// std::cout << s << std::endl;
}


namespace jsonat {

using std::string;
using std::istringstream;
using std::cout;
using std::endl;
using std::istream;
using std::regex;

static Object parse_Object(istream& is);
static Array parse_Array(istream& is);
static Value parse_Value(istream& is);
static String parse_String(istream& is);
static Number parse_Number(istream& is);




// -------- Aux functions --------

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

static bool isValidNumber(const string& s) {
	regex json_number("^-?(0|[1-9][0-9]*)(\\.[0-9]+)?((e|E)(\\+|-)?[0-9]+)?$");
	return regex_match(s, json_number);
}

static Number strToNumber(const string& str) {
	double d = 0.0;
	istringstream ss(str);
	ss >> d;
	return Number(d);
}

static char unicodeToAscii(const char hex_digits[4]) {
	istringstream ss(hex_digits);
	int c = 0;
	ss >> std::hex >> c;
	if (c < CHAR_MIN || c > CHAR_MAX) {
		error_alert("unable to transform unicode to char"
			" which out of range from 0 to 127");
	}
	return static_cast<char>(c);
}

static Value parse_Value_aux(istream& is, const string& _literal, const Value& _val) {
	debug_printf("parse_Value_aux()");

	for (int i = 0; i < _literal.length(); i++) {
		if (look_next_char(is) != _literal[i]) {
			error_alert("Do you mean \'" + _literal + "\'?");
			return Value();
		}
		get_next_char(is);
	}

	return _val;
}


void parse_Json(istream& is) {
	debug_printf("parse_Json()");
	switch (look_ahead(is)) {
		case '{': {
			Object obj = parse_Object(is);
			cout << obj << endl; 
			break;
		}
		case '[': {
			Array arr = parse_Array(is); 
			cout << arr << endl;
			break;
		}
		default: error_alert("A Json payload should be an object or array");
	}
	if (look_ahead(is) != 0) error_alert("redundant charactors after the Json");
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

		val = parse_Value_aux(is, "true", Boolen(true));

	} else if (c == 'f') {

		val = parse_Value_aux(is, "false", Boolen(false));

	} else if (c == 'n') {

		val = parse_Value_aux(is, "null", Value());

	} else {

		error_alert("invalid Value");

	}

	return val;
}


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
			switch (get_next_char(is)) {
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
					char ascii_char = unicodeToAscii(hex_digits);
					str.addChar(ascii_char);
				}
				default: error_alert("unable to identify the escape char");
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



int main(int argc, char* argv[]) {
	try { 
		jsonat::parse_Json(std::cin); 
	} catch (const std::string& _err) {
		std::cerr << _err << std::endl;
	} catch (const char* _err) {
		std::cerr << _err << std::endl;
	}
	return 0;
}