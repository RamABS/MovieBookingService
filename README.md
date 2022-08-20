# MovieBookingService
## API - Movie Booking
The Movie Booking Service provides below APIs,
1. List of movies
2. List of theaters which runs a movie
3. Book a ticket(s) in a theater

### Tool Required
1. Restbed - framework
2. C++ Complier
3. JSON library for Modern C++ - nlohmann
4. CMake

### Tools Installation

#### Restbed
Please refer the page for the build instructions 
https://github.com/Corvusoft/restbed

#### C++ Compiler
(_C++14 and above_)
##### Linux : gcc
##### Windows : VC++
##### Mac : Clang

#### JSON Library for Modern C++
Please download/copy the single include file from this repo (single_inclue/nlohmann/json.hpp)
https://github.com/nlohmann/json/tree/develop/single_include/nlohmann

#### CMake 
Please install from the page 
https://cmake.org/download/

### Build
#### Configure the Build :
cmake -Hmovies_backend_BT -Bmovies_backend_BT/build
#### Build the Source :
cmake --build movies_backend_BT/build --target all --config Release
#### Clean the build
cmake --build movies_backend_BT/build --target clean
