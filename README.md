# Jango


<img src="https://github.com/user-attachments/assets/94f709bb-4abf-4543-8ba8-9663fa66020d" alt="Jango pxArt" width="800">



# Jango Engine 

# IMPORTANT: I decided to work in a development repository apart from this. There is going to be doing a big release of Jango in the upcomming weeks! It will be including a full 3D renderer, 3D renderer will likely come first and then the 2D renderer, libraries like Box2D, Physx, yaml-cpp, assimp, and some networking multiplayer stuff soon after! If you are seeing this watch my repository! I am very excited for this upcomming release! I changed the game engine's name to Jango, was previously Crimson, so that is why in the files you will see Crimson, not Jango

Jango is an open-source game engine currently under development including 2D and 3D environments
imported tools used are found in the Crimson/vendor directory

---

## 🚀 Features (so far)

- **Cross-Platform Support**: Designed to run on multiple platforms.
- **Spdlog**: logging debug and program-tracing info
- **ImGui**: UI for runtime testing
- **GLFW**: Used to create windows, contexts, receiving input, and call-backs
- **Glad**: loading OpenGL functions into Jango
- **Math Library**: Developed my own math library, Chroma(https://github.com/anakin004/Chroma)
  relevant snipets and inspiration accredited to the YouTube channel GetIntoGameDev
  - **Compiler Support (Work in Progress)**: 
  - GCC, Cmake, MSVC support SIMD operations
  - working on including more
## In Unreleased Jango
- **Physx**: Physx Library with optional nvidia gpu acceleration
- **yaml-cpp**: config files and assets managment
- **assimp**: model loader
- **imguizmo**: ui to interact with objects
- **entt**: used for entity management


## Sneak Peak of Jango(Not Released Yet) ( Demo as of January 21st 2025 )
https://github.com/user-attachments/assets/0956fbeb-b1f8-4321-8566-b559aefaa198

//
![image](https://github.com/user-attachments/assets/3523a365-1b1e-43f7-8b20-472e7b069025)








---

## 🛠️ Getting Started

### Prerequisites
Before building Jango, ensure your system meets the following requirements:

- **C++ Compiler**: Supports C++17 or higher (GCC or MSVC recommended)
- **CMake**: Version 3.15 or higher
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
