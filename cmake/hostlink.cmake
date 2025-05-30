	if(JVX_LINK_WITH_DEVELOP_HOST)
		# Link with develop host
		set(LOCAL_LIBS ${LOCAL_LIBS}
			jvxLDevelopHost-static_static
			)
		# In case of standalone builds, we need to pull in some other libraries
		if(DEFINED JVX_SDK_PATH)
			include(${JVX_CMAKE_DIR}/cmake-sdk/cmake-lib-packages.develophost.cmake)
			include(${JVX_CMAKE_DIR}/cmake-sdk/cmake-lib-packages.network.cmake)
		endif()
	else(JVX_LINK_WITH_DEVELOP_HOST)
		if(JVX_LINK_WITH_CONSOLE_HOST)
		
			include_directories(
				# Console linkage
				${JVX_BINARY_DIR}/base/sources/jvxEventLoop/CjvxEStandalone
				${JVX_BINARY_DIR}/base/sources/jvxHosts/jvxHJvx/
				${JVX_BASE_LIBS_INCLUDE_PATH}/jvxLConsoleTools/include
				${JVX_BASE_LIBS_INCLUDE_PATH}/jvxLWebConsoleTools/include
				${JVX_BASE_LIBS_INCLUDE_PATH}/jvx-net-helpers/include
				${JVX_BASE_ROOT}/software/codeFragments/jvxHosts/common
				${JVX_BASE_LIBS_INCLUDE_PATH}/jvx-host-json/include
				${JVX_BASE_LIBS_INCLUDE_PATH}/jvx-json/include
				${JVX_BASE_ROOT}/sources/jvxLibraries/jvx-app-host/include)
				
			if(JVX_LINK_WITH_CONSOLE_HOST_FRONTEND_BACKEND_LIB)
				set(LOCAL_LIBS ${LOCAL_LIBS} jvx-link-frontend_static)
			endif()

			# Link with console host
			set(LOCAL_LIBS ${LOCAL_LIBS}				
				jvxLConsoleHost-static_static
				jvxLWebConsoleTools_static
				)
			# In case of standalone builds, we need to pull in some other libraries
			if(DEFINED JVX_SDK_PATH)
				include(${JVX_CMAKE_DIR}/cmake-sdk/cmake-lib-packages.consolehost.cmake)
				include(${JVX_CMAKE_DIR}/cmake-sdk/cmake-lib-packages.network.cmake)
			endif()
			force_console_app()
		endif(JVX_LINK_WITH_CONSOLE_HOST)
	endif(JVX_LINK_WITH_DEVELOP_HOST)