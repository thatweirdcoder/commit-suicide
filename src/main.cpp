#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"

struct window {
    int width{640};
    int height{480};
    const char *title{"Commit Suicide"};
    GLFWwindow *handle{};
    bool running{true};
} window;

struct joystick {
    bool present{false};
    const char *name{};
    int axes_count{};
    float left_axis_x{};
    float left_axis_y{};
    int buttons_count{};
    unsigned char button_a{};
} joystick;

bool init() {
    // logging
    initLogging();

    // window
    if (!glfwInit()) {
        LOG_ERROR("failed to initialize glfw");
        return false;
    }

    glfwWindowHint(GLFW_RESIZABLE, false);

    window.handle = glfwCreateWindow(window.width, window.height, window.title, nullptr, nullptr);
    const GLFWvidmode *vidmode{glfwGetVideoMode(glfwGetPrimaryMonitor())};
    glfwSetWindowPos(window.handle, (vidmode->width - window.width) / 2, (vidmode->height - window.height) / 2);

    if (!window.handle) {
        LOG_ERROR("error creating glfw window");
        return false;
    }

    glfwMakeContextCurrent(window.handle);

    // opengl
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOG_ERROR("error initializing glad");
        return false;
    }

    LOG_INFO("OpenGL Info:");
    LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    LOG_INFO("  Version: {0}", glGetString(GL_VERSION));

    float positions[6]{
            -0.5f, -0.5f,
            -0.0f, 0.5f,
            0.5f, -0.5f

    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    return true;
}

void update() {
    glClearColor(0.03f, 0.09f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    if (!glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        LOG_INFO("Connect Joystick");
        joystick.present = false;
    } else {
        joystick.name = glfwGetJoystickName(GLFW_JOYSTICK_1);

        const float *axes{glfwGetJoystickAxes(GLFW_JOYSTICK_1, &joystick.axes_count)};
        joystick.left_axis_x = axes[0];
        joystick.left_axis_y = axes[1];

        joystick.button_a = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &joystick.buttons_count)[0];
        joystick.present = true;
    }

    if (joystick.present && joystick.button_a == GLFW_PRESS) {
        LOG_INFO("JUMP");
    }

    glfwPollEvents();
}

void render() {
    glfwSwapBuffers(window.handle);
}

void run() {
    if (!init()) {
        LOG_ERROR("init error");
    }
    while (window.running) {
        update();
        render();

        if (glfwWindowShouldClose(window.handle)) {
            window.running = false;
        }
    }
}

void cleanup() {
    glfwTerminate();
}

int main() {
    run();
    cleanup();

    return 0;
}

