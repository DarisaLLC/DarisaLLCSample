cmake_minimum_required( VERSION 3.0 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( Sample )
set( APP_NAME "${PROJECT_NAME}App" )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cinder" ABSOLUTE )

get_filename_component( APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )
get_filename_component( BLOCK_DIR "${APP_DIR}/blocks" ABSOLUTE )

set( APP_SRCS
	${APP_DIR}/src/SampleApp.cpp
)

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
	APP_NAME ${APP_NAME}
	INCLUDES ${APP_DIR}/include
	SOURCES ${APP_SRCS}
	CINDER_PATH ${CINDER_PATH}
	BLOCKS ${BLOCK_DIR}/Cinder-Boost
		${BLOCK_DIR}/Cinder-OpenCV4
		${BLOCK_DIR}/Cinder-spdlog
)

get_target_property( OUTPUT_DIR ${APP_NAME} RUNTIME_OUTPUT_DIRECTORY )

if( APPLE )
	set_target_properties( ${APP_NAME} PROPERTIES
		MACOSX_BUNDLE TRUE
		MACOSX_BUNDLE_INFO_PLIST ${APP_DIR}/proj/cmake/Info.plist
	)

    add_custom_target( run
        COMMAND open ${OUTPUT_DIR}/${APP_NAME}.app
        DEPENDS ${OUTPUT_DIR}/${APP_NAME}.app/Contents/MacOS/${APP_NAME}
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
elseif( UNIX )
    add_custom_target( run
        COMMAND ${OUTPUT_DIR}/${APP_NAME}
        DEPENDS ${OUTPUT_DIR}/${APP_NAME}
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
endif()
