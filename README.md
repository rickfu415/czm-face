# CoreCodeRD

A modern C++ project template for research and development purposes.

## Project Structure

```
.
├── CMakeLists.txt
├── README.md
├── .gitignore
└── src/
    ├── CMakeLists.txt
    ├── main.cpp
    ├── core.cpp
    ├── core.hpp
    ├── vec3d/
    │   ├── vec3d.cc
    │   └── vec3d.h
    └── czm_face/
        ├── czm_face.cpp
        ├── czm_face.hpp
        ├── edge.cpp
        ├── edge.hpp
        ├── czm_point.cpp
        └── czm_point.hpp
```

## Features

- Modern C++ project structure using CMake
- Vector3D implementation for 3D geometry
- Face and Edge classes for geometric operations
- Multiple point generation methods:
  - Edge points only
  - Interior points only
  - Uniform grid points
  - Edge and interior points combined
  - Equal area points (new)

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

The project provides several geometric operations and point generation methods:

### Face Operations
- Create faces from 3 or 4 vertices
- Calculate face area, perimeter, and center
- Generate points on faces using different methods

### Point Generation Methods
1. Edge Points Only: Generates points only on the edges of the face
2. Interior Points Only: Generates points only in the interior of the face
3. Uniform Grid: Generates points in a uniform grid pattern
4. Edge and Interior: Combines both edge and interior points
5. Equal Area Points: Generates interior points where each point occupies an equal area

### Example

```cpp
// Create a face
std::vector<Vec3D> vertices = {
    Vec3D(0, 0, 0),
    Vec3D(1, 0, 0),
    Vec3D(1, 1, 0),
    Vec3D(0, 1, 0)
};

czm_face::CzmFace face;
face.createFace(vertices);

// Generate points with equal area distribution
int numPoints = 16; // Example: 4x4 grid
auto points = face.generateEqualAreaPoints(numPoints);
```

## Dependencies

- C++17 or later
- CMake 3.10 or later

## License

This project is licensed under the MIT License - see the LICENSE file for details. 