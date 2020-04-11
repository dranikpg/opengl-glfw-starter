#pragma once

#include <base.hpp>

#include <fstream>

std::string read_file(const char* file){
    std::ifstream in(file);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return contents;
}

GLenum print_gl_error(GLenum err = -1){
    if(err == -1) err = glGetError();
    if(err == GL_NO_ERROR) return GL_NO_ERROR;
    std::cerr << "OGL Error " << err << ' ';
    switch (err){
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            std::cerr << "UNKNOWN ";
            break;
    }
    std::cerr << std::endl;
    return err;
}

GLenum print_gl_error(const char* section){
    GLenum err = glGetError();
    if(err != GL_NO_ERROR){
        std::cerr << "# " << section << ':';
        return print_gl_error(err);
    }
    return err;
}
