#pragma once

#if defined(USE_IMGUI_GLFW)
   #include "imgui/src/imgui.h"
   typedef ImGuiKey KeySym;

   #define KS_0 ImGuiKey_0
   #define KS_1 ImGuiKey_1
   #define KS_2 ImGuiKey_2
   #define KS_3 ImGuiKey_3
   #define KS_4 ImGuiKey_4
   #define KS_5 ImGuiKey_5
   #define KS_6 ImGuiKey_6
   #define KS_7 ImGuiKey_7
   #define KS_8 ImGuiKey_8
   #define KS_9 ImGuiKey_9
   #define KS_A ImGuiKey_A
   #define KS_B ImGuiKey_B
   #define KS_C ImGuiKey_C
   #define KS_D ImGuiKey_D
   #define KS_E ImGuiKey_E
   #define KS_F ImGuiKey_F
   #define KS_G ImGuiKey_G
   #define KS_H ImGuiKey_H
   #define KS_I ImGuiKey_I
   #define KS_J ImGuiKey_J
   #define KS_K ImGuiKey_K
   #define KS_L ImGuiKey_L
   #define KS_M ImGuiKey_M
   #define KS_N ImGuiKey_N
   #define KS_O ImGuiKey_O
   #define KS_P ImGuiKey_P
   #define KS_Q ImGuiKey_Q
   #define KS_R ImGuiKey_R
   #define KS_S ImGuiKey_S
   #define KS_T ImGuiKey_T
   #define KS_U ImGuiKey_U
   #define KS_V ImGuiKey_V
   #define KS_W ImGuiKey_W
   #define KS_X ImGuiKey_X
   #define KS_Y ImGuiKey_Y
   #define KS_Z ImGuiKey_Z
   #define KS_RIGHT  ImGuiKey_RightArrow
   #define KS_LEFT   ImGuiKey_LeftArrow
   #define KS_DOWN   ImGuiKey_DownArrow
   #define KS_UP     ImGuiKey_UpArrow
   #define KS_SPACE  ImGuiKey_Space
   #define KS_ENTER  ImGuiKey_Enter
   #define KS_ESCAPE ImGuiKey_Escape

   // #define KS_0 GLFW_KEY_0
   // #define KS_1 GLFW_KEY_1
   // #define KS_2 GLFW_KEY_2
   // #define KS_3 GLFW_KEY_3
   // #define KS_4 GLFW_KEY_4
   // #define KS_5 GLFW_KEY_5
   // #define KS_6 GLFW_KEY_6
   // #define KS_7 GLFW_KEY_7
   // #define KS_8 GLFW_KEY_8
   // #define KS_9 GLFW_KEY_9
   // #define KS_A GLFW_KEY_A
   // #define KS_B GLFW_KEY_B
   // #define KS_C GLFW_KEY_C
   // #define KS_D GLFW_KEY_D
   // #define KS_E GLFW_KEY_E
   // #define KS_F GLFW_KEY_F
   // #define KS_G GLFW_KEY_G
   // #define KS_H GLFW_KEY_H
   // #define KS_I GLFW_KEY_I
   // #define KS_J GLFW_KEY_J
   // #define KS_K GLFW_KEY_K
   // #define KS_L GLFW_KEY_L
   // #define KS_M GLFW_KEY_M
   // #define KS_N GLFW_KEY_N
   // #define KS_O GLFW_KEY_O
   // #define KS_P GLFW_KEY_P
   // #define KS_Q GLFW_KEY_Q
   // #define KS_R GLFW_KEY_R
   // #define KS_S GLFW_KEY_S
   // #define KS_T GLFW_KEY_T
   // #define KS_U GLFW_KEY_U
   // #define KS_V GLFW_KEY_V
   // #define KS_W GLFW_KEY_W
   // #define KS_X GLFW_KEY_X
   // #define KS_Y GLFW_KEY_Y
   // #define KS_Z GLFW_KEY_Z
   // #define KS_RIGHT GLFW_KEY_RIGHT
   // #define KS_LEFT GLFW_KEY_LEFT
   // #define KS_DOWN GLFW_KEY_DOWN
   // #define KS_UP GLFW_KEY_UP
   // #define KS_SPACE GLFW_KEY_SPACE
   // #define KS_ENTER GLFW_KEY_ENTER
   // #define KS_ESCAPE GLFW_KEY_ESCAPE
#else
   #include <X11/X.h>
   #include <X11/keysym.h>
   typedef unsigned long KeySym;

   #define KS_0 XK_0
   #define KS_1 XK_1
   #define KS_2 XK_2
   #define KS_3 XK_3
   #define KS_4 XK_4
   #define KS_5 XK_5
   #define KS_6 XK_6
   #define KS_7 XK_7
   #define KS_8 XK_8
   #define KS_9 XK_9
   #define KS_A XK_a
   #define KS_B XK_b
   #define KS_C XK_c
   #define KS_D XK_d
   #define KS_E XK_e
   #define KS_F XK_f
   #define KS_G XK_g
   #define KS_H XK_h
   #define KS_I XK_i
   #define KS_J XK_j
   #define KS_K XK_k
   #define KS_L XK_l
   #define KS_M XK_m
   #define KS_N XK_n
   #define KS_O XK_o
   #define KS_P XK_p
   #define KS_Q XK_q
   #define KS_R XK_r
   #define KS_S XK_s
   #define KS_T XK_t
   #define KS_U XK_u
   #define KS_V XK_v
   #define KS_W XK_w
   #define KS_X XK_x
   #define KS_Y XK_y
   #define KS_Z XK_z
   #define KS_RIGHT XK_Right
   #define KS_LEFT XK_Left
   #define KS_DOWN XK_Down
   #define KS_UP XK_Up
   #define KS_SPACE XK_space
   #define KS_ENTER XK_Return
   #define KS_ESCAPE XK_Escape
#endif