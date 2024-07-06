# SDL2 Multiplatform Test

This project was created to exercise the use of SDL2 on Linux and WebAssembly (using Emscripten)

## Build

### Linux

```bash
cd build
cmake ..
make
```

### WebAssembly

```bash
cd embuild
emcmake cmake ..
emmake make
```

## Run

### Linux

```bash
cd bin
./game
```

### WebAssembly

```bash
cd bin
npx http-server -p 8080
```

or

```bash
cd bin
python -m http.server 8080
```

and open http://localhost:8080 in your browser
