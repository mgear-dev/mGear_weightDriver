set(SOURCE_FILES

	"BRMatrix.cpp"
	"pluginMain.cpp"
	"weightDriver.cpp"
	"BRMatrix.h"
	"weightDriver.h"
)

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})
MAYA_PLUGIN(${PROJECT_NAME})
