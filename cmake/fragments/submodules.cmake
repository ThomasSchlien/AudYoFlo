	# Obtain submodule list
  set(JVX_SUBMODULE_LIST "" CACHE STRING "Defined submodule list")
  # If provided, load submodule list
  message("------> ${JVX_BINARY_DIR}/submodulelist.txt")
  if(EXISTS ${JVX_BINARY_DIR}/submodulelist.txt)
	include(${JVX_BINARY_DIR}/submodulelist.txt)
	message("##> Submodule list: ${mysubmodules}")
  else()
	set(mysubmodules ${JVX_SUBMODULE_LIST})
  endif()
  
  message("<< Checking for submodule settings in folder <${JVXRT_SUBMODULE_PATH}> >>")
	if(mysubmodules)
		message("<< Selected submodules: <${mysubmodules}> >>")
	endif()
	if(ignsubmodules)
		message("<< Ignored submodules: <${ignsubmodules}> >>")
	endif()
  	
	# message(FATAL_ERROR "Hier")
		
	set(JVX_CONFIGURED_SUBMODULES_PRE "")
	SUBDIRLIST(SUBDIRS ${JVXRT_SUBMODULE_PATH})

	message ("--> Sub directories to be evaluated: ${SUBDIRS}")
	
	# LABEL ADD SUB_PROJECTS HERE!
	FOREACH(subdir ${SUBDIRS})
		if(mysubmodules)
			message("++> Look for ${subdir} in list of allowed submodules: \"${mysubmodules}\"")
			list(FIND mysubmodules ${subdir} ifoundit)
			if(${ifoundit} GREATER -1)
				if(EXISTS ${JVXRT_SUBMODULE_PATH}/${subdir}/.jvxprj.base OR EXISTS ${JVXRT_SUBMODULE_PATH}/${subdir}/.jvxprj.audio OR EXISTS ${JVXRT_SUBMODULE_PATH}/${subdir}/.jvxprj)
					set(JVX_CONFIGURED_SUBMODULES_PRE "${JVX_CONFIGURED_SUBMODULES_PRE};${subdir}")
				else()
					message("|--> .jvxprj.base|.jvxprj.audio|.jvxprj not found in ${JVXRT_SUBMODULE_PATH}/${subdir}, NOT Building folder.")
				endif()
			else()
				message("|--> Project ${JVXRT_SUBMODULE_PATH}/${subdir} is not in list for allowed submodules.")
			endif()
		else()
			if(EXISTS ${JVXRT_SUBMODULE_PATH}/${subdir}/.jvxprj.base OR EXISTS ${JVXRT_SUBMODULE_PATH}/${subdir}/.jvxprj.audio OR EXISTS ${JVXRT_SUBMODULE_PATH}/${subdir}/.jvxprj)
				set(JVX_CONFIGURED_SUBMODULES_PRE "${JVX_CONFIGURED_SUBMODULES_PRE};${subdir}")
			else()
				message("|--> .jvxprj.base|.jvxprj.audio|.jvxprj not found in ${JVXRT_SUBMODULE_PATH}/${subdir}, NOT Building folder.")
			endif()
		endif()
	ENDFOREACH()
	
	message("##> Step 1: Pre-selected submodules: ${JVX_CONFIGURED_SUBMODULES_PRE}")
	if(ignsubmodules)	
		FOREACH(entry ${JVX_CONFIGURED_SUBMODULES_PRE})
		
			# message("Look for ${entry} in list of ignored submodules: \"${ignsubmodules}\"")
			list(FIND ignsubmodules ${entry} ifoundit)
			if(${ifoundit} GREATER -1)
				# Nothing, ignoring
				message("|--> Project ${JVXRT_SUBMODULE_PATH}/${entry} is in list for ignored submodules - not building it.")
			else()				
				set(JVX_CONFIGURED_SUBMODULES "${JVX_CONFIGURED_SUBMODULES};${entry}")
			endif()
		ENDFOREACH()
	else()
		set(JVX_CONFIGURED_SUBMODULES "${JVX_CONFIGURED_SUBMODULES_PRE}")
	endif()		

	# The second variable may still be in use somewhere!
	set(JVX_CONFIGURED_AUDIO_SUBMODULES ${JVX_CONFIGURED_SUBMODULES})

	FOREACH(subdir ${JVX_CONFIGURED_SUBMODULES})
		message("XX> Building sub project in folder ${JVXRT_SUBMODULE_PATH}/${subdir}")
		set(JVX_FOLDER_HIERARCHIE_BASE_OLD ${JVX_FOLDER_HIERARCHIE_BASE})
		set(JVX_FOLDER_HIERARCHIE_BASE "${JVX_FOLDER_HIERARCHIE_BASE}/sub-projects/${subdir}")		
		add_subdirectory(${JVXRT_SUBMODULE_PATH}/${subdir} ${JVXRT_SUBPROJECTS_PATH_MAP}/${subdir})
		set(JVX_FOLDER_HIERARCHIE_BASE ${JVX_FOLDER_HIERARCHIE_BASE_OLD})
	ENDFOREACH()
	