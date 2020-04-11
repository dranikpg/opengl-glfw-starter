#include <base.hpp>
#include <functional>

#define hints_func std::function<void()>
#define prepare_func std::function<void(GLFWwindow*)>
#define update_func std::function<void()>
#define render_func std::function<void(int,int)>
#define destroy_func std::function<void()>

struct start_data{
    int width, height;
    std::string name;
    hints_func hints;
    prepare_func prepare;
    update_func update;
    render_func render;
    destroy_func destroy;
};

GLFWwindow* glfw_win = nullptr;

void error_callback(int error, const char* description)
{
    std::cerr << "GLFW ERROR \n" << description << std::endl;
}

void run(start_data data){
    if(!glfwInit()){
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);

    data.hints();

    glfw_win = glfwCreateWindow(data.width, data.height,data.name.c_str(), nullptr, nullptr);
    if(!glfw_win) exit(EXIT_FAILURE);

    glfwMakeContextCurrent(glfw_win);
    glfwSwapInterval(1);

    data.prepare(glfw_win);

    while (!glfwWindowShouldClose(glfw_win)){
        int width, height;
        glfwGetFramebufferSize(glfw_win, &width, &height);
        data.update();
        data.render(width,height);
        glfwSwapBuffers(glfw_win);
        glfwPollEvents();
    }

    data.destroy();
    glfwDestroyWindow(glfw_win);
    glfwTerminate();
}
