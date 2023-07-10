/*****************************************************************//**
 * @file   Lithe.hpp
 * @brief  Essential headers file
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once

#include "Lithe/Core/Application.hpp"
#include "Lithe/Core/Log.hpp"
#include "Lithe/Core/Layer.hpp"
#include "Lithe/Core/Platform.hpp"
#include "Lithe/Core/Timestep.hpp"

#include "Lithe/Events/Events.hpp"
#include "Lithe/Input/Keyboard.hpp"
#include "Lithe/Input/Mouse.hpp"
#include "Lithe/Input/CameraController.hpp"

#include "Lithe/ImGui/ImGuiLayer.hpp"

#include "Lithe/Scene/Scene.hpp"
#include "Lithe/Scene/Entity.hpp"
#include "Lithe/Scene/Components.hpp"
#include "Lithe/Scene/Components/Camera/Camera.hpp"
#include "Lithe/Scene/Components/Camera/PerspectiveCamera.hpp"

#include <ImGui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <EnTT/entt.hpp>
