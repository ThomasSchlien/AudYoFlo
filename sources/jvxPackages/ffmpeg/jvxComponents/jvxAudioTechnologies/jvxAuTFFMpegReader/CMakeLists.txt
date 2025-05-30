if(DEFINED JVX_SDK_PATH)
	include(${JVX_SDK_PATH}/cmake/standalone.cmake)
endif(DEFINED JVX_SDK_PATH)

set(PROJECT_NAME jvxAuTFFMpegReader)
include(${JVX_CMAKE_DIR}/common_local_lib_head.cmake)

set(LOCAL_PCG_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/codeGen/exports_technology.pcg
	${CMAKE_CURRENT_SOURCE_DIR}/codeGen/exports_device.pcg
	)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/target
  ${JVX_BASE_LIBS_INCLUDE_PATH}/jvx-dsp-base-cpp/include
  ${JVX_BASE_ROOT}/sources/jvxLibraries/jvx-component-templates-base/include
  ${JVX_BASE_BINARY_DIR}/sources/jvxLibraries/jvx-component-templates-base/generated

  # cpp helper functions
  ${JVX_BASE_ROOT}/sources/jvxLibraries/jvx-helpers-cpp/include

	${JVX_FFMPEG_ROOT_PATH}/jvxLibraries/jvx-ffmpeg-helpers/include

  ${JVX_FFMPEG_INCLUDE_DIR}
  )

set(LOCAL_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/target/componentEntry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioFFMpegReaderTechnology.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioFFMpegReaderDevice.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioFFMpegReaderTechnology.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioFFMpegReaderDevice.h
  )

set(LOCAL_LIBS
	jvx-component-templates-base_static
	
	# Helpers to provide some wav string conversions
	jvx-helpers-product_static

	jvx-ffmpeg-helpers_static
  )

  set(LOCAL_LIBS
  		${JVX_FFMPEG_LIBS}
		${JVX_SOCKET_LIBRARIES}
		${JVX_FFMPEG_SYS_LIBS}
	)

set(LOCAL_PCG_FILE_OPTIONS 
	-I ${JVX_SUBPRODUCT_ROOT}/sources/jvxLibraries/jvx-audiocodec-helpers/pcg)

set(IS_JVX_COMPONENT TRUE)
set(JVX_COMPONENT_ONLY_STATIC TRUE)

## message(FATAL_ERROR "->   ${JVX_FFMPEG_INCLUDE_DIR}")

include(${JVX_CMAKE_DIR}/common_local_lib_foot.cmake)
