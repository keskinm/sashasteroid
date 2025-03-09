# sashasteroid

### A working vscode c_cpp_properties.json:

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/SFML/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c17",
            "cppStandard": "c++14",
            "intelliSenseMode": "linux-clang-x64"
        }
    ],
    "version": 4
}
```

### Launch: 

```
g++ -std=c++17 -o flappy flappy_bird.cpp -lsfml-graphics -lsfml-window -lsfml-system ./flappy
```