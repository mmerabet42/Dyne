
# Dyne ?

**Dyne** is the biggest project i have made until now. It is supposed to be a general purpose engine, in which you can create window applications of any kind, and also 2D and 3D games most importantly.

In the current version you can create any kind of applications with a minimum of abstraction, meaning that you dont have to do some low-level thing in order to work with the engine.

# Why ?

Well, there was no specific goal except that it was just for learning and improving my current knowledge, until i reached a point that i wanted to make a real game engine that can be used to create any kind of game.

I've used the Unity3D engine for a year and i really liked the way it abstracted things using GameObjects and Components, so once i learned OpenGL and GLFW i wanted to reimplement that system.

I also heard about the ECS of Unity that uses data-oriented programming, which is really great and interesting for performance. So obviously, will come a point, were i will try to implement it.

# Installation

Dyne currently compiles on Linux, will soon in Windows. It does on MacOs but nothing renders, i dont know why, so i will focus on Linux and Windows for now.

Dyne requires some libraries in order to work:

- GLEW (OpenGL loader)
- GLFW (to create and manage windows)
- OpenAL (to manage 3D sound)
- sndfile (to open and read WAV files)

So once you have the required libraries you can compile the Dyne library:

```bash
$> make
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
