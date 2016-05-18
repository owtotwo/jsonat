// Jsonat -- A Json Library in C++
// Copyright (c) 2016 sysu_AT
// All rights reserved.

#include <iostream>
#include "Json.h"


struct Book {
	int id;
	std::string name;
	std::string author;
	double price;
	
	Book(int _id = 0, std::string _name = "No name", 
		std::string _author = "Anonymous", double _price = 0.00) 
		: id(_id), name(_name), author(_author), price(_price) {}
};

/*
   The sample is for driving the development of this project, so maybe it
   is not so concise and simple to figure out how to use the jsonat.
*/
void sample() {
	using jsonat::Json;
	using jsonat::makeArray;
	using jsonat::makeObject;
	
	Book books[5] = {
		{1, "The Little Prince", "Antoine de Saint-Exupéry", 6.70},
		{2, "The Moon and Sixpence", "W. Somerset Maugham", 11.40},
		{3, "To Kill a Mockingbird", "Harper Lee", 6.11},
		{4, "Frog", "Mo Yan", 14.17},
		{5, "Big Breasts and Wide Hips", "Mo Yan", 12.00}
	};
	
	
	/* --- save as bookname-author pairs --- */
	
	// var booklist = {"Red Sorghum": "Mo Yan", "Zero K": "Don DeLillo"};
	Json booklist = { // Object type
		{/* key */ "Red Sorghum", /* value */ "Mo Yan"}, 
		{/* key */ "Zero K", /* value */ "Don DeLillo"}
	};
	
	
	/* --- push all the books whose author do not be mentioned in booklist. --- */
	
	Json id_list = makeArray({}); // Array type, mark which should be added
	for (auto item : books) {
		Json has_same_author = false; // Boolean type
		for (auto book : booklist.getObject()) { // cause Object type
			if (book.second == item.author) has_same_author = true;
		}
		if (!has_same_author) id_list.push(item.id);
	}
	
	for (auto id : id_list.getArray()) { // cause Array type
		// bool insert(const String& key, const Value& value)
		booklist.insert(books[id - 1].name, books[id - 1].author);
	}
	
	
	/* --- show up in form of JSON --- */
	
	std::cout << "Not so pretty : \n";
	std::cout << booklist << std::endl << std::endl; // not so pretty
	
	std::cout << "Pretty output : \n";
	Json::pretty(std::cout, booklist); // pretty output
	
	std::cout << std::endl << "id list: " << id_list << std::endl;
	
	
	/* 
	 * If you want to put only one value which is a variable in type 
	 * of Array in an Array, you should use function makeArray to make
	 * sure that it will call the Array(initializer_list<Value> il) 
	 * instead of copy constructor.
	 * For instance: 
	 *   Json a = makeArray({}); // or Json a({}) which will call Array()
	 *   Json b = {a}; // Bad. g++ will call Json(initializer_list<Value> il)
	 *                 // but clang++ will call Json(const Json& pt) 
	 *   Json b = makeArray({a}); // Nice.
	 */
	Json a({}); // no equivalent to Json a{};
	Json b = makeArray({a});
	
	std::cout << (a.isArray() ? 
		"Json a({}) is an Array [].\n" : 
		"Json a({}) is not an Array [].\n"
	);
	
	std::cout << "b.size() == " << b.size() << '\n'; // should be 1
	
	
	/*
	 * Json c = {{"hello", "world"}}; // is equivalent to {"hello":"world"}.
	 * If you want to make an Array instead of an Object, you could code like
	 * this :
	 *   Json d = makeArray({{"hello", "world"}});
	 */
	Json c = {{"hello", "world"}};
	Json d = makeArray({{"hello", "world"}});
	
	std::cout << "Json c = {{\"hello\", \"world\"}} is" 
		<< (c.isObject() ? "" : " not") << " an Object [].\n";
	std::cout << "Json d = makeArray({{\"hello\", \"world\"}}) is" 
		<< (d.isArray() ? "" : " not") << " an Array [].\n";
		
	c["AT_University"] = "SYSU";
	c["outer"]["inner"] = 3.1415926;
	std::cout << "c[\"hello\"] == " << c["hello"] << '\n';
	std::cout << "c[\"AT_University\"] == " << c["AT_University"] << '\n';
	std::cout << "c[\"outer\"][\"inner\"] = " << c["outer"]["inner"] << '\n';	
	std::cout << "d.size() == " << d.size() << '\n'; // should be 1
	std::cout << "d[0].size() == " << d[0].size() << '\n'; // should be 2
	
	std::cout << "\nc : \n" << c << '\n';
}

int main() {
	sample();
	return 0;
}