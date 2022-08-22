cmake_minimum_required(VERSION 3.0)

project(MovieBookingService)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.71.0 COMPONENTS thread) 

if(Boost_FOUND)
include_directories(${Boost_INCLUDE_DIRS}) 
add_executable(MovieBookingService
main.cpp
source/BookingService.cpp
source/Database.cpp
source/Movies.cpp
source/Theaters.cpp
source/GetSeats.cpp
source/BookSeat.cpp
source/BookingServiceSettingsFactory.cpp)
 
target_link_libraries(MovieBookingService LINK_PUBLIC ${Boost_LIBRARIES} restbed)
endif()

target_include_directories(MovieBookingService PUBLIC ${CMAKE_SOURCE_DIR}/include)

set_property(TARGET MovieBookingService PROPERTY CXX_STANDARD 17)
