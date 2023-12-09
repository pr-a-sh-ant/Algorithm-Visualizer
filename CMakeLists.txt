cmake_minimum_required(VERSION 3.21)
project(AlgViz LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# set source directory
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
# set include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# set include files
set(INCLUDE_FILES
    ${INCLUDE_DIR}/Node.h
    ${INCLUDE_DIR}/Algorithm.h
    ${INCLUDE_DIR}/Mouse.h
    ${INCLUDE_DIR}/Entity.h
    ${INCLUDE_DIR}/Search.h
    ${INCLUDE_DIR}/App.h
    ${INCLUDE_DIR}/Button.h
    ${INCLUDE_DIR}/sort_alg.h
    ${INCLUDE_DIR}/array.h
    ${INCLUDE_DIR}/Sort.h
    ${INCLUDE_DIR}/State.h
    ${INCLUDE_DIR}/Home.h
    ${INCLUDE_DIR}/Animation.h
    ${INCLUDE_DIR}/Maze.h
    ${INCLUDE_DIR}/MazeBox.h
    ${INCLUDE_DIR}/Window.h
    ${INCLUDE_DIR}/SearchWindow.h
    ${INCLUDE_DIR}/SearchSpace.h
    ${INCLUDE_DIR}/HomeWindow.h
    # ${INCLUDE_DIR}/Box.h
)
# set source files
set(SOURCE_FILES_GG
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Mouse.cpp
    ${SOURCE_DIR}/Animation.cpp
    ${SOURCE_DIR}/Maze.cpp
    ${SOURCE_DIR}/MazeBox.cpp
    ${SOURCE_DIR}/Window.cpp
    ${SOURCE_DIR}/SearchWindow.cpp
    ${SOURCE_DIR}/Button.cpp
    ${SOURCE_DIR}/Search.cpp
    ${SOURCE_DIR}/Node.cpp
    ${SOURCE_DIR}/State.cpp
    ${SOURCE_DIR}/SearchSpace.cpp
    ${SOURCE_DIR}/App.cpp
    ${SOURCE_DIR}/HomeWindow.cpp
    # ${SOURCE_DIR}/Box.cpp
    # ${SOURCE_DIR}/Algorithm.cpp
    # ${SOURCE_DIR}/Entity.cpp
    # ${SOURCE_DIR}/sort_alg.cpp
    # ${SOURCE_DIR}/array.cpp
    # ${SOURCE_DIR}/Sort.cpp
    # ${SOURCE_DIR}/Home.cpp
)

add_executable(AlgViz 
    ${INCLUDE_FILES}
    ${SOURCE_FILES_GG}
)

include_directories(${INCLUDE_DIR})
target_link_libraries(AlgViz PRIVATE sfml-graphics)
target_compile_features(AlgViz PRIVATE cxx_std_20)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET AlgViz POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:AlgViz> $<TARGET_FILE_DIR:AlgViz> COMMAND_EXPAND_LISTS)
endif()

# copy Public folder to build directory
add_custom_command(TARGET AlgViz POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Public $<TARGET_FILE_DIR:AlgViz>/Public)

install(TARGETS AlgViz)
