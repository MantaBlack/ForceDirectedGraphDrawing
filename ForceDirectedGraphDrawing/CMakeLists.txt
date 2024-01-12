# CMakeList.txt : CMake project for ForceDirectedGraphDrawing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ForceDirectedGraphDrawing")

set(PROJECT_ID, "ForceDirectedGraphDrawing")

set(GLAD_INCLUDE "D:/TOOLS/GLAD/include/")
set(GLFW_INCLUDE "D:/TOOLS/GLFW/include/")
set(GLFW_LIB "D:/TOOLS/GLFW/lib/")

set(HEADER_FILES
    ${GLAD_INCLUDE}/glad/glad.h
    ${GLFW_INCLUDE}/GLFW/glfw3.h
)

set(SOURCE_FILES
    "main.cpp"
)

add_executable(ForceDirectedGraphDrawing ${SOURCE_FILES})

# import OpenGL library
find_package(OpenGL REQUIRED)

# specify directories for external header files
target_include_directories(ForceDirectedGraphDrawing PRIVATE ${GLAD_INCLUDE} ${GLFW_INCLUDE})

# specify directories for external libraries
target_link_directories(ForceDirectedGraphDrawing PRIVATE ${GLFW_LIB})

# specify libraries to link
target_link_libraries(ForceDirectedGraphDrawing PRIVATE glfw3.lib ${OPENGL_gl_LIBRARY})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ForceDirectedGraphDrawing PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
