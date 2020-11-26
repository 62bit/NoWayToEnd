#include "common.h"
#include "level_loader.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertexBuffer.h"
#include "window.h"

int main(int argc, char *args[])
{
    windowgl_sdl window = {0};
    window.name = "NoWayToEnd";
    window.width = WINDOW_WIDTH;
    window.height = WINDOW_HEIGHT;

    create_window(window);

    // NOTE(62bit): Shader
    shader mShader = {0};
    create_shader(mShader, "../code/shaders/vertex.vs",
                  "../code/shaders/fragment.vs");
    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH,
                                      (float)WINDOW_HEIGHT, 0.0f,
                                      -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(25.0f, 25.0f, 0.0f));
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 0.0f));
    debug(set_uniform_mat4(mShader, "model", model));
    debug(set_uniform_mat4(mShader, "projection", projection));
    //

    // NOTE(62bit): VertexBuffer
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    vertex_buffer vb;
    vb.vertices = &vertices[0];
    vb.size = sizeof(vertices);
    generate_vertex_buffer(vb);
    set_vertex_attributef(vb, 0, 3, 5 * sizeof(float), (void *)0);
    set_vertex_attributef(vb, 1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    //

    // NOTE(62bit): Texture
    texture tex;
    tex.path = "../assets/wall.png";
    tex.texType = texture::PNG;

    auto texResult = generate_texture(tex);
    if (!texResult)
        debug("Texture can't be loaded!");
    bind_texture(tex);
    //

    {
        int atrribcount;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &atrribcount);
        debug("Max Number of Attributes supported : " << atrribcount);
    }

    // NOTE(62bit): Level
    level lvl = {0};
    lvl.file_path = "../assets/levels/level1.lvl";
    load_level(lvl);
    //

    while (true)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                    return 0;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    return 0;
                else if (e.key.keysym.sym == SDLK_c)
                    set_rendering_mode(WIREFRAME);
            default:
                break;
            }
        }
        fill_screen_with_color(0, 0, 0, 255);

        for (int i = 0; i < 100; ++i)
        {
            if (lvl.cells[i] == 1)
            {
                int row = i / 10;
                int column = i % 10;
                float x = (column * 80.0f) + 80 / 2;
                float y = (row * 80.0f) + 80 / 2;

                model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
                model = glm::scale(model, glm::vec3(80.0f, 80.0f, 0.0f));
                set_uniform_mat4(mShader, "model", model);
                render(mShader, vb);
            }
        }

        swap(window.window);
    }
    return 0;
}