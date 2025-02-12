#include "Nexus.h"

void testLogger() {
  Nexus::Logger::setLevel(Nexus::LogLevel::Trace);
  Nexus::Logger::trace("Hello, World!");
  Nexus::Logger::debug("Hello, World!");
  Nexus::Logger::info("Hello, World!");
  Nexus::Logger::warn("Hello, World!");
  Nexus::Logger::error("Hello, World!");
  Nexus::Logger::critical("Hello, World!");
}

bool testEventCallback(int x) {
  Nexus::Logger::info("function: Value: {0}", x);
  return false;
}

void testEvent() {
  Nexus::Event<int> event;
  event.on([](int x) -> bool {
    Nexus::Logger::info("lambda: Value: {0}", x);
    return false;
  });
  event.on(testEventCallback);

  event.invoke(42);
}

void test() {
  Nexus::Window::s_api = Nexus::Window::API::GLFW;
  auto window = Nexus::Window::create();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  window->setVSync(true);
  window->onKey([&window](int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      Nexus::Logger::info("Escape key pressed");
      window->shouldClose = true;
      return true;
    }
    return false;
  });

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  window->whileOpen([&]() {
    glClear(GL_COLOR_BUFFER_BIT);

    //* Stolen from ImGui example
    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to create a named window.
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                     // and append into it.

      ImGui::Text("This is some useful text."); // Display some text (you can
                                                // use a format strings too)
      ImGui::Checkbox(
          "Demo Window",
          &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f,
                         1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3(
          "clear color",
          (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                   // widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin(
          "Another Window",
          &show_another_window); // Pass a pointer to our bool variable (the
                                 // window will have a closing button that will
                                 // clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }

    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
  });
}

int main() {
  testLogger();
  testEvent();
  test();
}