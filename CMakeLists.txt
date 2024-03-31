cmake_minimum_required(VERSION 3.12)
project("Game-Engine-2D")

set(CMAKE_CXX_STANDARD 20)

# Header files
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Create executable with the source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
add_subdirectory(vendor/glfw-3.3.2)			# window opener
add_subdirectory(vendor/glad)				# opengl loader
add_subdirectory(vendor/stb_image)			# loading immaged
add_subdirectory(vendor/stb_truetype)		# loading ttf files
add_subdirectory(vendor/glm)				# math
add_subdirectory(vendor/imgui-docking)		# ui


# Debug configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -D_UNICODE -DUNICODE")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Set configuration to Debug")
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG _UNICODE UNICODE)
    target_link_libraries(${PROJECT_NAME} glad imgui glm opengl32)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
else()
    # Release configuration
    message("Set configuration to Release")
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Release)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE UNICODE)
    target_link_libraries(${PROJECT_NAME} glad imgui glm opengl32)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:wWinMainCRTStartup")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS_RELEASE "_WINDOWS")
endif()
