# R-Type
This project is a 2D game inspired by the R-Type game. The goal is to create a game where the player can move a spaceship and shoot enemies in network. The game will be developed in C++ using SDL2, Enet, and Flatbuffers libraries.

## Setup
##### Install required libs using your package manager
* python3-jinja2
* Windows only: https://github.com/ninja-build/ninja/releases

## Build
(Create a build directory if it doesn't exist)
#### Init build targets
* Unix:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
* Windows:
```bash
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
```

#### Build client and server
```bash
cmake --build build
```

#### Build specific target
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
