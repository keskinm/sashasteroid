# sashasteroid


### Compile: 

~~g++ -std=c++17 -o flappy flappy_bird.cpp -lsfml-graphics -lsfml-window -lsfml-system ./flappy~~

```bash
mkdir -p build
cmake -S . -B build
cmake --build build

./build/flappy
```

