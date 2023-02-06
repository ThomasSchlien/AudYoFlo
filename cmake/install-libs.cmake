set(JVX_INSTALL_EXTERNAL_LIBS TRUE)

macro(find_boost) 
  message("--> Looking for boost, lib path = ${BOOST_LIBRARY_PATH}")
	if(NOT BOOST_LIBRARY_PATH)
		message("Boost location taken from env variable")
		set(BOOST_LIBRARY_PATH $ENV{BOOST_LIBRARY_PATH})
	endif()
  set(BOOST_INCLUDEDIR_OSGUESS ${BOOST_LIBRARY_PATH}/boost)
  message("Boost OS GUESS PATH: ${BOOST_LIBRARY_PATH}/boost")
  find_path (BOOST_INCLUDEDIR config.hpp PATHS "${BOOST_INCLUDEDIR_OSGUESS}")

  if(BOOST_INCLUDEDIR)
    set(BOOST_FOUND TRUE)
	set(BOOST_INCLUDEDIR "${BOOST_INCLUDEDIR}/..")
    message("    include path: ${BOOST_INCLUDEDIR}")
  else()
    set(BOOST_FOUND FALSE)
    message(FATAL_ERROR "    lib boost not available, you need to specify the location in environment variable BOOST_LIBRARY_PATH.")
  endif()
endmacro (find_boost)

macro(find_eigen)
  message("--> Looking for Eigen")
  if(NOT EIGEN_LIBRARY_PATH) 
	set(EIGEN_LIBRARY_PATH $ENV{eigen_LIBRARY_PATH})
  endif()
  set(EIGEN_INCLUDEDIR_OSGUESS ${EIGEN_LIBRARY_PATH}/Eigen)
  find_path (EIGEN_INCLUDEDIR Core PATHS "${EIGEN_INCLUDEDIR_OSGUESS}")

  if(EIGEN_INCLUDEDIR)
    set(EIGEN_FOUND TRUE)
	set(EIGEN_INCLUDEDIR "${EIGEN_INCLUDEDIR}/..")
    message("    include path: ${EIGEN_INCLUDEDIR}")
  else()
    set(EIGEN_FOUND FALSE)
    message(FATAL_ERROR "    lib Eigen not available, you need to specify the location in environment variable EIGEN_LIBRARY_PATH.")
  endif()
endmacro (find_eigen)