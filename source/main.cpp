#include <base.hpp>

#include <util.hpp>
#include <window.hpp>

#include <shader.hpp>
#include <vbo.hpp>
#include <vao.hpp>

#include <functional>


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

vbo_t<float> verts;
shader_t shader;
vao_t vao;

void prepare(GLFWwindow* win){
    vao = vao_t(true);
    glBindVertexArray(vao.addr());

    print_gl_error("vao");

    std::vector<float> vs = {-0.8,-0.8, 0.8,-0.8, 0.8,0.8,-0.8,0.8};
    verts = vbo_t<float>(vs, false);

    print_gl_error("vbo");
       
    glBindBuffer(GL_ARRAY_BUFFER, verts.addr());
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    print_gl_error("attrib ptr");
    
    std::string vert_src = read_file("../shaders/triangle.vs");
    std::string frag_src = read_file("../shaders/triangle.fs");
    shader = shader_t(vert_src,frag_src,"outColor");

    print_gl_error("shader");
}

void render(int w, int h){
    glClearColor(1,0.5,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    float v0[2] = {-glfwGetTime()/30.0, -glfwGetTime()/30.0};
    verts.update(v0, 2, 0);

    shader.use();
    vao.bind();

    glLineWidth(10);

    glDrawArrays(GL_LINE_LOOP, 0, 4);

    print_gl_error("render");
}

signed main(){
    start_data data = {
        640, 480, "OpenGL",
        [](){
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        },
        prepare,
        [](){},
        render,
        [](){}
    };
    run(data);
}