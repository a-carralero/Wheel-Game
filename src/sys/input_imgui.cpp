#include "cmp/input.hpp"
#include "sys/input_imgui.hpp"
#include "imgui/src/imgui.h"


bool InputSys_ImGui::isKeyPressed(KeySym k) const
{
   auto& io = ImGui::GetIO();
   return !io.WantCaptureKeyboard && ImGui::IsKeyPressed(k);
}

bool InputSys_ImGui::isKeyDown(KeySym k) const
{
   auto& io = ImGui::GetIO();
   return !io.WantCaptureKeyboard && ImGui::IsKeyDown(k);
}