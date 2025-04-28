# Create vec3d library
add_library(vec3d STATIC
    vec3d/vec3d.cc
    vec3d/vec3d.h
)

# Create core library
add_library(corecode STATIC
    core.cpp
    core.hpp
)

# Create czm_face library
add_library(czm_face STATIC
    czm_face/czm_face.cpp
    czm_face/czm_face.hpp
    czm_face/edge.cpp
    czm_face/edge.hpp
    czm_face/czm_point.cpp
    czm_face/czm_point.hpp
)

# Create executable target
add_executable(corecode_app
    main.cpp
)

# Link executable with libraries
target_link_libraries(corecode_app
    PRIVATE
        corecode
        vec3d
        czm_face
)

# Set include directories
target_include_directories(corecode
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(vec3d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(czm_face
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set compile options based on compiler
if(MSVC)
    target_compile_options(corecode
        PRIVATE
            /W4     # Warning level 4
            /WX     # Treat warnings as errors
    )
    target_compile_options(vec3d
        PRIVATE
            /W4     # Warning level 4
            /WX     # Treat warnings as errors
    )
    target_compile_options(czm_face
        PRIVATE
            /W4     # Warning level 4
            /WX     # Treat warnings as errors
    )
else()
    target_compile_options(corecode
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
    target_compile_options(vec3d
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
    target_compile_options(czm_face
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif() 