// #include <MemoryTraker.h>
#ifdef _WIN32
// Extern to use discret GPU
extern "C" {
    // NVIDIA
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
    // AMD
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

#include <iostream>

// #include "src/core/core.hpp"

int main() {
    printf("Start Create params\n");
    CoreParams CParam;
    printf("Create params\n");
    Core core(CParam);
    core.start_loop();
    return 0;
}
