#include "joguinho/renderer/renderer.h"
#include "joguinho/utils.h"

#include <math.h>
#include <stb_image.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SETUP(thing)                                                           \
    RenderError thing##_error = setup_##thing();                               \
    if (thing##_error != RENDER_SUCCESS) {                                     \
        return thing##_error;                                                  \
    }

static double s_dt = 1.0 / 60.0;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vertex;

static bool init = false;
static RenderInitFlags s_flags = 0;

static GLFWwindow *s_window = NULL;
static GLuint s_canvas_program = 0;

static GLuint s_rect_vao = 0;
static GLuint s_rect_vbo = 0;

static int s_window_width = 1024;
static int s_window_height = 600;

static GLuint load_shader(const char *path, GLenum shader_type) {
    char *shader_src = read_file(path);

    GLuint shader = glCreateShader(shader_type);
    if (!shader) {
        LOG("Could not load shader\"%s\"", path);
        return 0;
    }

    // This casting is just to make the warning go away
    glShaderSource(shader, 1, (const char *const *)&shader_src, NULL);
    free(shader_src);

    glCompileShader(shader);

    int res = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (!res) {
        const GLsizei INFO_LOG_MAX_LENGTH = 256;
        GLchar info_log[INFO_LOG_MAX_LENGTH];
        GLsizei info_log_length = 0;

        glGetShaderInfoLog(shader, INFO_LOG_MAX_LENGTH, &info_log_length,
                           info_log);

        LOG("Could not compile shader %s\n", info_log);

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

static GLuint create_program(const char *vertex_shader_path,
                             const char *fragment_shader_path) {
    GLuint vertex_shader = load_shader(vertex_shader_path, GL_VERTEX_SHADER);
    GLuint fragment_shader =
        load_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
    if (!vertex_shader || !fragment_shader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    int res = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &res);
    if (!res) {
        const GLsizei INFO_LOG_MAX_LENGTH = 256;
        GLchar info_log[INFO_LOG_MAX_LENGTH];
        GLsizei info_log_length = 0;

        glGetProgramInfoLog(program, INFO_LOG_MAX_LENGTH, &info_log_length,
                            info_log);

        LOG("%s", info_log);

        glDeleteProgram(program);
        return 0;
    }

    return program;
}

static int setup_glfw() {
    // GLFW Initialization
    if (!glfwInit()) {
        return RENDER_GLFW_INIT_ERROR;
    }

    // Window Creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    s_window = glfwCreateWindow(s_window_width, s_window_height, "Sandbox",
                                NULL, NULL);
    if (!s_window) {
        return RENDER_WINDOW_CREATION_ERROR;
    }

    glfwMakeContextCurrent(s_window);

    return RENDER_SUCCESS;
}

static int setup_gl() {
    // OpenGL setup
    if (!gladLoadGL(glfwGetProcAddress)) {
        return RENDER_GL_LOAD_ERROR;
    }

    glEnable(GL_PROGRAM_POINT_SIZE);
    glViewport(0, 0, s_window_width, s_window_height);

    return RENDER_SUCCESS;
}

static RenderError setup_buffers() {
    // Rectangle
    Vertex rect_vertices[] = {
        {-1.0, -1.0, 0.0}, {1.0, -1.0, 0.0}, {1.0, 1.0, 0.0},
        {-1.0, -1.0, 0.0}, {1.0, 1.0, 0.0},  {-1.0, 1.0, 0.0},
    };

    glGenVertexArrays(1, &s_rect_vao);
    glGenBuffers(1, &s_rect_vbo);

    glBindVertexArray(s_rect_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_rect_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    return RENDER_SUCCESS;
}

static RenderError setup_programs() {
    s_canvas_program =
        create_program("shaders/passthrough.vert", "shaders/passthrough.frag");
    if (!s_canvas_program) {
        return RENDER_PROGRAM_CREATION_ERROR;
    }

    return RENDER_SUCCESS;
}

RenderError render_init(RenderInitFlags flags) {
    SETUP(glfw);
    SETUP(gl);
    SETUP(programs);
    SETUP(buffers);

    init = true;
    s_flags = flags;

    return RENDER_SUCCESS;
}

#define SET_UNIFORM(uniform_func, program, name, ...)                          \
    uniform_func(glGetUniformLocation(program, name), __VA_ARGS__)

void render_present() {
    static double start = -1;
    if (start == -1) {
        start = glfwGetTime();
    } else {
        double now = glfwGetTime();
        s_dt = now - start;
        start = now;
    }

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(s_rect_vao);
    glUseProgram(s_canvas_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwPollEvents();

    if (s_flags & RENDER_UNLOCK_FPS) {
        glfwSwapInterval(0);
    }

    glfwSwapBuffers(s_window);
}

void render_terminate() {
    if (!init) {
        return;
    }

    // Programs
    glDeleteProgram(s_canvas_program);
    s_canvas_program = 0;

    // VAOs and VBOs
    glDeleteVertexArrays(1, &s_rect_vao);
    glDeleteBuffers(1, &s_rect_vbo);

    glfwDestroyWindow(s_window);
    glfwTerminate();
}

double dt() { return s_dt; }
