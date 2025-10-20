#ifndef _CORE_HPP_
#define _CORE_HPP_

#include "render/render.hpp"
#include <filesystem>
#include <cstdint>
#include <windows.h>                            
#include <stdio.h> 
#include <profileapi.h> 
#include <intrin.h>  
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <DS>
#include "area/area.hpp"




struct CoreParams {
    uint16_t target_fps{(uint16_t)60};
    std::string name{"Embrozy"};
    int SCREEN_WIDTH{2560}, SCREEN_HEIGHT{1600};
};

class Core {
    Area *area;
    GLFWwindow *window;
    CoreParams params;
    // UI UserInterface;
    LARGE_INTEGER g_qpc_frequency{0};
    
    float delta_time{1.0f};
    bool ContinueFlag{0};
    int error;

    void CWindow() {
        window = Init_Window(params.name, &this->area->PlayerCamera);
        if (window == nullptr){
            perror("Window can't create.\n");
        }
    }

    int initialize_timing() {
        if (g_qpc_frequency.QuadPart == 0) {
            if (!QueryPerformanceFrequency(&g_qpc_frequency)) {
                fprintf(stderr, "Error: QueryPerformanceFrequency not handling.\n");
                return 0;
            }
            if (g_qpc_frequency.QuadPart == 0){
                fprintf(stderr, "Error: QueryPerformanceFrequency gived 0.\n");
                return 0;
            }
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
public:
    Core(CoreParams PARAMS): params(PARAMS) { 
        printf("Core start init\n");
        
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
        
        area = new Area(params.name, 1);
        
        this->CWindow();
        if (window != nullptr){
            if (!Init_Render(PARAMS.SCREEN_WIDTH, PARAMS.SCREEN_HEIGHT)) { 
                perror("Error: Render not initialized.\n");
            }
            else {
                this->area->CreateTerrain(1, 5, glm::dvec3(0.0f));
            }
        }
    }

    int start_loop() {
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
    if (current_time_ns == 0 && g_qpc_frequency.QuadPart != 0) { 
        fprintf(stderr, "Error: Cant get start time value.\n");
        return 0;
    }
    uint64_t next_frame_target_time_ns = current_time_ns + target_frame_ns;
    this->delta_time = (float) 1 / (float)this->params.target_fps * 32;
    printf("Started with FPS=%d, Frame value: %llu ns\n", this->params.target_fps, (unsigned long long)target_frame_ns);
    while (ContinueFlag >= 0 && !glfwWindowShouldClose(window)) {
        if (frame_count % 60 % 60 == 0) {
            printf("camera pos:%.2f, %.2f, %.2f\n", area->PlayerCamera.Position.x, area->PlayerCamera.Position.y, area->PlayerCamera.Position.z);
        }
        // UpdateScreen();
        this->processInput(window);
        
        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->area->render();
        
        _ClearRender();
        glfwSwapBuffers(window);

        glfwPollEvents();

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
    glfwTerminate();
    printf("Main loop culminate: frames: %d\n", frame_count);
    return 1;
}

    void culminate_loop();

    void CursorMovement(bool FLAG) {
        if (FLAG) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        } 
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }
    }

    void processInput(GLFWwindow *window){
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
            printf("Close window\n");
        }
        float cameraSpeed = static_cast<float>(2.5 * delta_time);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            this->CursorMovement(false);
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            this->CursorMovement(true);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            area->PlayerCamera.Position += cameraSpeed * area->PlayerCamera.Front;
            // printf("Ch: W\n");
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            area->PlayerCamera.Position -= cameraSpeed * area->PlayerCamera.Front;
            // printf("Ch: S\n");
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            area->PlayerCamera.Position -= glm::normalize(glm::cross(area->PlayerCamera.Front, area->PlayerCamera.Up)) * cameraSpeed;
            // printf("Ch: A\n");
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            area->PlayerCamera.Position += glm::normalize(glm::cross(area->PlayerCamera.Front, area->PlayerCamera.Up)) * cameraSpeed;
            // printf("Ch: D\n");
        }
        
    }

    ~Core() {}
};

int MainLoop(int target_fps, Area *AREA);

#endif