cmake_minimum_required(VERSION 3.21)
project(AlgViz LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(AlgViz 
    src/Node.h
    src/Box.h
    src/Algorithm.h
    src/Mouse.h
    src/Entity.h
    src/Search.h
    src/App.h
    src/Button.h
    src/sort_alg.h
    src/array.h
    src/Sort.h
    src/State.h
    
    src/Node.cpp 
    src/Box.cpp 
    src/Algorithm.cpp 
    src/Mouse.cpp 
    src/Entity.cpp 
    src/Search.cpp
    src/App.cpp
    src/main.cpp
    src/Home.cpp
    src/Button.cpp
    src/sort_alg.cpp
    src/array.cpp
    src/Sort.cpp
)

target_include_directories(AlgViz PRIVATE src)
target_link_libraries(AlgViz PRIVATE sfml-graphics)
target_compile_features(AlgViz PRIVATE cxx_std_20)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET AlgViz POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:AlgViz> $<TARGET_FILE_DIR:AlgViz> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS AlgViz)
