cmake_minimum_required(VERSION 3.15)

project(Nexus_Example CXX)

if (NOT TARGET Nexus)
	find_package(Nexus REQUIRED)
endif()

add_executable(Nexus_Example "main.cpp")
target_link_libraries(Nexus_Example PRIVATE Nexus)