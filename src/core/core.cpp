#include "core.hpp"


//#include "area/area.hpp"
#include <cstdint>

#ifdef WIN32
#include <windows.h>                            
#include <stdio.h> 
#include <profileapi.h> 
#include <intrin.h>  


#include "area/area.hpp"
#include "render/render.hpp"

static LARGE_INTEGER g_qpc_frequency{0};
int ContinueFlag = 0;


int initialize_timing() {
    if (g_qpc_frequency.QuadPart == 0) {
        if (!QueryPerformanceFrequency(&g_qpc_frequency)) {
            fprintf(stderr, "Error: QueryPerformanceFrequency not handling.\n");
            return 0;
        }
        fprintf(stderr, "Error: QueryPerformanceFrequency gived 0.\n");
        return 0;
    }
    return 1;
}

uint64_t get_monotonic_time_ns() {

    if (g_qpc_frequency.QuadPart == 0) {
        if (!initialize_timing()) return 0;
    }
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    uint64_t whole_seconds = counter.QuadPart / g_qpc_frequency.QuadPart;
    uint64_t remainder_ticks = counter.QuadPart % g_qpc_frequency.QuadPart;
    uint64_t fractional_ns = (remainder_ticks * 1000000000ULL) / g_qpc_frequency.QuadPart;
    return (whole_seconds * 1000000000ULL) + fractional_ns;
}

void precise_sleep_ns(uint64_t nanoseconds) {
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
#endif

int Init_core(){

}

int MainLoop(int target_fps, Area *AREA) {

#ifdef WIN32

    if (target_fps <= 0) {
        fprintf(stderr, "Error: target_fps must be above 0.\n");
        return 0;
    }
    if (!initialize_timing()) {
        return 0;
    }
    const uint64_t target_frame_ns = 1000000000ULL / (uint64_t)target_fps;
    uint64_t frame_count = 0;
    uint64_t current_time_ns = get_monotonic_time_ns();
    if (current_time_ns == 0 && g_qpc_frequency.QuadPart != 0) { 
        fprintf(stderr, "Error: Cant get start time value.\n");
        return 0;
    }
    if (!Init_Render()){
        printf("Render can't initialize!\n");
        return 0;
    }

    uint64_t next_frame_target_time_ns = current_time_ns + target_frame_ns;
    printf("Started with FPS=%d, Frame value: %llu ns\n", target_fps, (unsigned long long)target_frame_ns);
    while (ContinueFlag >= 0) {
#else

#endif
        
        _PrepareRender();
        UpdateScreen();
        _ClearRender();

#ifdef WIN32
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
#endif

    printf("Main loop culminate\n");
    return 1;
}
