---
sidebar_position: 1
---

# R-Type
This project is a 2D game inspired by the R-Type game. The goal is to create a game where the player can move a spaceship and shoot enemies in network. The game will be developed in C++ using SDL2 and Allegro libraries.

## Build
(Create a build directory if it doesn't exist)
```bash
cmake -S . -B build
```

* Build client and server
```bash
cmake --build build
```

* Build specific target
```bash
cmake --build build --target [client/server]
```

## Run
* Server
```bash
./build/server/server
```
* Client
```bash
./build/client/client
```

## Contributing
Contributions are always welcome! If you encounter any bugs, have suggestions for improvements, or would like to contribute additional features, please feel free to submit a pull request.

## License
This proect is licensed under the MIT License, which means you are free to use, modify, and distribute the code as long as you include the original copyright and license notice.