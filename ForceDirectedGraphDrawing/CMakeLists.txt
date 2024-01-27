# CMakeList.txt : CMake project for ForceDirectedGraphDrawing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PROJECT_NAME "ForceDirectedGraphDrawing")

project (${PROJECT_NAME})

set(GLAD_INCLUDE "$ENV{TOOLS_DIR}/GLAD/include/")
set(GLFW_INCLUDE "$ENV{TOOLS_DIR}/GLFW/include/")
set(GLFW_LIB "$ENV{TOOLS_DIR}/GLFW/lib/")
set(SFML_INCLUDE "$ENV{SFML_DIR}/include/")
set(SFML_LIB "$ENV{SFML_DIR}/lib/")

set(SFML_LINK_LIBS
    sfml-graphics-d.lib
    sfml-window-d.lib
    sfml-system-d.lib
    freetype.lib
)

set(HEADER_FILES
    ${GLAD_INCLUDE}/glad/glad.h
    ${GLFW_INCLUDE}/GLFW/glfw3.h
    "IBufferObject.hpp"
    "IGraphGenerator.hpp"
    "IRenderer.hpp"
    "ElementBufferObject.hpp"
    "VertexBufferObject.hpp"
    "VertexArrayObject.hpp"
    "RendererOpenGL.hpp"
    "GridGraphGenerator.hpp"
    "ShaderObject.hpp"
    "IGraphDrawer.hpp"
    "SingleThreadGraphDrawerGL.hpp"
)

set(SOURCE_FILES
    "main.cpp"
    "glad.c"
    "ElementBufferObject.cpp"
    "VertexBufferObject.cpp"
    "VertexArrayObject.cpp"
    "RendererOpenGL.cpp"
    "GridGraphGenerator.cpp"
    "ShaderObject.cpp"
    "SingleThreadGraphDrawerGL.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# import OpenGL library
find_package(OpenGL REQUIRED)

# specify directories for external header files
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_INCLUDE} ${GLFW_INCLUDE} ${SFML_INCLUDE})

# specify directories for external libraries
target_link_directories(${PROJECT_NAME} PRIVATE ${GLFW_LIB} ${SFML_LIB})

# specify libraries to link
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3.lib ${OPENGL_gl_LIBRARY} ${SFML_LINK_LIBS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
