# opengl-glfw-starter
My OpenGL GLFW CMake starter pack

Contains simple helper classes for VAO, VBO, GLSL shaders and basic GLFW+mainloop window setup


```c++
#include <base.hpp>
#include <util.hpp>
#include <window.hpp>
#include <shader.hpp>
#include <vbo.hpp>
#include <vao.hpp>
#include <functional>

vbo_t<float> verts;
shader_t shader;
vao_t vao;

void prepare(GLFWwindow* win){
    vao = vao_t(true); //create VAO, assign wih move semantics
    glBindVertexArray(vao.addr()); //get GLuint
    print_gl_error("vao"); //check for GL errors and print erorr info with tag

    std::vector<float> vs = {-0.8,-0.8, 0.8,-0.8, 0.8,0.8,-0.8,0.8};
    verts = vbo_t<float>(vs, false); //create VBO from vectors/arrays and set STATIC_DRAW to false
       
    glBindBuffer(GL_ARRAY_BUFFER, verts.addr());
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    
    std::string vert_src = read_file("../shaders/triangle.vs"); // simple util
    std::string frag_src = read_file("../shaders/triangle.fs");
    shader = shader_t(vert_src,frag_src,"outColor"); // load and compile shader
}

void render(int w, int h){
    glClearColor(1,0.5,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    float v0[2] = {-glfwGetTime()/30.0, -glfwGetTime()/30.0};
    verts.update(v0, 2, 0); // glBufferData wrapper
  
    shader.use(); // glUseProgram(shader.addr())
    vao.bind(); // glBindVertexArray(vao.addr())

    glLineWidth(10);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

signed main(){
    start_data data = {
        640, 480, "OpenGL",
        [](){ //pre initialize glfw
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        },
        prepare,
        [](){}, //update
        render,
        [](){} //destroy
    };
    run(data); // open window and start loop with simple config struct
}
```
