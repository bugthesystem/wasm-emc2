#include <stdio.h>
#include <emscripten/emscripten.h>

int main(int argc, char ** argv) {
    printf("WASM emscripten yay!\n");
}

//wrapped in `extern "C"` to prevent C++ name mangling
extern "C" {
    void EMSCRIPTEN_KEEPALIVE func(int argc, char ** argv) {
      printf("bidi function called!\n");
    }
}
