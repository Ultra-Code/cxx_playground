#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <utility>

using std::printf;
using std::fprintf;

auto
draw_triangle() -> void;

constexpr auto set_opengl_version = [] {
  if (glfwInit() == GLFW_FALSE)
    {
      // Initialization failed
      printf("Initialization of glfw failed"); // NOLINT
      std::exit(EXIT_FAILURE);
    }
  constexpr int8_t major = 4;
  constexpr int8_t minor = 6;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  /// Means not to use backward compatibility features
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
};

constexpr auto close_window = +[](GLFWwindow *window, int key,
                                  int /*scancode*/, int action, int /*mods*/) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
};

constexpr auto resize_widow
    = +[](GLFWwindow * /*window*/, int width, int height) {
        glViewport(0, 0, width, height);
      };

constexpr auto set_callbacks = +[](GLFWwindow *window) {
  glfwSetErrorCallback(+[](int error, const char *description) {
    fprintf(stderr, "Error code %d , %s\n", error, description); // NOLINT
  });

  printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
         glGetString(GL_SHADING_LANGUAGE_VERSION));

  glfwSetKeyCallback(window, close_window);
  glfwSetFramebufferSizeCallback(window, resize_widow);
};

constexpr auto initialize_window = [] [[nodiscard]]
{
  set_opengl_version();
  constexpr auto width = int32_t(680);
  constexpr auto height = int32_t(640);
  GLFWwindow *window = glfwCreateWindow(
      width, height, "First Step Into OpenGL", nullptr, nullptr);
  if (window == nullptr)
    {
      // Window or OpenGL context creation failed
      printf("Failed to create a GLFW window \n");
      glfwTerminate();
      std::exit(EXIT_FAILURE);
    }
  glfwMakeContextCurrent(window);
  set_callbacks(window);
  return window;
};

auto
main(int /*argc*/, char * /*argv*/[]) -> int
{
  // Assume context creation using GLFW
  auto *window = initialize_window();
  while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
      // Keep running
      const auto render_opengl = [&window] {
        auto width = int();
        auto height = int();
        glfwGetFramebufferSize(window, &width, &height);
        // glViewport(0, 0, width, height);
        return std::pair{ width, height };
      };

      [[maybe_unused]] const auto &&[buf_width, buf_height] = render_opengl();
      glClearColor(0.2, 0.3, 0.3, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      draw_triangle();
      glfwPollEvents();
      glfwSwapBuffers(window);
    }

  glfwTerminate();
}
