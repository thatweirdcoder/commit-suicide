#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

#define LOG_TRACE(...) Logger->trace(__VA_ARGS__)
#define LOG_INFO(...) Logger->info(__VA_ARGS__)
#define LOG_WARN(...) Logger->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger->error(__VA_ARGS__)
#define LOG_FATAL(...) Logger->fatal(__VA_ARGS__)
#else
#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#endif

struct windowInfo {
    int width = 640;
    int height = 480;
    const char *title = "Commit Suicide";
} windowInfo;

int main() {
#ifdef DEBUG
    std::shared_ptr<spdlog::logger> Logger;
    spdlog::set_pattern("%^[%T] %n: %v%$");
    Logger = spdlog::stdout_color_mt("Logger");
    Logger->set_level(spdlog::level::trace);
    LOG_INFO("Init Logger");
#endif

    GLFWwindow *window;

    if (!glfwInit()) {
        LOG_ERROR("failed to initialize glfw");
        return -1;
    }

    window = glfwCreateWindow(windowInfo.width, windowInfo.height, windowInfo.title, nullptr, nullptr);
    if (!window) {
        LOG_ERROR("error creating glfw window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOG_ERROR("error initializing glad");
        return -1;
    }

    LOG_INFO("OpenGL Info:");
    LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    LOG_INFO("  Version: {0}", glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.03f, 0.09f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

