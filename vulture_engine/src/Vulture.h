#pragma once

//For used by the applications
#include "Vulture/Application.h"
#include "Vulture/Layer.h"
#include "Vulture/Log.h"

#include "Vulture/Core/Timestep.h"

#include "Vulture/Input.h"
#include "Vulture/KeyCodes.h"
#include "Vulture/MouseButtonCodes.h"

//Debugging GUI layer
#include "Vulture/ImGui/ImGuiLayer.h"


//***************Renderer************************
//Renderer
#include "Vulture/Renderer/Renderer.h"
#include "Vulture/Renderer/RenderCommand.h"

//Renderer resources
#include "Vulture/Renderer/Buffer.h"
#include "Vulture/Renderer/Shader.h"
#include "Vulture/Renderer/Texture.h"
#include "Vulture/Renderer/VertexArray.h"

//Cameras
#include "Vulture/Renderer/OrthographicCamera.h"
#include "Vulture/Renderer/PerspectiveCamera.h"
#include "Vulture/CameraController.h"

//*************************************************


//***************EntryPoint************************
#include "Vulture/EntryPoint.h"
//*************************************************