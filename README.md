# Iron Dust
**This is the birth of a new 3d tank shooter**

----

## Some words about the OBJ loader from the OpenGL Tutorial:

This one is a real asshole. Like the original author mentioned it can't do shit!
Do REALLY search for a better one!

## Some things to consider about exporting .obj files if we use this loader:

### Create fucking UV coordinates or it won't work, in Blender:
 - When you have a model: switch to Edit Mode
 - Mesh -> UV Unwrap -> Unwrap

### Exporting Options:

 File -> Export -> Wavefront (.obj)

 - Selection only
 - Write Normals
 - Include UVs (don't fuck with this one)
 - Triangulate Faces (if you don't use this, Blender will export Quads and your model will look like swiss cheese)

## Get it runnig
### Requirements
- OpenGL
- [glm](http://glm.g-truc.net/0.9.6/index.html) >= 0.9.6 - header-only math library for matrix operations
- [glfw](http://www.glfw.org/) >= 3.0 - library for opengl windows, events and input handling
- [libcg](https://github.com/HymiR/libcg) >= 0.2.3 **NOTE - currently only the gerfried branch is compatible!!**

### Build
This is done the good old straight way:
```bash
./make
./irondust
```
