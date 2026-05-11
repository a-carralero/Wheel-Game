#pragma once
#include <cstdint>
#include <string_view>
#include "cmp/entity.hpp"
#include "man/entitymanager.hpp"

#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

struct GLFWwindow;
struct EntityManager;
struct Entity;

struct RenderSys_ImGui
{
private:
   GLFWwindow* window = nullptr;
   int32_t m_selEntity = 0;

   void Imgui_renderUI(EntityManager& em);
   void Imgui_renderFramebuffer(uint32_t* screen);
   void Imgui_postrender();
   void Imgui_showSelectedEntityData(EntityManager& em);
   Entity& ImGui_getSelectedEntity(EntityManager& em);
   void ImGui_showComponentData(EntityManager& em, Entity& e);
   void ImGui_showStatusComponent(EntityManager& em, Entity& e);
   void ImGui_showAIComponent(EntityManager& em, Entity& e);


   template <typename Cmp_t>
   bool ImGui_componentButton(EntityManager& em, Entity& e, std::string_view cmpname){
      bool hasCmp = e.hasCmp<Cmp_t>();
      bool wantsCmp = hasCmp;
      ImGui::Checkbox(cmpname.data(), &wantsCmp);
      if (hasCmp != wantsCmp){
         if (wantsCmp) em.addComponent<Cmp_t>(e);
         else          em.destroyEntityByID(e.getEntityID());
      }
      return wantsCmp;
   }

public:
   RenderSys_ImGui();
   ~RenderSys_ImGui();
   void prerender();
   void update(EntityManager& em, uint32_t* screen);
};