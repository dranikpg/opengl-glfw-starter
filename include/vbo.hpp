#pragma once

#include <base.hpp>
#include <vector>

template<typename V>
struct vbo_t{
public: 
    vbo_t(){
        m_addr = 0;
    }
    vbo_t(size_t capacity): m_capacity(capacity){
        glGenBuffers(1, &m_addr);
        glBindBuffer(GL_ARRAY_BUFFER, m_addr);
        glBufferData(GL_ARRAY_BUFFER, m_capacity*sizeof(V), nullptr, GL_DYNAMIC_DRAW);
    }
    vbo_t(const V* data, size_t size, bool static_draw = true): m_capacity(size){
        glGenBuffers(1, &m_addr);
        glBindBuffer(GL_ARRAY_BUFFER, m_addr);
        glBufferData(GL_ARRAY_BUFFER, size*sizeof(V), data, static_draw ? GL_STATIC_DRAW: GL_DYNAMIC_DRAW);

    }
    vbo_t(const std::vector<V>& data, bool static_draw = true) : vbo_t(&data[0], data.size(), static_draw){
    }
    ~vbo_t(){
        if(m_addr != 0) glDeleteBuffers(1, &m_addr);
    }

    vbo_t& operator=(const vbo_t& rhs) = delete;
    vbo_t& operator=(vbo_t&& rhs){
        if(this->m_addr != 0) glDeleteBuffers(1, &m_addr);
        this->m_addr = rhs.m_addr;
        this->m_capacity = rhs.m_capacity;
        rhs.m_addr = 0;
    }

    GLuint addr(){
        return m_addr;
    }
    void bind(){
        glBindBuffer(GL_ARRAY_BUFFER, m_addr);
    }

    void update(const std::vector<V>& data){
        update(&data[0], data.size(), 0);
    }
    void update(const V* data, int size, int offset){
        assert(size <= m_capacity);
        glBindBuffer(GL_ARRAY_BUFFER, m_addr);
        glBufferSubData(GL_ARRAY_BUFFER, offset*sizeof(V), size*sizeof(V), data);
    }
private:
    GLuint m_addr;
    size_t m_capacity;
};