set(PROJECT_NAME libsdl)
include(${JVX_CMAKE_DIR}/common_local_lib_head.cmake)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libsdl)
	message("libsdl sub project not available. Starting script to download it.") 
	execute_process(COMMAND ${mysh} -c "cd ${CMAKE_CURRENT_SOURCE_DIR} ; ./prepareModules-win.sh; exit")
	message("libsdl installation complete.")
endif()

set(SDL_LIBRARY_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/libsdl/SDL2-2.26.3" CACHE INTERNAL "libsdl lib path (windows)")
if(JVX_PLATFORM MATCHES "32bit")
	set(SDL_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/libsdl/SDL2-2.26.3/lib/x86/SDL2.lib" CACHE INTERNAL "libsdl lib (windows)")
else()
	set(SDL_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/libsdl/SDL2-2.26.3/lib/x64/SDL2.lib" CACHE INTERNAL "libsdl lib (windows)")
endif()