#include <cstdio>
#include <exception>
#include <algorithm>
#include <cassert>

#include "sys/render_imgui.hpp"
#include "man/entitymanager.hpp"
#include "util/constants.hpp"
#include "cmp/debug.hpp"

#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "cmp/render.hpp"
#include "cmp/input.hpp"
#include "cmp/collider.hpp"
#include "cmp/physics.hpp"
#include "cmp/status.hpp"
#include "cmp/spawner.hpp"
#include "cmp/camera.hpp"


RenderSys_ImGui::RenderSys_ImGui()
{
   // setup window
   glfwSetErrorCallback([](auto error, auto description){
      std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
      std::terminate();
   });

   if (!glfwInit())
      std::terminate();

      // GL 3.0 + GLSL 130
   const char* glsl_version = "#version 130";
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
   //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

   // Create window with graphics context
   // float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
   // GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Game", nullptr, nullptr);
   window = glfwCreateWindow(960, 720, "Game", nullptr, nullptr);
   if (window == nullptr)
      std::terminate();
   glfwMakeContextCurrent(window);
   glfwSwapInterval(1); // Enable vsync

   // Init OpenGL Loader
   if (glewInit() != GLEW_OK) std::terminate();

   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();
   //ImGui::StyleColorsLight();

   // Setup scaling
   // ImGuiStyle& style = ImGui::GetStyle();
   // style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
   // style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);
}

RenderSys_ImGui::~RenderSys_ImGui()
{
   // Cleanup
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   if(window)
      glfwDestroyWindow(window);
   glfwTerminate();
}


void RenderSys_ImGui::prerender()
{
   // Poll and handle events (inputs, window resize, etc.)
   // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
   // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
   // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
   // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
   glfwPollEvents();
   if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
   {
      ImGui_ImplGlfw_Sleep(10);
      return;
   }

   // Start the Dear ImGui frame
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();
}

void RenderSys_ImGui::
ImGui_showStatusComponent(EntityManager& em, Entity& e)
{
   if (!ImGui_componentButton<StatusCmp>(em, e, "StatusCmp")) return;
   StatusCmp& st = e.getComponent<StatusCmp>();

   ImGui::BeginTable("StatusCmp", 2, 0, ImVec2(300.0, 0.0));
   //------------------------------------------------------------
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Health");
   ImGui::TableNextColumn();
   ImGui::InputDouble("##HST", &st.health , 1.0, 5.0, "%.2f");
   ImGui::SameLine();
   ImGui::ProgressBar(st.health/100.0);
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Ammo ");
   ImGui::TableNextColumn();
   uint16_t ammo = static_cast<uint16_t>(st.ammo);
   static uint16_t constexpr min{1}, max{5};
   ImGui::InputScalar("##AST", ImGuiDataType_U16, &ammo, &min, &max);
   st.ammo = ammo;
   ImGui::EndTable();
}

void RenderSys_ImGui::
ImGui_showAIComponent(EntityManager& em, Entity& e)
{
   if (!ImGui_componentButton<AiCmp>(em, e, "AICmp")) return;
   AiCmp& ai = e.getComponent<AiCmp>();

   ImGui::BeginTable("AICmp", 2, 0, ImVec2(300.0, 0.0));
   //------------------------------------------------------------
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Perception Frec");
   ImGui::TableNextColumn();
   double freq = 1.0 / ai.perceptionTime;
   ImGui::InputDouble("##PF", &freq, 0.2, 1.0, "%.2f");
   ai.perceptionTime = 1.0 / freq;
   //------------------------------------------------------------
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Arrival Radius ");
   ImGui::TableNextColumn();
   ImGui::InputDouble("##AR", &ai.arrivalRadius, 1.0, 5.0, "%.2f");
   //------------------------------------------------------------
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Time 2 arrive  ");
   ImGui::TableNextColumn();
   ImGui::InputDouble("##T2A", &ai.time2arrive, 0.1, 0.5, "%.2f");
   //------------------------------------------------------------
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Time 2 Perceive  ");
   ImGui::TableNextColumn();
   double timeToPerceive = (ai.perceptionTime - ai.accumulated_dt) / ai.perceptionTime;
   ImGui::ProgressBar(timeToPerceive);
   //------------------------------------------------------------
   ImGui::TableNextRow(); ImGui::TableNextColumn();
   ImGui::Text("Behaviour  ");
   ImGui::TableNextColumn();
   int behitem = static_cast<int>(ai.behaviour);
   ImGui::Combo("##Beh", &behitem, ai.SB_names.data(), ai.SB_names.size());
   if (behitem >= 0 && behitem < static_cast<int>(ai.SB_names.size()))
      ai.behaviour = static_cast<SB>(behitem);
   //------------------------------------------------------------
   ImGui::EndTable();
}

