cmake_minimum_required(VERSION 3.1)

project(bel
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
option(BEL_BUILD_RANG "A small library that colorizes your terminal." ON)

find_package(bia REQUIRED)

add_library(bel)

if(BEL_BUILD_RANG)
	list(APPEND BEL_HEADER_FILES "bel/rang/module.hpp")
	list(APPEND BEL_SOURCE_FILES "bel/rang/module.cpp")
	target_include_directories(bel
		PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/rang/include")
endif()

target_sources(bel
	PRIVATE
		"${BEL_HEADER_FILES}"
		"${BEL_SOURCE_FILES}")
target_link_libraries(bel PUBLIC bia::bia)
add_library(bia::bel ALIAS bel)

add_executable(main "main.cpp")
target_link_libraries(main PRIVATE bel)
