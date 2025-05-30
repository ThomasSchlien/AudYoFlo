if(DEFINED JVX_SDK_PATH)
	include(${JVX_SDK_PATH}/cmake/standalone.cmake)
endif(DEFINED JVX_SDK_PATH)

set(PROJECT_NAME jvxAuTCoreAudio)
include(${JVX_CMAKE_DIR}/common_local_lib_head.cmake)

set(LOCAL_PCG_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/codeGen/exports_device.pcg
  )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/target
${JVX_BASE_ROOT}/sources/jvxLibraries/jvx-component-templates-base/include
  ${JVX_BASE_BINARY_DIR}/sources/jvxLibraries/jvx-component-templates-base/generated)

set(LOCAL_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/target/componentEntry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioCoreAudioTechnology.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioCoreAudioDevice.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CjvxAudioCoreAudioDevice_coreaudio.cpp
  )

set(LOCAL_LIBS
  ${COREAUDIO}
  ${COREFOUNDATION}
  ${AUDIOUNIT}
  ${COREAUDIOKIT}
  ${AUDIOTOOLBOX}
  ${CORESERVICES}
  jvx-component-templates-base_static
  )

set(IS_JVX_COMPONENT TRUE)

include(${JVX_CMAKE_DIR}/common_local_lib_foot.cmake)
