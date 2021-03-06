libzeug
=======

Libzeug is a collection of C++ functions, classes and libraries that are too small to be standalone.
It acts like a storage point for useful and reusable code for everyone using C++.
Libzeug is a cross-platform library licenced under the [MIT license](http://opensource.org/licenses/MIT).

The current modules in libzeug are:
 * [iozeug](#iozeug)
 * [loggingzeug](#loggingzeug)
 * [propertyguizeug](#propertyguizeug)
 * [reflectionzeug](#reflectionzeug)
 * [scriptzeug](#scriptzeug)
 * [signalzeug](#signalzeug)
 * [threadingzeug](#threadingzeug)

The current release is [libzeug-v0.5.0](https://github.com/hpicgs/libzeug/releases/tag/v0.5.0).

__Our [wiki](https://github.com/hpicgs/libzeug/wiki) contains information to help you get started.__

### Documentation

A first basic libzeug documentation can be found [here](http://costumebrother.de/libzeug).

### Dependencies

The following dev-libraries and programs need to be provided for correct CMake configuration:
* C++11 compatible compiler (e.g. gcc 4.7, VS 2013)
* CMake (>=2.8.9, better 2.8.12): http://www.cmake.org/
* Qt5 (>= 5.0): http://www.qt-project.org/

iozeug
------

iozeug contains a function to read a file into an std::string.

loggingzeug
-----------

loggingzeug provides stream like logging functionality with customizable outputs (default output is to the console).

propertyguizeug
---------------

propertyguizeug contains the automatic generation of a GUI from a set of properties from [reflectionzeug](#reflectionzeug).

reflectionzeug
------------

reflectionzeug allows the definition of properties that can be used to parameterize a program.
It supports saving and loading properties to and from a file.
The currently implemented property types are `bool`, `float`, `double`, `std::string`, `FilePath`, `Color`, every integral type, user-defined enums and glm types. Every prior type can be wrapped in an `std::array`. You can extend reflectionzeug and add your own types.

scriptzeug
----------

scriptzeug offers a scripting environment to which one can register reflectionzeug objects that then can be manipulated within a scripting language.
Currently implemented as scripting environment is Javascript, both with [V8](https://code.google.com/p/v8/) (must be compiled and provided externally) and [Duktape](http://duktape.org/) (default, included in scriptzeug).


signalzeug
----------

signalzeug is a small library that provides classes for a simple signal system.
Objects can define signals they can fire and other objects can register on those signals.
Arbitrary parameters and even signal chaining are allowed.

threadingzeug
-------------

threadingzeug provides a `parallel_for` function that uses either OpenMP or the `std::thread` classes to execute a for loop concurrently.
