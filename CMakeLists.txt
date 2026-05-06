cmake_minimum_required(VERSION 3.16)
project(HotelReservationQt LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets QUIET)
if(Qt6_FOUND)
    set(QT_PACKAGE Qt6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    set(QT_PACKAGE Qt5)
endif()

add_executable(HotelReservationQt WIN32
    qt_main.cpp
    admin.cpp
    billing.cpp
    booking.cpp
    doubleroom.cpp
    filemanager.cpp
    guest.cpp
    Hotelexception.cpp
    hotelsystem.cpp
    person.cpp
    records.cpp
    room.cpp
    rules.cpp
    singleroom.cpp
    suiteroom.cpp
)

target_include_directories(HotelReservationQt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(HotelReservationQt PRIVATE ${QT_PACKAGE}::Widgets)
