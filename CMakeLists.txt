cmake_minimum_required( VERSION 2.8 ) 
project ( SNAP-visual-audio-engine )
# Get the required packages
find_package( OpenCV REQUIRED )
find_package( OpenAL REQUIRED )
# Set project include directory
include_directories( 
	include
	${OpenCV_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIR}
)
# Set project source directory
file(GLOB SOURCES "src/*.cpp")
# Set the name of the executable
add_executable( ${PROJECT_NAME} ${SOURCES} )
# Set the libaraies to link with the project
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${OPENAL_LIBRARY})

add_custom_command (TARGET SNAP-visual-audio-engine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${OpenCV_DIR}/../bin/opencv_world340d.dll ${CMAKE_BINARY_DIR}
)