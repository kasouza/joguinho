#ifndef KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_RENDERER_INCLUDE_JOGUINHO_RENDERER_RENDERER_H
#define KASOUZA_JOGUINHO_INCLUDE_JOGUINHO_RENDERER_INCLUDE_JOGUINHO_RENDERER_RENDERER_H

#include "joguinho/input.h"
#include "joguinho/renderer/gl.h"

typedef enum {
    RENDER_SUCCESS,
    RENDER_GLFW_INIT_ERROR,
    RENDER_WINDOW_CREATION_ERROR,
    RENDER_GL_LOAD_ERROR,
    RENDER_PROGRAM_CREATION_ERROR,
    RENDER_FRAMEBUFFER_CREATION_ERROR,
} RenderError;

typedef enum {
    RENDER_UNLOCK_FPS = 0x00000001,
} RenderInitFlags;

RenderError render_init(RenderInitFlags flags);
void render_present();
void render_terminate();
double dt();

#endif
