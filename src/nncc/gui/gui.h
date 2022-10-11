#pragma once

#include <entt/entt.hpp>
#include <nncc/gui/imgui/imgui_bgfx.h>

namespace nncc::gui {

struct GuiPiece {
    entt::delegate<void()> render;
};

}