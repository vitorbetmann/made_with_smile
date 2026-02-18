cmake_minimum_required(VERSION 4.0.2)

# ----------------------------
# Set proj name from root name
# ----------------------------
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES C)

# --------
# Busywork
# --------
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(sources.cmake)
add_executable(${PROJECT_NAME} ${SOURCES})

# ------------
# Raylib setup
# ------------
set(RAYLIB_DIR "$ENV{HOME}/_dev/raylib")
set(RAYLIB_SRC_DIR "${RAYLIB_DIR}/src")
set(RAYLIB_LIB_PATH "${RAYLIB_SRC_DIR}") # Defaults to native build

# -------------------------
# Platform specific configs
# -------------------------
if (EMSCRIPTEN)
    set(RAYLIB_LIB_PATH "${RAYLIB_DIR}/build_web/raylib")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}
        -s USE_GLFW=3
        -s ASSERTIONS=1
        -s ALLOW_MEMORY_GROWTH=1
        -s WASM=1
        -s ASYNCIFY
        -s GL_ENABLE_GET_PROC_ADDRESS=1
        -s EXPORTED_RUNTIME_METHODS=['ccall','HEAPF32']
        --preload-file ../assets@assets
        --shell-file ${RAYLIB_SRC_DIR}/minshell.html
        ")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WEB)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
elseif (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            "-framework IOKit"
            "-framework Cocoa"
            "-framework CoreFoundation")
endif ()

# --------------------------------------------
# Apply include and library settings to target
# --------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_SRC_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(${PROJECT_NAME} PRIVATE "${RAYLIB_LIB_PATH}")
target_link_libraries(${PROJECT_NAME} PRIVATE "raylib")


## Include the SMILE headers
#target_include_directories(${PROJECT_NAME} PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/smile/include
#)
#
## Link with the SMILE static library
#target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/smile/build/libsmile.a)


# Add Smile as a subdirectory
add_subdirectory(smile)

# Include Smile headers
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/smile/include
)

# Link against the Smile static library
target_link_libraries(${PROJECT_NAME} PRIVATE smile)