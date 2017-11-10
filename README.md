# web-emc2
C++ Webassembly experiments using Emscripten on OSX

## Pre
```
brew install cmake
```
## emcc
```
git clone https://github.com/juj/emsdk.git
cd emsdk

./emsdk install --build=Release sdk-incoming-64bit binaryen-master-64bit
./emsdk activate --global --build=Release sdk-incoming-64bit binaryen-master-64bit

source ./emsdk_env.sh
```

## Compile
```sh
emcc -o out/hello.html hello.c -O3 -s WASM=1 \ 
     --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1
```

## Preview

```sh
# install simple http server
npm install -g lite-server
```

```sh
lite-server out/
```

|> z i λ a s a l
