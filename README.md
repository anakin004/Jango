
# Jango Engine 

## What's Being Worked On
- **Full 3D Renderer** 
- **2D Renderer**
- **Physics Libraries Integration**:
  - [Box2D](https://box2d.org/)
  - [PhysX](https://github.com/NVIDIAGameWorks/PhysX)
- **Multiplayer Networking Support** (planned after)

> **Note:**  
> Some files may still reference the old engine name (**Crimson**). This will be updated as development continues.

---

## 📢 Stay Tuned
Follow the repository for updates —  

Jango is an open-source game engine currently under development including 2D and 3D environments
imported tools used are found in the Crimson/vendor directory

---

## 🚀 Features (so far)

- **Cross-Platform Support**: Designed to run on multiple platforms.
- **Spdlog**: logging debug and program-tracing info
- **ImGui**: UI for runtime testing
- **GLFW**: Used to create windows, contexts, receiving input, and call-backs
- **Glad**: loading OpenGL functions into Jango
- **Math Library**: Developed my own math library, [Chroma](https://github.com/ryan-mangeno/Chroma)
  relevant snipets and inspiration accredited to the YouTube channel GetIntoGameDev
  - **Compiler Support (Work in Progress)**: 
  - GCC, Cmake, MSVC support SIMD operations
  - working on including more
- **Physx**: Physx Library with optional nvidia gpu acceleration
- **yaml-cpp**: config files and assets managment
- **assimp**: model loader
- **imguizmo**: ui to interact with objects
- **entt**: used for entity management





![demoo3](https://github.com/user-attachments/assets/2a36ba50-847e-4a23-84b6-29af4efa2b2f)
![demobonnie](https://github.com/user-attachments/assets/af94219a-d3e7-4e6a-a7ab-1f6dcc44b066)




---

## 🛠️ Getting Started

### Prerequisites
Before building Jango, ensure your system meets the following requirements:

- **C++ Compiler**: Supports C++17 or higher (GCC or MSVC recommended)
- **Premake**: Included in vendor folder
- **Git**: For cloning the repository and managing submodules

---

### Installation

Follow these steps to set up the project:

1. **Clone the Repository**:

   Clone Jango along with its submodules:
   ```bash
   git clone --recursive https://github.com/anakin004/Jango.git

### Generate Project Files

Navigate to the repository directory and execute the provided script:  
```bash
cd Jango
./GenerateProjects.bat
```
### Building

Currently toned towards msvc, 
will soon include docs for cmake, gcc, etc


## 💻 Contributing

I welcome contributions to Jango! To contribute:  
1. Fork the repository 
2. Create a new branch for your feature or fix
3. Commit your changes with detailed messages
4. Submit a pull request  
