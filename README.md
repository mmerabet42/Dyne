
# Dyne ?

**Dyne** is a C++ library for creating games and applications, it is still under development and is lacking of many features.

# Why ?

Well, the main purpose of this project was to improve my programming knowledge. This is the first answer that comes in my mind, but of course, it is more complicated than that.

To make it short: On day i've wondered how computers managed to render things on the screen so generecally, like how do you tell the computer to render a house easily. Then i've read an article that was talking about vertices and how graphic cards works, and it was really interesting so i first learned DirectX3D but switched to OpenGL really quickly because it was cross-platform and more interesting. At this point i got the idea of creating a simle game engine, to learn OpenGL and the GLFW library (everyone does that). Then it was just about improving it everytime, and Dyne is the new and latest version.

# Installation

Dyne currently compiles on Linux, will soon in Windows. It does on MacOs but nothing renders, i dont know why, so i will focus on Linux and Windows for now.

Dyne requires some libraries in order to work:

- GLEW (OpenGL loader)
- GLFW (to create and manage windows)
- OpenAL (to manage 3D sound)

And uses these libraries but you dont need to install them:

- dr_wav (header only library for reading WAV files)
- tiny_obj_loader (header only library for reading OBJ files)
- stb_image (header only library for reading images)

So once you have the required libraries you can compile the Dyne library:

- We need a build directory, so if it doesn't exist, you need to create it: `mkdir build`.
- Then use this command to compile the library.

```bash
> (cd build; cmake ..; make; sudo make install)
```


This command will generate the library we are looking for 'libdn.a', we will use it to compile our projects.

## Example

Let's first start with a simple example, that shows a window.

```C++

#include "dn/Application.hpp"
#include "dn/Window.hpp"

int main()
{
  dn::Window window(600, 500, "Window Title");
  
  return dn::Application::run();
}

```

And voila, these two lines of codes creates a window, and shows it.

In the really first two line we've included the *Application.hpp* and *Window.hpp* files, we  need them in order to create a window
```C++
dn::Window window(600, 500, "Window Title");
```
and run the application
```C++
return dn::Application::run();
```
