jvx_exclude_platform("Emscripten")

set(PROJECT_NAME ayf-shared-connection-host)
include(${JVX_CMAKE_DIR}/common_local_lib_head.cmake)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/os-${JVX_OS}
  ${CMAKE_CURRENT_BINARY_DIR}

  ${JVX_BASE_LIBS_INCLUDE_PATH}/jvx-host-json/include
  ${JVX_BASE_BINARY_DIR}/sources/jvxMinHosts/jvxMHAppMinHostCon/

  ${JVX_BASE_BINARY_DIR}/sources/jvxTools/jvxTconfigProcessor
  )

set(LOCAL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ayf-connection-host.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CayfGlobalHostClass.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CayfGlobalHostClass.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CayfConnectionHostDll.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exports/${JVX_OS}/exports-connect-host.def)

set(BUILD_SHARED TRUE)

# this changes the name of the output to be followed by "_import"
# It does NOT produce an import lib in the SDK for all projects which
# are compiled to form a runtime
set(JVX_FORCE_RUNTIME_IMPORTLIB TRUE)

# This allows to copy import lib (.lib file) to sdk also
set(JVX_SDK_FORCE_DEPLOY_IMPORT_STATIC_LIB TRUE)

set(LOCAL_LIBS 
    jvxMHAppMinHostCon_static
    jvxTconfigProcessor_static
    jvx-host-json_static)

include(${JVX_CMAKE_DIR}/common_local_lib_foot.cmake)

# message(FATAL_ERROR "Import lib")
