# Jsonat - A JSON Library in C++ #
*Copyright (c) 2016 sysu_AT &lt;<owtotwo@163.com>&gt;*  

[![Build Status](https://travis-ci.org/owtotwo/jsonat.svg?branch=master)](https://travis-ci.org/owtotwo/jsonat)

## Introduction ##
* Jsonat is a C++ library used to read and write JSON.


## Sample ##
* Please see the [sample4.cpp](sample/sample4.cpp) for detials.
```
using jsonat::Json; // or jsonat::JSON
using jsonat::makeArray; // or Json::make_array;
using jsonat::makeObject; // or Json::make_object;

Json a; // NULL_TYPE
Json b = 15331120; // NUMBER_TYPE
Json c = 3.1415926; // NUMBER_TYPE
Json d = "hello"; // STRING_TYPE
Json e = true; // BOOLEAN_TYPE
Json f = {{"shape", "rectangle"}, {"length", 12}, {"width", c}}; // OBJECT_TYPE
Json g = {a, b, c, d, "Literal", e, f}; // ARRAY_TYPE

f["color"] = "red";
a["author"]["university"] = "SYSU";

```


## Features ##
* Concise implementation
* JavaScript object-like 
* Simple API
* More test relatively


## Requirements ##
+ Platforms
 - Windows (x64)
 - Linux (ubuntu12.04)
 - Mac OS X
 
+ A **C++11**-Standard-Compliant Compiler 
 - [GCC 4.8.1 and later](https://gcc.gnu.org/gcc-4.8/cxx0x_status.html)
 - [Clang 3.3 and later](http://clang.llvm.org/cxx_status.html)
 
+ Additional Compile Flag  
 - -std=c++11
 


## How To Use ##
* `$> make`  
* `$> make test`  
* `$> make sample`  


## Related Projects ##
* [Google Test](https://github.com/google/googletest)


## License ##
* [GNU LESSER GENERAL PUBLIC LICENSE ( LGPL )](LICENSE)