#include <iostream>
#include <string>
#include <unordered_set>
#include <SDL.h>

template <typename T>
void print_set(std::unordered_set<T> const &s)
{
    std::cout << "set{ ";
    for (const auto &elem : s)
    {
        std::cout << elem << " ";
    }
    std::cout << "}\n";
}

int main(int argc, char **argv)
{
    // std::string s = "Hello world 2!";

    // std::cout << "Hello World" << std::endl;
    // std::cout << s << std::endl;

    // if (__cplusplus == 201703L)
    //     std::cout << "C++17\n";
    // else if (__cplusplus == 201402L)
    //     std::cout << "C++14\n";
    // else if (__cplusplus == 201103L)
    //     std::cout << "C++11\n";
    // else if (__cplusplus == 199711L)
    //     std::cout << "C++98\n";
    // else
    //     std::cout << "pre-standard C++\n";

    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    SDL_Event event;

    std::unordered_set<SDL_Keycode> keys_pressed;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                else
                {
                    bool inserted = keys_pressed.insert(event.key.keysym.sym).second;
                    if (inserted) print_set(keys_pressed);
                }
                break;

            case SDL_KEYUP:
                keys_pressed.erase(event.key.keysym.sym);
                print_set(keys_pressed);
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 120, 140, 70, 255);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
