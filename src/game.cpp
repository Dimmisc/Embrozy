#include "game.hpp"

#include <filesystem>
#include <cstdint>
#include <windows.h>                            
#include <stdio.h> 
#include <profileapi.h> 
#include <intrin.h>  

Game::Game(GP params = GP()) : params(params) {
    namespace fs = std::filesystem;

    if (!fs::exists("assets")) {
        perror("Can't find assets dirictory.\n");
    }
    fs::current_path(fs::current_path()/"assets");
    if (!fs::exists("textures") || !fs::exists("shaders") || !fs::exists("saves") || !fs::exists("fonts") || !fs::exists("audio")) {
        perror("Can't find subdirictory in assets.\n");
    }
    else if (!fs::exists("saves")) {
        try {
            fs::create_directory("saves");  
        }
        catch (const fs::filesystem_error& e) {
            fprintf(stderr, "Error: Can't create 'saves' directory. %s\n", e.what());
        }
    }
    fs::current_path("..");

    this->window = new Window();
    this->engine = new Engine();
    this->ui = new UI();
    this->settings_controller = new SettingsController();
}  

int Game::initialize_timing() {
    if (this->g_qpc_frequency.QuadPart == 0) {
        if (!QueryPerformanceFrequency(&this->g_qpc_frequency)) {
            fprintf(stderr, "Error: QueryPerformanceFrequency not handling.\n");
            return 0;
        }
        if (this->g_qpc_frequency.QuadPart == 0){
            fprintf(stderr, "Error: QueryPerformanceFrequency gived 0.\n");
            return 0;
        }
    }
    return 1;
}

uint64_t Game::get_monotonic_time_ns() {
    if (this->g_qpc_frequency.QuadPart == 0) {
        if (!initialize_timing()) return 0;
    }
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    uint64_t whole_seconds = counter.QuadPart / this->g_qpc_frequency.QuadPart;
    uint64_t remainder_ticks = counter.QuadPart % this->g_qpc_frequency.QuadPart;
    uint64_t fractional_ns = (remainder_ticks * 1000000000ULL) / this->g_qpc_frequency.QuadPart;
    return (whole_seconds * 1000000000ULL) + fractional_ns;
}

void Game::precise_sleep_ns(uint64_t nanoseconds) {
    if (nanoseconds == 0) return;
    uint64_t start_time = get_monotonic_time_ns();
    if (start_time == 0) return;
    uint64_t target_end_time = start_time + nanoseconds;
    const uint64_t min_sleep_threshold_ns = 2000000ULL; // 2 мс
    const uint64_t spin_wait_allowance_ns = 1500000ULL; // 1.5 мс
    
    if (nanoseconds > min_sleep_threshold_ns) {
        uint64_t sleep_duration_ns = nanoseconds - spin_wait_allowance_ns;
        DWORD sleep_ms = (DWORD)(sleep_duration_ns / 1000000ULL);
        if (sleep_ms > 0) {
            Sleep(sleep_ms);
        }
    }
    while (get_monotonic_time_ns() < target_end_time) {
        YieldProcessor();
    }
}

int Game::Start(int nfps = 0) {
    if (nfps != 0) {
        this->params.target_fps = nfps;
    }
    if (this->params.target_fps <= 0) {
        fprintf(stderr, "Error: target_fps must be above 0.\n");
        return 0;
    }
    if (!initialize_timing()) {
        return 0;
    }
    const uint64_t target_frame_ns = 1000000000ULL / (uint64_t)this->params.target_fps;
    uint64_t frame_count = 0;
    uint64_t current_time_ns = get_monotonic_time_ns();
    if (current_time_ns == 0 && this->g_qpc_frequency.QuadPart != 0) { 
        fprintf(stderr, "Error: Cant get start time value.\n");
        return 0;
    }
    uint64_t next_frame_target_time_ns = current_time_ns + target_frame_ns;
    this->params.delta_time = (float) 1 / (float)this->params.target_fps * 32;
    printf("Started with FPS=%d, Frame value: %llu ns\n", this->params.target_fps, (unsigned long long)target_frame_ns);
    while (this->CONTINUE_FLAG >= 0 && !this->window->WindowShouldClose()) {
        // later will be added

        frame_count++;
        current_time_ns = get_monotonic_time_ns();
        if (current_time_ns < next_frame_target_time_ns) {
            uint64_t sleep_time_ns = next_frame_target_time_ns - current_time_ns;
            precise_sleep_ns(sleep_time_ns);
        }
        next_frame_target_time_ns += target_frame_ns;
        current_time_ns = get_monotonic_time_ns();
        if (next_frame_target_time_ns < current_time_ns) {
            next_frame_target_time_ns = current_time_ns + target_frame_ns;
        }
    }
    
    printf("Main loop culminate: frames: %d\n", frame_count);
    return 1;
}