include(${NNCC_PROJECT_ROOT}/cmake/target_shader.cmake)

# Context: singleton for basic systems
set(NNCC_CONTEXT_DIR ${CMAKE_CURRENT_LIST_DIR}/context)
add_library(nncc-context SHARED ${NNCC_CONTEXT_DIR}/context_instance.cpp)
target_include_directories(nncc-context PUBLIC ${NNCC_PROJECT_ROOT}/include ${CMAKE_CURRENT_LIST_DIR}/.. ${CONAN_INCLUDE_DIRS_ENTT} ${NNCC_PROJECT_ROOT}/external/stb)
target_link_libraries(nncc-context PUBLIC bx bgfx CONAN_PKG::glfw CONAN_PKG::folly CONAN_PKG::imgui)

add_library(nncc SHARED ${NNCC_PROJECT_ROOT}/external/imnodes/imnodes/imnodes.cpp)
#set_target_properties(nncc PROPERTIES CXX_VISIBILITY_PRESET hidden)

set(NNCC_INCLUDES_PRIVATE ${NNCC_PROJECT_ROOT}/include ${CMAKE_CURRENT_LIST_DIR}/..)
set(NNCC_INCLUDES_PRIVATE ${NNCC_INCLUDES_PRIVATE} PARENT_SCOPE)
set(NNCC_INCLUDES ${NNCC_INCLUDES_PRIVATE})
set(NNCC_INCLUDES ${NNCC_INCLUDES} PARENT_SCOPE)

target_link_libraries(nncc PUBLIC
        bx bgfx
        CONAN_PKG::glfw
        CONAN_PKG::folly
        CONAN_PKG::imgui
        CONAN_PKG::double-conversion
        ${Python_LIBRARIES}
        nncc-context
        )
target_include_directories(nncc PUBLIC
        ${BGFX_DIR}/include ${BX_DIR}/include
        ${CONAN_INCLUDE_DIRS_ENTT}
        ${CONAN_INCLUDE_DIRS_GLFW}
        ${NNCC_PROJECT_ROOT}/external/stb
        ${NNCC_PROJECT_ROOT}/external/IconFontCppHeaders
        ${NNCC_PROJECT_ROOT}/external/ImGuizmo
        ${NNCC_PROJECT_ROOT}/external/imnodes
        ${CPP_REDIS_INCLUDES}
        ${NNCC_INCLUDES_PRIVATE}
        ${Python_INCLUDE_DIRS}
        )

# Common: types, utilities, macros
set(NNCC_COMMON_DIR ${CMAKE_CURRENT_LIST_DIR}/common)
target_sources(nncc PRIVATE ${NNCC_COMMON_DIR}/image.cpp)

# Context: singleton for basic systems
set(NNCC_CONTEXT_DIR ${CMAKE_CURRENT_LIST_DIR}/context)
target_sources(
        nncc PRIVATE
        ${NNCC_CONTEXT_DIR}/context.cpp
        ${NNCC_CONTEXT_DIR}/glfw_utils.cpp
)

## Input: abstraction for key/mouse/char events, event queue
set(NNCC_INPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/input)
target_sources(
        nncc PRIVATE
        ${NNCC_INPUT_DIR}/event.cpp
        ${NNCC_INPUT_DIR}/hid.cpp
)

# Engine: basic loop for rendering, navigation, GUI, timer, subsystems
set(NNCC_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/engine)
target_sources(
        nncc PRIVATE
        ${NNCC_ENGINE_DIR}/camera.cpp
        ${NNCC_ENGINE_DIR}/loop.cpp
)

# GUI: ImGui+bgfx, derived controls
set(NNCC_GUI_DIR ${CMAKE_CURRENT_LIST_DIR}/gui)
target_sources(
        nncc PRIVATE
        ${NNCC_GUI_DIR}/imgui_bgfx.cpp
        ${NNCC_GUI_DIR}/imgui_smart_strings.cpp
        ${NNCC_GUI_DIR}/guizmo.cpp
        ${NNCC_GUI_DIR}/picking.cpp
        ../../external/ImGuizmo/ImGuizmo/ImGuizmo.cpp
)
target_shader(nncc ${NNCC_GUI_DIR}/shaders/fs_imgui_image.sc FRAGMENT)
target_shader(nncc ${NNCC_GUI_DIR}/shaders/vs_imgui_image.sc VERTEX)
target_shader(nncc ${NNCC_GUI_DIR}/shaders/fs_ocornut_imgui.sc FRAGMENT)
target_shader(nncc ${NNCC_GUI_DIR}/shaders/vs_ocornut_imgui.sc VERTEX)
target_shader(nncc ${NNCC_GUI_DIR}/shaders/picking/fs_picking.sc FRAGMENT)
target_shader(nncc ${NNCC_GUI_DIR}/shaders/picking/vs_picking.sc VERTEX)

# Compute platform
set(NNCC_COMPUTE_DIR ${CMAKE_CURRENT_LIST_DIR}/compute)
target_sources(
        nncc PRIVATE
        ${NNCC_COMPUTE_DIR}/graph.cpp
        ${NNCC_COMPUTE_DIR}/algebra_ops.cpp
)

# Math: vector and matrix ops
set(NNCC_MATH_DIR ${CMAKE_CURRENT_LIST_DIR}/math)
target_sources(nncc PRIVATE ${NNCC_MATH_DIR}/types.cpp)

# Rendering subsystem
set(NNCC_RENDERING_DIR ${CMAKE_CURRENT_LIST_DIR}/rendering)
target_shader(nncc ${NNCC_RENDERING_DIR}/shaders/default_diffuse/vs_default_diffuse.sc VERTEX)
target_shader(nncc ${NNCC_RENDERING_DIR}/shaders/default_diffuse/fs_default_diffuse.sc FRAGMENT)
target_sources(
        nncc PRIVATE
        ${NNCC_RENDERING_DIR}/surface.cpp
        ${NNCC_RENDERING_DIR}/batch_renderer.cpp
        ${NNCC_RENDERING_DIR}/renderer.cpp
        ${NNCC_RENDERING_DIR}/rendering.cpp
        ${NNCC_RENDERING_DIR}/bgfx/loaders.cpp
)
