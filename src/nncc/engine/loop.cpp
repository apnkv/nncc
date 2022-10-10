#include "loop.h"

#include <imnodes/imnodes.h>

#include <imgui_internal.h>

#include <nncc/context/context.h>
#include <nncc/engine/camera.h>
#include <nncc/gui/gui.h>

namespace nncc::engine {

int LoopThreadFunc(bx::Thread* self, void* args) {
    auto& delegate = *static_cast<ApplicationLoop*>(args);
    auto& context = *context::Context::Get();
    auto& window = context.GetWindow(0);

    if (context.rendering.Init(window.framebuffer_width, window.framebuffer_height) != 0) {
        return 1;
    }
    float font_size = 18;

    if (context.imgui_context == nullptr) {
        imguiCreate(font_size, NULL, window.scale);
        context.imgui_context = ImGui::GetCurrentContext();
        ImGui::GetAllocatorFunctions(&context.imgui_allocators.p_alloc_func, &context.imgui_allocators.p_free_func, &context.imgui_allocators.user_data);
    }

    ImGui::GetStyle().ScaleAllSizes(window.scale);

    ImNodes::CreateContext();

    int result = delegate();

    ImNodes::DestroyContext();
    imguiDestroy();
    context.rendering.Destroy();

    auto exit_event = context::GlfwEvent(context::GlfwEventType::Destroy, context.GetGlfwWindow(0));
    context.dispatcher.enqueue(exit_event);

    bgfx::destroy(rendering::Material::default_texture);
    bgfx::shutdown();
    delegate.reset();

    return result;
}

void ProcessWindowingEvents(const context::GlfwEvent& event) {
    static bool fullscreen = false;

    if (event.type == nncc::context::GlfwEventType::Destroy) {
        glfwSetWindowShouldClose(event.window, true);
    } else if (event.type == nncc::context::GlfwEventType::ToggleFullscreen) {

#if NNCC_PLATFORM_OSX
        ToggleFullscreenCocoa(glfwGetCocoaWindow(event.window));
        fullscreen = !fullscreen;
#else
        context.log_message = "This button only works on macOS yet.";
#endif
    }
}

int Run(ApplicationLoop* loop) {
    auto& context = *nncc::context::Context::Get();
    if (!context.InitInMainThread()) {
        return 1;
    }

    auto& window = context.GetWindow(0);
    auto glfw_main_window = context.GetGlfwWindow(0);

    context.dispatcher.sink<context::GlfwEvent>().connect<&ProcessWindowingEvents>();
    context.dispatcher.sink<input::ExitEvent>().connect<&context::Context::HandleExitEvent>(context);

    auto thread = context.GetDefaultThread();
    thread->init(&LoopThreadFunc, static_cast<void*>(loop), 0, "main_loop");

    while (!glfwWindowShouldClose(glfw_main_window)) {
        glfwWaitEventsTimeout(1. / 60);

        // TODO: support multiple windows
        int width, height;
        glfwGetWindowSize(glfw_main_window, &width, &height);
        if (width != window.width || height != window.height) {
            input::ResizeEvent event;
            event.window_idx = 0;
            event.width = width;
            event.height = height;

            context.dispatcher.enqueue(event);
        }

        bgfx::renderFrame();
    }

    context.Exit();
    while (bgfx::renderFrame() != bgfx::RenderFrame::NoContext) {}
    thread->shutdown();
    return thread->getExitCode();
}
}
