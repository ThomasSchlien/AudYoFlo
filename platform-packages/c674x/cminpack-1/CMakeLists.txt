set(JVX_TARGET_NAME "cminpack-1-c674x")
message("--> Configuring ${JVX_TARGET_NAME}")
project(${JVX_TARGET_NAME})

set(JVX_PLATFORM_PACKAGE_LIB_NAME cminpack-1)
set(JVX_PLATFORM_NAME "c674x")

# During cmake run phase, create workspace if not available yet
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/ws)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ws)

	# Import the target project
	execute_process(
		COMMAND ${CCS_ECLIPSE}
		-noSplash -data ${CMAKE_CURRENT_BINARY_DIR}/ws
		-application com.ti.ccstudio.apps.projectImport
		-ccs.location ${CMAKE_CURRENT_SOURCE_DIR}/project/${JVX_PLATFORM_PACKAGE_LIB_NAME})
endif()

# At build time, run the ccs command script to build release as well as release version of lib
add_custom_target(${JVX_TARGET_NAME}
	ALL
	COMMAND ${CCS_ECLIPSE}
	-noSplash -data ${CMAKE_CURRENT_BINARY_DIR}/ws -application com.ti.ccstudio.apps.projectBuild -ccs.projects
	${JVX_PLATFORM_PACKAGE_LIB_NAME} -ccs.configuration Debug && 
	${CCS_ECLIPSE}
	-noSplash -data ${CMAKE_CURRENT_BINARY_DIR}/ws -application com.ti.ccstudio.apps.projectBuild -ccs.projects
	${JVX_PLATFORM_PACKAGE_LIB_NAME} -ccs.configuration Debug-c8 &&
	${CCS_ECLIPSE} -noSplash -data ${CMAKE_CURRENT_BINARY_DIR}/ws
	-application com.ti.ccstudio.apps.projectBuild
	-ccs.projects ${JVX_PLATFORM_PACKAGE_LIB_NAME} -ccs.configuration Release &&
	${CCS_ECLIPSE} -noSplash -data ${CMAKE_CURRENT_BINARY_DIR}/ws
	-application com.ti.ccstudio.apps.projectBuild
	-ccs.projects ${JVX_PLATFORM_PACKAGE_LIB_NAME} -ccs.configuration Release-c8)
	
# Install both libraries
if(JVX_RELEASE_SDK)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/project/${JVX_PLATFORM_PACKAGE_LIB_NAME}/Debug/${JVX_PLATFORM_PACKAGE_LIB_NAME}.lib DESTINATION ${INSTALL_PATH_PLATFORM_PACKAGE_LIB_STATIC}/${JVX_PLATFORM_NAME}/Debug)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/project/${JVX_PLATFORM_PACKAGE_LIB_NAME}/Release/${JVX_PLATFORM_PACKAGE_LIB_NAME}.lib DESTINATION ${INSTALL_PATH_PLATFORM_PACKAGE_LIB_STATIC}/${JVX_PLATFORM_NAME}/Release)
	
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/project/${JVX_PLATFORM_PACKAGE_LIB_NAME}/Debug-c8/${JVX_PLATFORM_PACKAGE_LIB_NAME}.lib DESTINATION ${INSTALL_PATH_PLATFORM_PACKAGE_LIB_STATIC}/${JVX_PLATFORM_NAME}/Debug-c8)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/project/${JVX_PLATFORM_PACKAGE_LIB_NAME}/Release-c8/${JVX_PLATFORM_PACKAGE_LIB_NAME}.lib DESTINATION ${INSTALL_PATH_PLATFORM_PACKAGE_LIB_STATIC}/${JVX_PLATFORM_NAME}/Release-c8)

	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../compatibility/ DESTINATION ${INSTALL_PATH_PLATFORM_PACKAGE_INCLUDE_STATIC}/${JVX_PLATFORM_NAME} FILES_MATCHING PATTERN "*.h")
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${INSTALL_PATH_PLATFORM_PACKAGE_INCLUDE_STATIC}/${JVX_PLATFORM_NAME} FILES_MATCHING PATTERN "*.h")

endif()
