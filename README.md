# SDL2 Multiplatform Test

This project was created to exercise the use of SDL2 on Linux, WebAssembly
(using Emscripten) and Windows

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

### Windows

Make sure you have `vcpkg` installed. And `SDL2` and `SDL2_ttf` too

```PowerShell
vcpkg install SDL2:x64-windows SDL2-ttf:x64-windows
```

```PowerShell
cd winbuild
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
.\sdl2-multiplatform-test.sln
```
and build from Visual Studio

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

### Windows

```PowerShell
cd bin
.\game.exe
```
