# Celestial

A C++17 library for orbital mechanics with Python bindings using nanobind.

## Architecture

```text
Celestial/
├── Kepler/
│   ├── CMakeLists.txt
│   ├── HarmoniMundi/
│   │   ├── CMakeLists.txt
│   │   ├── OrbitTypes.hpp
│   │   └── *.hpp / *.cpp
│   └── python/
│       ├── CMakeLists.txt
│       ├── bindings.cpp
│       └── test.py
└── third_party/
    └── eigen/
```

- **HarmoniaMundi/** — C++ orbital mechanics implementations.
- **python/** — Python bindings built with nanobind.
- **third_party/** — External dependencies (Eigen).

## Build

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install nanobind

cmake -S Kepler -B build -DBUILD_PYTHON_BINDINGS=ON
cmake --build build
```

## Python Test

```bash
PYTHONPATH="$PWD/build/python" python Kepler/python/test.py
```

## Dependencies

C++17, CMake, Eigen3, Python 3.10+, nanobind.
