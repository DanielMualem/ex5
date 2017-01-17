

cmake_minimum_required(VERSION 3.6)
project(ex3)
set(core_sockets sockets/Socket.cpp sockets/Udp.cpp sockets/Tcp.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
find_package (Threads)
include_directories(${Boost_INCLUDE_DIR})
add_library(sockets ${core_sockets})

set(SOURCE_FILES src/Point.cpp src/Point.h src/Node.cpp src/Node.h src/GridBase.cpp src/GridBase.h src/GridTwoD.cpp src/GridTwoD.h src/BFS.cpp src/BFS.h src/Cab.cpp src/Cab.h src/Driver.cpp src/Driver.h src/LuxuryCab.cpp src/LuxuryCab.h src/Passenger.cpp src/Passenger.h src/StandardCab.cpp src/StandardCab.h src/TaxiCenter.cpp src/TaxiCenter.h src/TripInfo.cpp src/TripInfo.h src/MartialStatus.h src/Manufacturer.h src/Color.h)
add_executable(server ${SOURCE_FILES} src/MainServer.cpp)
add_executable(client ${SOURCE_FILES} src/MainClient.cpp)

target_link_libraries(server sockets ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(client sockets ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})