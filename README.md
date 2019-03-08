
# Dyne ?

**Dyne** is a C++ library for creating games and applications, it is still under development and is lacking of many features.


# Why ?

Well, the main purpose of this project was to improve my programming knowledge. This is the first answer that comes in my mind, but of course, it is more complicated than that.

To make it short: On day i've wondered how computers managed to render things on the screen so generecally, like how do you tell the computer to render a house easily. Then i've read an article that was talking about vertices and how graphic cards works, and it was really interesting so i first learned DirectX3D but switched to OpenGL really quickly because it was cross-platform and more interesting. At this point i got the idea of creating a simple game engine, to learn OpenGL and the GLFW library. Then it was just about improving it, and Dyne is the new and latest version.

# Installation

Dyne currently compiles on Linux, will soon on Windows. It does on MacOs but nothing renders, i dont know why, so i will focus on Linux and Windows for now.

Dyne uses C++17 (The 2017 standard of C++).

Dyne requires some libraries in order to work, but they dont need to be installed:

- OpenGL (Graphic library API)
- Glad   (OpenGL loader)
- GLFW   (Window and event library)
- OpenAL (3D audi API)
- dr_wav (header only library for loading WAV files)
- tiny_obj_loader (header only library for loading OBJ files)
- stb_image (header only library for loading images)

Now go to the build directory (`mkdir build` if it doesn't exist) then execute `cmake ..`, a Makefile will be generated; do `make` and then `sudo make install`. 

- Now, the Dyne library must have been installed, you can start using it.

## Example

Let's first start with a 'Hello World' example.

```C++

#include "dn/Application.hpp"
#include "dn/Window.hpp"

int main()
{
  dn::Window window(600, 500, "Hello world");
  
  return dn::Application::run();
}

```

Compile the example `g++ -std=c++17 example.cpp -Ipath/to/include/of/dyne`

And voila, these two lines of codes creates a window, and shows it.

In the really first two line we've included the *Application.hpp* and *Window.hpp* files, we need them in order to create a window
```C++
dn::Window window(600, 500, "Window Title");
```
and run the application
```C++
return dn::Application::run();
```
