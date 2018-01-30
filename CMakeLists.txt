cmake_minimum_required( VERSION 2.8 ) 
project ( SNAP-visual-audio-engine )
find_package( OpenCV REQUIRED )
find_package( OpenAL REQUIRED )

set( NAME_SRC
    src/main.cpp
	src/BlenderToDepthMapDLL.cpp
	src/stdafx.cpp
)

set( NAME_HEADERS       
     include/BlenderToDepthMapDLL.h
	 include/stdafx.h
	 include/targetver.h
)

include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OpenCV_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIR}
)

link_directories( ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable( ${PROJECT_NAME} ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${OPENAL_LIBRARY})