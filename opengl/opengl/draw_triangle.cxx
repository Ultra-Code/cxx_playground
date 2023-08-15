#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <iostream>
#include <array>

using std::array;
using std::cerr;
using std::cout;

auto constexpr compile_shader_err_handling = [](GLuint shader_obj) {
  auto success = int();
  auto constexpr char_size = 512;
  auto error_info = array<char, char_size>{};
  // use to check if compiling shader was a success
  glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE)
    {
      glGetShaderInfoLog(shader_obj, char_size, nullptr, error_info.data());
      cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
           << error_info.data() << '\n';
    }
};

auto constexpr link_shader_err_handling = [](GLuint shader_program) {
  auto success = int();
  auto constexpr char_size = 512;
  auto error_info = array<char, char_size>{};
  // use to check if compiling shader was a success
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE)
    {
      glGetProgramInfoLog(shader_program, char_size, nullptr,
                          error_info.data());
      cerr << "ERROR::SHADES::PROGRAM::LINKING_FAILED\n"
           << error_info.data() << '\n';
    }
};
auto constexpr create_vertex_shader = [] [[nodiscard]]
{
  // so basically our vertex_shader is transforming out 3d vertex data into
  // another 3d data with an additional information the pespective division
  auto constexpr vertex_shader = R"(
    //declace version where the 460 coresponds with opengl 4.60
    //then the profile which in our case is the core profile
    #version 460 core
    //We also specifically set the location of the input variable
    //via layout (location = 0)
    //We declace all input vertex attributes with the in keyword
    //since our vertex data is a 3 dimensional array when need
    //one input vertex attributes of type vec3 with the name aPos
    layout (location = 0) in vec3 aPos;
    void main()
    {
    //note that all glsl data are vec4 but the last argument doesn't
    //specify a posision in space but rather pespective division
    //gl_Position is a predifined variable that specify the output of our
    //vertex shader
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";
  auto vertex_shader_obj = glCreateShader(GL_VERTEX_SHADER);
  auto constexpr number_of_vertex_shaders = 1;
  glShaderSource(vertex_shader_obj, number_of_vertex_shaders, &vertex_shader,
                 nullptr);
  glCompileShader(vertex_shader_obj);
  compile_shader_err_handling(vertex_shader_obj);
  return vertex_shader_obj;
};

auto constexpr create_fragment_shader = [] [[nodiscard]]
{
  // fragment shader is for calculating the color output of our pixels
  auto constexpr fragment_shader = R"(
    #version 460 core
    //declare an output variable with out
    out vec4 FragColor;
    void main()
    {
    //assigning a vec4 of color values which is some what orange
    //meaning the color of our pixels should be some what orange
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    )";
  auto fragment_shader_obj = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_obj, 1, &fragment_shader, nullptr);
  glCompileShader(fragment_shader_obj);
  compile_shader_err_handling(fragment_shader_obj);
  return fragment_shader_obj;
};

auto constexpr shader_program
    = [](GLuint vertex_shader_obj, GLuint fragment_shader_obj) {
        auto shader_program_obj = glCreateProgram();
        glAttachShader(shader_program_obj, vertex_shader_obj);
        glAttachShader(shader_program_obj, fragment_shader_obj);
        glLinkProgram(shader_program_obj);
        link_shader_err_handling(shader_program_obj);
        glUseProgram(shader_program_obj);
        glDeleteShader(vertex_shader_obj);
        glDeleteShader(fragment_shader_obj);
      };

auto constexpr store_vbo_on_gpu = [](auto const &vertex_data,
                                     auto const &indices) {
  auto vao_obj = GLuint();
  glGenVertexArrays(1, &vao_obj);
  glBindVertexArray(vao_obj);
  // memory address of the generated vbo
  auto vbo_obj = GLuint();
  glGenBuffers(1, &vbo_obj);
  // bind vbo_obj to GL_ARRAY_BUFFER so that all calls with the target
  // type GL_ARRAY_BUFFER configure and modify vbo_obj
  glBindBuffer(GL_ARRAY_BUFFER, vbo_obj);
  // copy vertex_data into buffer of type GL_ARRAY_BUFFER which is the
  // vbo_obj buffer the last argument to glBufferData tells opengl how we
  // want the graphics card to manage the buffer data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data.data(),
               GL_STATIC_DRAW);
  auto ebo_obj = GLuint();
  glGenBuffers(1, &ebo_obj);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_obj);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
               GL_STATIC_DRAW);
  // layout(location = 0).in our vertex shader for our aPos attribute
  auto constexpr vertex_attribute_location = GLuint(0);
  // our in attribute data had 3 values x,y,z and type  vec3
  auto constexpr vertex_attribute_size = 3;
  auto constexpr vertex_data_type = GL_FLOAT;
  auto constexpr normalize_vertex_data = GL_FALSE; // data is already in NDC
  // specify the size of the consecutive column of a vertex attributes it is
  // also called stride.NOTE we could specify 0 for opengl to detect the
  // stide but this only works if our buffer data is tightly packed
  auto constexpr space_between_consecutive_vertex
      = vertex_attribute_size * sizeof(float);
  // the offset of where the position data begins in the buffer
  auto constexpr position_data_start_offset = static_cast<void *>(nullptr);
  glVertexAttribPointer(vertex_attribute_location, vertex_attribute_size,
                        vertex_data_type, normalize_vertex_data,
                        space_between_consecutive_vertex,
                        position_data_start_offset);
  glEnableVertexAttribArray(vertex_attribute_location);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_attribute_location);
  glBindVertexArray(vertex_attribute_location);
  return vao_obj;
};

auto constexpr setup_shaders = [] {
  auto vertex_shader = create_vertex_shader();
  auto fragment_shader = create_fragment_shader();
  shader_program(vertex_shader, fragment_shader);
};

auto
draw_triangle() -> void
{
  auto constexpr rectangle
      = std::array<std::array<float, 3>, 4>{ { { 0.5F, 0.5F, 0.0F },
                                               { 0.5F, -0.5F, 0.0F },
                                               { -0.5F, -0.5F, 0.0F },
                                               { -0.5F, 0.5F, 0.0F } } };
  auto constexpr indices
      = std::array<std::array<uint8_t, 3>, 2>{ { { 0, 1, 3 }, { 1, 2, 3 } } };

  auto vao_obj = store_vbo_on_gpu(rectangle, indices);
  setup_shaders();
  glBindVertexArray(vao_obj);
  auto constexpr vertex_array_start_index = 0;
  auto constexpr number_of_vertices_to_draw = 3;
  glDrawArrays(GL_TRIANGLES, vertex_array_start_index,
               number_of_vertices_to_draw);
  auto constexpr primative_type = GL_TRIANGLES;
  auto constexpr number_of_rectangle_vertice = 6;
  auto constexpr type_of_indices = GL_UNSIGNED_INT;
  auto *indices_offset = static_cast<void *>(nullptr);
  /* glDrawElements(primative_type, number_of_rectangle_vertice, type_of_indices,
                 indices_offset); */
}
