find_path(AUBIO_INCLUDE_DIR
  NAMES aubio/aubio.h
  PATHS "$ENV{HOME}/vcpkg/installed/arm64-osx/include"
)

find_library(AUBIO_LIBRARY
  NAMES aubio
  PATHS "$ENV{HOME}/vcpkg/installed/arm64-osx/lib"
)

if(AUBIO_INCLUDE_DIR AND AUBIO_LIBRARY)
  set(AUBIO_FOUND TRUE)
  set(AUBIO_LIBRARIES ${AUBIO_LIBRARY})
  set(AUBIO_INCLUDE_DIRS ${AUBIO_INCLUDE_DIR})
endif()

if(AUBIO_FOUND)
  add_library(aubio::aubio UNKNOWN IMPORTED)
  set_target_properties(aubio::aubio PROPERTIES
    IMPORTED_LOCATION ${AUBIO_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${AUBIO_INCLUDE_DIRS}
  )
else()
  message(FATAL_ERROR "Could not find aubio")
endif()

mark_as_advanced(AUBIO_INCLUDE_DIR AUBIO_LIBRARY)