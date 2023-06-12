Talha Hussain, MyRaceTracingProjectAssignmentTwo, Computer Science
Computer Graphics Project Assignment 2 Ray Tracing 2

Websites:
To complete my Computer Graphics Project Assignment 2 Ray Tracing 2, I received helpful inspiration from the following
websites shown below:
The Magic of the LookAt Matrix - https://medium.com/@carmencincotti/lets-look-at-magic-lookat-matrices-c77e53ebdf78
Reading: Geometry - https://cs.wellesley.edu/~cs307/readings/08-geometry.html
Depth of Field rendering in path tracting - https://medium.com/@elope139/depth-of-field-in-path-tracing-e61180417027
Refraction using Fresnel calculations - https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lecture13_0.pdf
 Multithreading:
 - https://en.cppreference.com/w/cpp/thread/thread
 - https://en.cppreference.com/w/cpp/thread/lock_guard

Usage: A make file has been included with the following commands.
make rtrace - Runs the compilation using the g++ compiler.
make clean - Cleans the intermediate files and compiled target.
After running make rtrace, choose one of the following make commands below to run and then make clean. Each .ppm File can be generated one at a time.
make teapot - Runs the compiled target using the teapot-3.nff file.
make stratified - Runs the compiled target using the teapot-3.nff file with a stratified sample size of 3.
make dof - Runs the compiled target using the teapot-3.nff file with a stratified sample size of 3 and aperture size of 0.5.
make refract - Runs the compiled target using the refract.nff file.
make phong - Runs the compiled target using the teapot-3.nff file with phong shading.

Summary: This project continued on from assignment 1. Adding in some structures to improve the code quality and allow for the lighting, shading, reflections,
and refraction. I also implemented anti-aliasing through the use of Stratified sampling and depth of field using a focal plane method. Lighting and shading
followed the code snippet provided and only required minor updates to the intersection to provide normal and positional values from the
intersection proper. With those I was able to determine the light intersection as well as smooth normals for the polygon patches. To perform reflection and
refraction I added two functions to the Vector3 class that calculated the resultant vector from the intersection and cast extra rays as necessary. Stratified
sampling was implemented by performing a nested for loop to send out a grid of rays each offset by the sampling value. A similar method was employed with the
depth of field but with the origin and not the direction being sampled multiple times. Both systems are independant and can work together. To improve the speed
of the rendering I added multithreading using the std::thread class from C++17. This greatly improved the testing of the code while providing the same results
as the single threaded system.

