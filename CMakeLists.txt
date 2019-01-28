cmake_minimum_required(VERSION 3.3)
project("Dyne")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -Wno-unused-parameter")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fsanitize=address")

include_directories("include")

# Application source directory
set(SRC_Application
		src/Application/Application.cpp
		src/Application/Callbacks.cpp
		src/Application/Init.cpp
		src/Application/WindowManagement.cpp
		src/Application/DependentsManagement.cpp
		src/Application/ApplicationDependent.cpp)
# list(TRANSFORM SRC_Application PREPEND "srcs/Application")

# Window source directory
set(SRC_Window
		src/Window/Window.cpp
		src/Window/Window2.cpp
		src/Window/CallbackSetters.cpp)

# Shader source directory
set(SRC_Shader
		src/Shader/Shader.cpp
		src/Shader/DefaultShader.cpp)

# Model source directory
set(SRC_Model
		src/Model/Model.cpp
		src/Model/Models.cpp)

# Math source directory
set(SRC_Math
		src/Math/SmoothDamp.cpp
		src/Math/Random.cpp)

# Object source directory
set(SRC_Object
		src/Object/Object.cpp
		src/Object/UComponent.cpp
		src/Object/Component.cpp
		src/Object/Transform.cpp
		src/Object/Camera.cpp
		src/Object/Mesh.cpp)

# Texture source directory
set(SRC_Texture
		src/Texture/Texture.cpp)

# Audio source directory
set(SRC_Audio
		src/Audio/AudioListener.cpp
		src/Audio/AudioSource.cpp
		src/Audio/Audio.cpp)

# utils source directory
set(SRC_utils
		src/Utils/Utils.cpp)

# Scene source directory
set(SRC_Scene
		src/Scene/Scene.cpp
		src/Scene/ModelInstance.cpp)

# Engine source directory
set(SRC_Engine
		src/Engine/Engine.cpp
		src/Engine/RenderEngine.cpp)

set(SRC_glad
		src/glad/glad.c)

set(SOURCES
	${SRC_Application}
	${SRC_Window}
	${SRC_Shader}
	${SRC_Model}
	${SRC_Math}
	${SRC_Object}
	${SRC_Texture}
	${SRC_Audio}
	${SRC_utils}
	${SRC_Scene}
	${SRC_Engine}
	${SRC_glad})

add_library(dyne SHARED ${SOURCES})

install(TARGETS dyne DESTINATION "/usr/lib")

target_link_libraries(dyne glfw3)
target_link_libraries(dyne GL)
target_link_libraries(dyne openal)
target_link_libraries(dyne X11)
