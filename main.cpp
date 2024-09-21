#include <SDL2/SDL.h>
#include <emscripten.h>
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

void drawTriangle() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Define triangle vertices
    SDL_Point points[3] = {
        {300, 100},
        {200, 300},
        {400, 300}
    };

    // Set triangle color (red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Fill the triangle
    for (int y = points[0].y; y <= points[1].y; ++y) {
        float alpha = (float)(y - points[0].y) / (points[1].y - points[0].y);
        int x1 = points[0].x + alpha * (points[1].x - points[0].x);
        int x2 = points[0].x + alpha * (points[2].x - points[0].x);

        SDL_RenderDrawLine(renderer, x1, y, x2, y);
    }

    // Draw the outline
    SDL_RenderDrawLines(renderer, points, 3);
    SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[0].x, points[0].y);

    SDL_RenderPresent(renderer);
}

void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            emscripten_cancel_main_loop();
            return;
        }
    }
    drawTriangle();
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("SDL Triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    emscripten_set_main_loop(mainLoop, 0, 1);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}