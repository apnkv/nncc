#pragma once

#include <nncc/gui/imgui_bgfx.h>

namespace nncc::gui {

void EditWithGuizmo(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition = true);

}

