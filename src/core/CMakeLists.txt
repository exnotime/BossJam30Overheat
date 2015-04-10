# Recursivly add source files in the subfolders selected
file(GLOB_RECURSE SOURCES
	"*.cpp"
	"*.h"
	"*.hpp"
	"*/*.cpp"
	"*/*.h"
	"*/*.hpp"
)

# Generate source groups depending on folders (creates Visual Studio filters)
set(RELPATH ${ProjectRoot}/src/)
get_filename_component(RELPATH ${RELPATH} ABSOLUTE)
foreach(f ${SOURCES})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR ${RELPATH} ${f})
    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()


SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH
	"$ORIGIN/../../../lib/")

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# the RPATH to be used when installing, but only if it's not a system directory
#LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
#IF("${isSystemDir}" STREQUAL "-1")
#   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#ENDIF("${isSystemDir}" STREQUAL "-1")

# Make executable from main.cpp and sources listed above
add_executable(${CMAKE_PROJECT_NAME} Main.cpp ${SOURCES})
# Link libraries to the executable
target_link_libraries(${CMAKE_PROJECT_NAME} optimized ${SFMLMainLib} ${SFMLWindowLib} ${SFMLSystemLib} ${SFMLGraphicsLib} ${SFMLAudioLib} debug ${SFMLMainLibDebug} ${SFMLWindowLibDebug} ${SFMLSystemLibDebug} ${SFMLGraphicsLibDebug} ${SFMLAudioLibDebug})

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin/${OperatingSystemNameLowerCase}/${TargetArchitecture})
