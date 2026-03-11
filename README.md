# The Guild

A text-based RPG adventure game in the spirit of traditional roguelikes

Basic Gameplay UI with map, interaction messages and basic stats. An initial combat system allows Tavern pest control, but has its dangers.
<img width="1141" height="593" alt="Näyttökuva 2026-03-11 150340" src="https://github.com/user-attachments/assets/5b47ea25-b1e0-4f5b-a57a-47fbbb34935d" />

The inventory has a dedicated UI that displays the player's items and the selected item's description.
<img width="1144" height="433" alt="Näyttökuva 2026-03-11 150439" src="https://github.com/user-attachments/assets/388c32e6-bebe-49c2-9fdc-8f8fb8a81142" />

## Project Overview

**Author:** Sepe Ahtosalo (The Left Hand) 
**Development Started:** February 14, 2026  
**AI Assistant:** GitHub Copilot (Claude Sonnet 4) (The Right Hand)

This project is a learning project in C++ game development, an attempt at clean code architecture, modern C++20 features, and professional development practices.

## AI Collaboration Methodology
This project uses structured AI-assisted development. See [AI Guidelines](ai_guidelines/) for collaboration framework and methodology.

## Learning Objectives

This project serves as a comprehensive learning experience covering:

### C++ Programming Concepts
- **Modern C++20 Features**: Designated initializers, concepts, ranges, and other modern language features
- **Object-Oriented Design**: Class hierarchies, inheritance, and polymorphism through game entities
- **Memory Management**: Smart pointers, RAII principles, and efficient resource handling
- **Standard Library**: Use of STL containers, algorithms, and utilities

### Software Engineering Practices
- **CMake Build System**: Cross-platform build configuration and dependency management
- **Version Control**: Git workflow, branching strategies, and (hopefully :heart: )collaborative development
- **Code Organization**: Header/implementation separation, namespace usage, and modular design
- **Documentation**: Code comments, README files, and API documentation

### Game Development Fundamentals
- **Game Loop Architecture**: Turn-based mechanics and state management
- **Data-Driven Design**: Moving towards JSON-based item databases and configurable game content
- **Player Progression Systems**: Experience, leveling, and character advancement
- **Procedural Content**: Dynamic level generation and randomized encounters

## Current Status

🚧 **Project Status: Heavy Construction** 🚧

The project is in early development with foundational systems being implemented:

- ✅ CMake build system with C++20 support
- ✅ Basic project structure and class definitions
- ✅ Core game loop implementation
- ✅ Item database and inventory system with dedicated UI
- ✅ Renderable entities: interactive map objects, monsters
- 🔄 Player character system (in progress)
- 🔄 Level and dungeon mechanics (in progress)

**Known Technical Debt:** Platform-specific input handling (`conio.h`), inline Level implementations, and other rapid prototyping decisions documented for future architectural improvements.

## Building the Project

### Prerequisites
- CMake 3.16 or higher
- C++20 compatible compiler (MSVC 2019+, GCC 10+, or Clang 12+)
- Git (for version control)

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd the_guild

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --config Debug
```

### Running the Game
```bash
# From the build directory
./Debug/TheGuild.exe    # Windows
./TheGuild              # Linux/macOS
```

## Project Structure

```
the_guild/
├── CMakeLists.txt          # Build configuration
├── README.md               # Project documentation
├── .gitignore              # Version control exclusions
├── include/                # Header files
│   ├── Game.h              # Main game controller
│   ├── Player.h            # Player character system
│   ├── Level.h             # Level base class
│   ├── ItemDatabase.h      # Item management system
│   ├── Entity.h            # Renderables, Monsters, MapObjects
│   └── InventoryUI.h       # The inventory screen and controls
├── src/                    # Implementation files
│   ├── main.cpp            # Application entry point
│   ├── Game.cpp            # Game logic implementation
│   ├── ItemDatabase.cpp    # Item system implementation
│  	├── Entity.cpp          # MapObject interactions implementation
│   ├── InventoryUI.cpp     # Inventory screen implementation
│   └── levels/             # Level implementations (currently inlined in Level.h)
│       └── TavernLevel.cpp # Starting tavern area  (currently inlined in Level.h)
├── assets/                 # Game assets
├── docs/                   # Additional documentation
└── build/                  # Generated build files (gitignored)
```

## Development Philosophy

This project emphasizes:
- **Learning-First Approach**: Each feature implementation focuses on understanding underlying concepts
- **Modern C++ Practices**: Leveraging the latest language features and best practices
- **Collaborative AI Development**: Systematic exploration of AI-assisted programming workflows
- **Professional Standards**: Industry-standard tooling, documentation, and code organization

## Contributing

This is primarily a learning project, but suggestions and educational discussions are welcome! Please feel free to:
- Review code architecture and suggest improvements
- Propose learning exercises or challenges
- Share resources about game development or modern C++
- Test the game, at the moment that means: buy ale and kill rats in the tavern

## License

This project is created for educational purposes. Feel free to use any code for your own learning journey.

---

*"We are the Guild, some call us the Two Hands."*
