# rana v0.9

rana is a C++ library for reading and writing JavaScript Object Notation (JSON) files with an emphasis on ease-of-use.

## Quick start

To try out the program, there are two options:

* [Download the latest release](https://github.com/tfussell/rana/archive/master.zip).
* Clone the repository: `git clone https://github.com/tfussell/rana`.

To start using rana in your project, just include **rana.hpp**. All of the objects and functions are in the namespace rana.

Load a JSON file like this:
```c++
rana::value json = rana::from_file("file.json");
```

You can treat this object much like an object in JavaScript:
```c++
//Keyed access
int item1 = json["item1"];
bool item2 = json["item2"];
//Indexed access
std::string item3 = json[3];
float item4 = json[4];
```

If your JSON object contains an array, you can iterate over all of the values:
```c++
for(const auto &element : json[5].iter_array())
{
    std::cout << element << std::endl;
}
```

Likewise for an object:
```c++
for(const auto &member : json[5].iter_object())
{
    std::cout << member.first << " " << member.second << std::endl;
}
```

You can append an item to your array:
```c++
rana::value a = rana::value::array;
a.append(3);
a.append(false);
// Convenience notation for the same
rana::value a = rana::value::array(3)(false);
```

Finally, stringify your object:
```c++
std::cout << rana::to_string(a) << std::endl;
```

This is assuming we have an example file, **file.json**, which looks like this:
```js
{
  "item1" : 42,
  "item2" : false,
  "item3" : "this is a string",
  "item4" : 3.141592,
  "item5" : [0, 1, 2],
}
```

## Why JSON?

* **Config files** - JSON is a convenient, concise, and readable format for storing configuration options.
* **Interoperability** - There are JSON interfaces for all of the major languages. It allows data to be transferred between processes and systems without some of the complications of serialization.
* **Flat file databases** - JSON is more compact than CSV or XML. It is also less cumbersome than XML for editing by hand.

## Features

* Simple - 3 objects
* Fast - speed similar to other C++ JSON libraries in built-in benchmarks
* Unicode support - strings are internally stored as UTF8. They can be read from and written to ascii, latin1, utf8, utf16, and utf32.
* No external dependencies - rana doesn't require boost or parser generators--only the STL
* Windows/Linux/OS X compability - rana is regularly built on and passes all tests in the three major operating systems and their associated compilers
* Configurable pretty print - enable or disable indentation, spaces before and after object member/array elements, and encoding.
* Supports reading/writing to/from strings, streams, and files.

