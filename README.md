
# Dyne ?

**Dyne** is a general purpose engine in which you can create window applications, 2D and 3D applications.

# Why ?

My first goal 

As i said the main goal was just to improve my C++ knownledge by creating a productive and decent user interface in which it would be simple to create an object and place it in a 3D environement and move it around, and create other objects, assign textures etc.

But it got so interesting over time that i wanted to create a **real working game engine** that can be used to create any kind of game.

Well, i am not planning to compete with Unity and Unreal Engine or other existing engines, of course it stays a 'personnal' and 'educative' project.

But ... you know, i wanted to see how far **i could go**.

# Installation

Dyne uses the GLFW, GLEW and OpenAL libraries, so you have to install them.

```bash
$> make
```

And that is all, it generated a 'libdn.a' file, which is the library.

## Example

Let's first start with an example code to see how simple it is to create a window and catch some events

```C++

#include "dn/Application.hpp"
#include "dn/Window.hpp"

int main()
{
  dn::Window window(600, 500, "Window Title");
  
  window->keyEvent.addListener([](dn::Window *w, dn::KeyCode keyCode, dn::Action action) {
   
   if (action == dn::Action::press)
    std::cout << "Key pressed : " << dn::KeyCode::getName(keyCode) << std::endl;
   else if (action == dn::Action::repeat)
    std::cout << "Key repeat : " << dn::KeyCode::getName(keyCode) << std::endl;
   else if (action == dn::Action::release)
    std::cout << "Key released : " << dn::KeyCode::getName(keyCode) << std::endl;
    
  });
  
  return dn::Application::run();
}

```
