#pragma once

#include <base.hpp>

struct shader_t{
public:
    shader_t(){}
    shader_t(const char* vertex_src, const char* fragment_src){
        build(vertex_src, fragment_src);
    }
    shader_t(const char* vertex_src, const char* fragment_src, const char* outname){
        build(vertex_src, fragment_src);
        init_fragment_output(outname);
    }
    shader_t(const std::string& vertex_src, const std::string& fragment_src){
        build(vertex_src.c_str(), fragment_src.c_str());
    }
    shader_t(const std::string& vertex_src, const std::string& fragment_src, const char* outname){
        build(vertex_src.c_str(), fragment_src.c_str());
        init_fragment_output(outname);
    }
    ~shader_t(){
        if(m_addr != 0) {
            std::cout << "deleting" << m_addr << std::endl;
            glDeleteProgram(m_addr);
        }
    }

    shader_t& operator=(const shader_t& rhs) = delete;
    shader_t& operator=(shader_t&& rhs){ // steal data
        if(this->m_addr != 0) glDeleteProgram(m_addr);
        this->m_addr = rhs.m_addr;
        rhs.m_addr = 0; 
    }


    void use(){
        glUseProgram(m_addr);
    }
    GLuint addr(){
        return m_addr;
    }
    GLuint uniform(const char* name){
        return glGetUniformLocation(m_addr, name);
    }
    GLuint attribute(const char* name){
        return glGetAttribLocation(m_addr, name);
    }
    void init_fragment_output(const char* outname){
        glBindFragDataLocation(m_addr, 0, outname);
    }
private:   
    GLuint m_addr;
    GLuint compile(GLuint type, const char* source){
        GLuint addr = glCreateShader(type);
        glShaderSource(addr, 1, &source, nullptr);
        glCompileShader(addr);

        GLint success = GL_FALSE;
        glGetShaderiv(addr, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE){
            char buf[512];
            glGetProgramInfoLog(addr, 512, nullptr, buf);
            std::cerr << "SHADER COMPILATION ERROR" << std::endl;
            std::cerr << buf << std::endl;
        }
        
        return addr;
    }
    GLuint build(const char* vertex_src, const char* fragment_src){
        GLuint vertex = compile(GL_VERTEX_SHADER, vertex_src);
        GLuint fragment = compile(GL_FRAGMENT_SHADER, fragment_src);

        m_addr = glCreateProgram();
        glAttachShader(m_addr, vertex);
        glAttachShader(m_addr, fragment);
        glLinkProgram(m_addr);

        GLint success = GL_FALSE;
        glGetProgramiv(m_addr, GL_LINK_STATUS, &success);
        if(success == GL_FALSE){
            char buf[512];
            glGetProgramInfoLog(m_addr, 512, nullptr, buf);
            std::cerr << "SHADER LINK ERROR" << std::endl;
            std::cerr << buf << std::endl;
        }

        glDetachShader(m_addr,vertex);
        glDetachShader(m_addr,fragment);
        glDeleteShader(vertex);
        glDeleteShader(fragment); 
    }
};