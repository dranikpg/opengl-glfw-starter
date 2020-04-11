#pragma once

#include <base.hpp>

struct vao_t{
public:
    vao_t(bool create = false){
        if(create) glGenVertexArrays(1, &m_addr);
    }
    ~vao_t(){
        if(m_addr != 0) glDeleteVertexArrays(1, &m_addr);
    }

    vao_t& operator=(const vao_t& rhs) = delete;
    vao_t& operator=(vao_t&& rhs){ // steal data
        if(this->m_addr != 0) glDeleteVertexArrays(1, &m_addr);
        this->m_addr = rhs.m_addr;
        rhs.m_addr = 0; 
    }


    GLuint addr(){
        return m_addr;
    }
    void bind(){
        glBindVertexArray(m_addr);
    }
private:
    GLuint m_addr;
};