# Soft-body-simulator

## Description
The program, written in C++ is a simple simulation of a soft body. It is modeled as a
spring-masspoint system with linear force model. The physics are implemented as a time-driven simulation, in particular
collisions and the Newtonian differential equations.

![](sbs.gif)
### Visualization
The visualisation is made with SFML - an OpenGL based 2D graphics library. *Some of the header
and source files in the repository are related to the pure OpenGL and therefore are deprecated.*

### Physics
The collision detection is using the sweep and prune method, a simple and effective method
to implement. The collision solving is a simple time-driven simulation. The interaction between the masspoints
throughout the spring, is solved with Runge-Kutta 4 method. Each masspoint may have its own damping,
radius, etc ... A masspoint can also hae an arbitrary number of springs attached to it.
The gravity is acting on all masspoints and can be changed during the runtime.
The configuration is created in the System's class in the method config1().

### Configuration for Linux
In order to run the programm properly, you must have installed `sfml` and other OpenGL dependencies,
i.e. `glfw`, `GLEW` (everything can be seen in the `./src/CMakeLists.txt` file). In the main directory the project must be built using CMake.