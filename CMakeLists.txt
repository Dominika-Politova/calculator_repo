cmake_minimum_required(VERSION 3.14)

project(calculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
mathlib
GIT_REPOSITORY https://github.com/Dominika-Politova/mathlib_repo.git
GIT_TAG main
)
FetchContent_MakeAvailable(mathlib)

add_executable(calculator src/main.cpp)

target_include_directories(calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mathlib/include)

target_link_libraries(calculator PRIVATE mathlib)

install(TARGETS calculator DESTINATION bin)


find_program(CLANG_FORMAT_BIN clang-format)
if(CLANG_FORMAT_BIN)
file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp src/*.h mathlib/include/*.h)

add_custom_target(format COMMAND ${CLANG_FORMAT_BIN} -i ${ALL_SOURCE_FILES} COMMENT "Running clang-format")
endif()

find_program(CLANG_TIDY_BIN clang-tidy)
if(CLANG_TIDY_BIN)
add_custom_target(tidy COMMAND ${CLANG_TIDY_BIN} -p ${CMAKE_BINARY_DIR} src/main.cpp COMMENT "Running clang-tidy")
endif()