void RenderSys_ImGui::
ImGui_showComponentData(EntityManager& em, Entity& e)
{
   ImGui_componentButton<RenderCmp>(em, e, "RenderCmp");
   ImGui_componentButton<InputCmp>(em, e, "InputCmp");
   ImGui_componentButton<ColliderCmp>(em, e, "ColliderCmp");
   ImGui_componentButton<PhysicsCmp>(em, e, "PhysicsCmp");
   ImGui_componentButton<SpawnerCmp>(em, e, "SpawnerCmp");
   ImGui_componentButton<CameraCmp>(em, e, "CameraCmp");
   ImGui_showStatusComponent(em, e);
   ImGui_showAIComponent(em, e);
}

Entity& RenderSys_ImGui::
ImGui_getSelectedEntity(EntityManager& em)
{
   m_selEntity = std::clamp(m_selEntity, 0, static_cast<int32_t>(em.numberOfEntities() - 1));
   return em.getEntityByID(static_cast<uint32_t>(m_selEntity));
}


void RenderSys_ImGui::
Imgui_showSelectedEntityData(EntityManager& em)
{
   Entity& entity = ImGui_getSelectedEntity(em);

   ImGui::Begin("Entity Viewer");
   if (ImGui::Button("Clone")){
   }
   ImGui::SameLine();
   if (ImGui::Button("Destroy")){
      em.destroyEntityByID(entity.getEntityID());
   }
   ImGui::Text("EID: %u", entity.getEntityID());
   ImGui::SameLine(); if (ImGui::Button("-")) --m_selEntity;
   ImGui::SameLine(); if (ImGui::Button("+")) ++m_selEntity;
   ImGui_showComponentData(em, entity);
   ImGui::End();
}

void RenderSys_ImGui::Imgui_renderUI(EntityManager& em)
{
   auto& io = ImGui::GetIO();

   // Debug Window
   DebugBoard& dbg = em.getDebugBoard();
   ImGui::Begin("Debug Window");
   if (ImGui::CollapsingHeader("Execution")){
      ImGui::Checkbox("Pause", &dbg.pause.value);
      ImGui::Text("FPS  "); ImGui::SameLine();
      ImGui::InputDouble("##I1", &dbg.fps, 1.0, 5.0, "%.2f", 0);
      ImGui::Text("SimFPS  "); ImGui::SameLine();
      ImGui::InputDouble("##I2", &dbg.simfps, 1.0, 5.0, "%.2f", 0);
      ImGui::Text("Running: %.2f FPS, %.2f mspf", io.Framerate, 1000.0f/io.Framerate);
      dbg.fps = std::clamp(dbg.fps, 0.01, 500.0);
      dbg.simfps = std::clamp(dbg.simfps, 0.01, 500.0);
   }
   ImGui::Checkbox("Show AI Targets", &dbg.showDegubCross);
   ImGui::End();

   // 
   Imgui_showSelectedEntityData(em);

}
   

void RenderSys_ImGui::Imgui_renderFramebuffer(uint32_t* screen)
{
   int display_w, display_h;
   glfwGetFramebufferSize(window, &display_w, &display_h);
   display_h -= KHEIGHT;
   if (display_h < 0) display_h = 0;
   glWindowPos2i(0,display_h);
   glDrawPixels(KWIDTH, KHEIGHT, GL_BGRA, GL_UNSIGNED_BYTE, screen);
}

void RenderSys_ImGui::Imgui_postrender() 
{
   // Rendering
   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   glfwSwapBuffers(window);
}

void RenderSys_ImGui::update(EntityManager& em, uint32_t* screen)
{
   glClear(GL_COLOR_BUFFER_BIT);
   Imgui_renderUI(em);
   // Render Frame Buffer in OpenGL context
   Imgui_renderFramebuffer(screen);
   Imgui_postrender();
}