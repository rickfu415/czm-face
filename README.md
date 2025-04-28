# CoreCodeRD

A modern C++ project template for research and development purposes.

## Project Structure

```
.
├── CMakeLists.txt          # Main CMake configuration
├── src/                    # Source files
│   ├── CMakeLists.txt     # Source CMake configuration
│   ├── core.hpp           # Core header file
│   └── core.cpp           # Core implementation
└── tests/                  # Test files
    ├── CMakeLists.txt     # Test CMake configuration
    └── core_tests.cpp     # Unit tests
```

## Requirements

- CMake 3.15 or higher
- C++17 compatible compiler
- Google Test (for testing)

## Building the Project

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run tests
ctest
```

## Development

This project uses modern C++ features and follows these guidelines:
- C++17 standard
- RAII principles
- Move semantics
- Smart pointers
- Unit testing with Google Test

## License

This project is licensed under the MIT License - see the LICENSE file for details. 