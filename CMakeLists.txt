cmake_minimum_required(VERSION 3.15)
project(Nexus VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

if(NOT DEFINED NEXUS_MASTER_PROJECT)
	if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
		set(NEXUS_MASTER_PROJECT ON)
	else()
		set(NEXUS_MASTER_PROJECT OFF)
	endif()
endif()

option(NEXUS_TIDY "Enable clang-tidy" OFF)
if(NEXUS_TIDY)
	set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	message(STATUS "clang-tidy enabled")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

file(GLOB NEXUS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/Nexus.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/Nexus/*.h")
file(GLOB NEXUS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_STANDARD 23)

add_library(Nexus STATIC ${NEXUS_HEADERS} ${NEXUS_SOURCES})
target_include_directories(Nexus PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(NEXUS_MASTER_PROJECT)
	add_subdirectory(example)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad)
target_link_libraries(Nexus PUBLIC glad)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
target_link_libraries(Nexus PUBLIC glfw)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
target_link_libraries(Nexus PUBLIC glm)

add_library(ImGui STATIC)

# add_subdirectory(vendor/ImGui)
# target_link_libraries(Nexus PUBLIC imgui)
file (GLOB IMGUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/*.h")
list (APPEND IMGUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/backends/imgui_impl_glfw.h")
list (APPEND IMGUI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/backends/imgui_impl_opengl3.h")

file (GLOB IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/*.cpp")
list (APPEND IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/backends/imgui_impl_glfw.cpp")
list (APPEND IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/backends/imgui_impl_opengl3.cpp")
list (APPEND IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui/misc/cpp/imgui_stdlib.cpp")

target_sources(ImGui PUBLIC ${IMGUI_HEADERS} ${IMGUI_SOURCES})
target_link_libraries(ImGui PUBLIC glad glfw)
target_include_directories(ImGui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor")
target_include_directories(ImGui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/ImGui")

target_link_libraries(Nexus PUBLIC ImGui)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
target_link_libraries(Nexus PUBLIC spdlog::spdlog)