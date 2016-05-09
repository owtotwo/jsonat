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
	
}

int main() {
	sample();
	return 0;
}