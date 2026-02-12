#include "toggle.h"
#include <SDL3/SDL.h>

Toggle::Toggle(bool on, double required_time)
    :on{on}, required_time{required_time}, elapsed{required_time}, performace_frquency{SDL_GetPerformanceFrequency()}, prev_counter{SDL_GetPerformanceCounter()}{}

void Toggle::flip() {
    Uint64 now = SDL_GetPerformanceCounter();
    elapsed += (now - prev_counter) / static_cast<double>(performace_frquency);
    prev_counter = now;

    if (elapsed >= required_time) {
        on = !on;
        elapsed = 0;
    }
}
