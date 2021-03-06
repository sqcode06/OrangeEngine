cmake_minimum_required(VERSION 3.12)

set(ENGINE_PROJECT_NAME OrangeEngineCore)

set(ENGINE_PUBLIC_INCLUDES 
	includes/OrangeEngineCore/Application.h
	includes/OrangeEngineCore/Event.h
	includes/OrangeEngineCore/Camera.h
	includes/OrangeEngineCore/Keys.h
	includes/OrangeEngineCore/Input.h
)

set(ENGINE_PRIVATE_INCLUDES 
	src/OrangeEngineCore/Window.h
	src/OrangeEngineCore/Graphics/OpenGL/Light/LightMaterial.h
	src/OrangeEngineCore/Graphics/OpenGL/Light/DirectionalLight.h
	src/OrangeEngineCore/Graphics/OpenGL/Light/PointLight.h
	src/OrangeEngineCore/Graphics/OpenGL/Light/SpotLight.h
	src/OrangeEngineCore/Graphics/OpenGL/Shader.h
	src/OrangeEngineCore/Graphics/OpenGL/VertexBuffer.h
	src/OrangeEngineCore/Graphics/OpenGL/VertexArray.h
	src/OrangeEngineCore/Graphics/OpenGL/IndexBuffer.h
	src/OrangeEngineCore/Graphics/OpenGL/Material.h
	src/OrangeEngineCore/Graphics/OpenGL/Texture.h
	src/OrangeEngineCore/Graphics/OpenGL/Renderer_OpenGL.h
	src/OrangeEngineCore/Modules/UIModule.h
	src/OrangeEngineCore/ResourceLoader.h
)

set(ENGINE_PRIVATE_SOURCES 
	src/OrangeEngineCore/Application.cpp
	src/OrangeEngineCore/Window.cpp
	src/OrangeEngineCore/Camera.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Light/DirectionalLight.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Light/PointLight.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Light/SpotLight.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Shader.cpp
	src/OrangeEngineCore/Graphics/OpenGL/VertexBuffer.cpp
	src/OrangeEngineCore/Graphics/OpenGL/VertexArray.cpp
	src/OrangeEngineCore/Graphics/OpenGL/IndexBuffer.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Material.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Texture.cpp
	src/OrangeEngineCore/Graphics/OpenGL/Renderer_OpenGL.cpp
	src/OrangeEngineCore/Modules/UIModule.cpp
	src/OrangeEngineCore/ResourceLoader.cpp
	src/OrangeEngineCore/Input.cpp
)

set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ENGINE_ALL_SOURCES}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)

add_subdirectory(../external/stb_image ${CMAKE_CURRENT_BINARY_DIR}/stb_image)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE stb_image)

set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_glfw.h
	../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp
	../external/imgui/imgui_demo.cpp
	../external/imgui/imgui_tables.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_draw.cpp
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)