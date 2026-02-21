# ATOMIC ORBITALS VISUALISER

# PROJECT ...

...

# DEPENDENCIES

The following dependencies are *already included*:
- **glad**
- **ImGui**

You *do not* need to install these two.

To build and run the project, you do **need to install the following dependencies**:
- **CMake (v3.10+)**
- **GLFW (v3.3+)**
- **GLM (OpenGL Mathematics)**

## LINUX INSTALLATION

Depending on your distribution, you can install the required packages using your system's package manager.

**Ubuntu / Debian:**
```
sudo apt install build-essential cmake libglfw3-dev libglm-dev
```

**Fedora:**
```
sudo dnf install cmake glfw-devel glm-devel
```

**Arch:**
```
sudo pacman -S base-devel cmake glfw glm
```

## WINDOWS INSTALLATION

The easiest way to install the required dependencies is via [vcpkg](https://vcpkg.io/en/):

1. **Install vcpkg:**
    Open PowerShell and run:
    ```
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    .\bootstrap-vcpkg.bat
    ```
2. **Install GLFW and GLM:**
    Run:
    ```
    .\vcpkg install glfw3 glm
    ```
3. **Link vcpkg to CMake:**
    When you will run the `cmake` command to build the project, you will need to 
    pass the correct toolchain file.
    It will look something like:
    ```
    cmake .. -DCMAKE_TOOLCHAIN_FILE="C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake"
    ```

# BUILD AND RUN

## COMPILE THE PROJECT

1. **Clone the repo**
    ```
    git clone https:...
    cd Atomic-Orbitals-Visualiser
    ```
2. **Build**
    Create a `build` directory:
    ```
    mkdir build
    cd build
    ```
    And compile the project:
    ```
    cmake ..
    make
    ```

## RUN IT

Run with:
```
./AtomSimulation
```
on linux, or:
```
.\AtomSimulation.exe
```
on Windows.

**NOTE:** On Windows, depending on your compiler, CMake might place the executable in a subfolder.
