cmake_minimum_required(VERSION 3.9)

project(prounit)

#set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")  for Qt5
set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_AUTOMOC ON)
option(BUILD_TESTS "Build tests" OFF)

find_package(SFML REQUIRED COMPONENTS system window graphics)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
#find_package(GTest CONFIG REQUIRED)


if(WIN32)
   find_package(Tesseract CONFIG REQUIRED)

endif(WIN32)
   
if(UNIX AND NOT APPLE)
   #find_package(SFML REQUIRED COMPONENTS system window graphics)
   #find_package(Qt5Gui CONFIG REQUIRED)
   #find_package(Qt5Widgets CONFIG REQUIRED)
   find_package(Qt5Core CONFIG REQUIRED)
endif(UNIX AND NOT APPLE)

add_library(unittest STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/source/drawer.cpp)

add_executable(main
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/ui.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/drawer.cpp)

#add_executable(tests
#${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp)


target_include_directories(main
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_include_directories(tests
#PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(unittest
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


#target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main unittest)

#sfml 
#target_link_libraries(main PRIVATE FLAC OpenAL OpenGL Vorbis)
target_link_libraries(unittest -lsfml-graphics -lsfml-window -lsfml-system)
################### Linux  ###############################
if(UNIX AND NOT APPLE)
 target_compile_options(main PRIVATE -fPIC)
 include_directories(${Tesseract_INCLUDE_DIRS})
 include_directories(${Qt5Gui_INCLUDE_DIRS})
 include_directories(${Qt5Widgets_INCLUDE_DIRS})
 include_directories(${Qt5Core_INCLUDE_DIRS})
 include_directories(sfml-system sfml-window sfml-graphics)

 #target_link_libraries(main PRIVATE ${Leptonica_LIBRARIES})
 #target_link_libraries(main PRIVATE ${Tesseract_LIBRARIES})
 #target_link_libraries(main PRIVATE ${SFML_LIBRARIES})
 target_link_libraries(main -llept -ltesseract -lQt5Widgets -lQt5Gui -lQt5Core -lsfml-graphics -lsfml-window -lsfml-system)
 
 #target_link_libraries(unittest PRIVATE ${SFML_LIBRARIES})
 #target_link_libraries(unittest -lsfml-graphics -lsfml-window -lsfml-system)
endif(UNIX AND NOT APPLE)



################### WIN ##################################

if(WIN32) 
 include_directories(sfml-system sfml-window sfml-graphics)

 target_link_libraries(main PRIVATE libtesseract)
 target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)
 target_link_libraries(main PRIVATE ${Qt5Widgets_LIBRARIES})
 ##?#target_link_libraries(main PRIVATE ${Qt5Gui_LIBRARIES})
 target_link_libraries(main PRIVATE ${Qt5Gui_LIBRARIES})

 #target_link_libraries(unittest PRIVATE sfml-system sfml-window sfml-graphics)
endif(WIN32)

#if(BUILD_TESTS)
  add_subdirectory(third-party/gtest)
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(unit ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp)
  target_include_directories(unit 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(unit PRIVATE unittest gtest_main)
  add_test(NAME unit COMMAND unit)
#endif()
