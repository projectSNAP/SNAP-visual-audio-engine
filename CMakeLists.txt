cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project (SNAP-visual-audio-engine VERSION 0.1 LANGUAGES CXX)
SET(CMAKE_SYSTEM_NAME Windows)
# Set build type default to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Get the required packages
find_package(OpenCV REQUIRED)
find_package(OpenAL REQUIRED)
# Set project include directory
include_directories(
	include
	${OpenCV_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIR}
)
# Set project source directory
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")
# Set the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
	
# Set the name of the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set the libaraies to link with the project
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${OPENAL_LIBRARY})

#MACRO (COPY_DLL trgt libname)
#        ADD_CUSTOM_COMMAND (
#        TARGET ${trgt}
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND}
#        ARGS -E copy "${OPENCVDIR/bin}/${libname}.dll" ${CMAKE_CURRENT_BINARY_DIR}
#        )
#ENDMACRO (COPY_DLL)