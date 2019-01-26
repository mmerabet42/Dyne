cmake_minimum_required(VERSION 3.3)
project("Dyne")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -Wno-unused-parameter")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address")

include_directories("includes")

# Application source directory
set(SRC_Application
		srcs/Application/Application.cpp
		srcs/Application/Callbacks.cpp
		srcs/Application/Init.cpp
		srcs/Application/WindowManagement.cpp
		srcs/Application/DependentsManagement.cpp
		srcs/Application/ApplicationDependent.cpp)
# list(TRANSFORM SRC_Application PREPEND "srcs/Application")

# Window source directory
set(SRC_Window
		srcs/Window/Window.cpp
		srcs/Window/Window2.cpp
		srcs/Window/CallbackSetters.cpp)

# Shader source directory
set(SRC_Shader
		srcs/Shader/Shader.cpp
		srcs/Shader/DefaultShader.cpp)

# Model source directory
set(SRC_Model
		srcs/Model/Model.cpp
		srcs/Model/Models.cpp)

# Math source directory
set(SRC_Math
		srcs/Math/SmoothDamp.cpp
		srcs/Math/Random.cpp)

# Object source directory
set(SRC_Object
		srcs/Object/Object.cpp
		srcs/Object/UComponent.cpp
		srcs/Object/Component.cpp
		srcs/Object/Transform.cpp
		srcs/Object/Camera.cpp
		srcs/Object/Mesh.cpp)

# Texture source directory
set(SRC_Texture
		srcs/Texture/Texture.cpp)

# Audio source directory
set(SRC_Audio
#		srcs/Audio/AudioSource.cpp
#		srcs/Audio/AudioListener.cpp
		srcs/Audio/Audio.cpp)

# utils source directory
set(SRC_utils
		srcs/Utils/Utils.cpp)

# Scene source directory
set(SRC_Scene
		srcs/Scene/Scene.cpp
		srcs/Scene/ModelInstance.cpp)

# Engine source directory
set(SRC_Engine
		srcs/Engine/Engine.cpp
		srcs/Engine/RenderEngine.cpp)

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
	${SRC_Engine})

add_library(dyne SHARED ${SOURCES})

install(TARGETS dyne DESTINATION /usr/lib)

target_link_libraries(dyne glfw3)
target_link_libraries(dyne GLEW)
target_link_libraries(dyne GL)
target_link_libraries(dyne openal)
target_link_libraries(dyne sndfile)
