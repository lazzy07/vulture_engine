#pragma once

//For used by the applications
#include "Vulture/Core/Application.h"
#include "Vulture/Core/Layer.h"
#include "Vulture/Core/Log.h"

#include "Vulture/Core/Timestep.h"

#include "Vulture/Core/Input.h"
#include "Vulture/Core/KeyCodes.h"
#include "Vulture/Core/MouseButtonCodes.h"

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
#include "Vulture/Core/CameraController.h"
//*************************************************


//**************DispatchQueue**********************
#include "Vulture/Core/DispatchQueue.h"
//*************************************************

//**************ModelLoader**********************
#include "Vulture/Renderer/ModelLoader.h"
//*************************************************

//***************EntryPoint************************
#include "Vulture/Core/EntryPoint.h"
//*************************************************