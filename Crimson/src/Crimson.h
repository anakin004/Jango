#pragma once


//only used by Crimson applications

#include "Crimson/Core/Core.h"
#include "Crimson/Core/UUID.h"
#include "Crimson/Core/Application.h"
#include "Crimson/Core/Layer.h"
#include "Crimson/Core/Log.h"
#include "Crimson/ImGui/ImGuiLayer.h"

#include "Crimson/Core/Input.h"
#include "Crimson/Core/KeyCodes.h"
#include "Crimson/ImGui/ImGuiLayer.h"
#include "Crimson/Scene/Scene.h"
#include "Crimson/Scene/Entity.h"
#include "Crimson/Scene/Component.h"
#include "Crimson/Scene/ScriptableEntity.h"

//-------Non Crimson api----------------
#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/matrix_major_storage.hpp"
#include "entt.hpp"

// ---Renderer------------------------
#include "Crimson/Renderer/Renderer.h"
#include "Crimson/Renderer/Renderer2D.h"
#include "Crimson/Renderer/Renderer3D.h"
#include "Crimson/Renderer/RenderCommand.h"
#include "Crimson/Renderer/Buffer.h"
#include "Crimson/Renderer/Shader.h"
#include "Crimson/Renderer/OrthographicCamera.h"
#include "Crimson/Controller/OrthographicCameraController.h"
#include "Crimson/Renderer/Texture.h"
#include "Crimson/Renderer/SubTexture.h"
#include "Crimson/Renderer/FrameBuffer.h"
#include "Crimson/Renderer/Cameras/SceneCamera.h"
#include "Crimson/Renderer/Cameras/EditorCamera.h"
#include "Crimson/Renderer/Bloom.h"
#include "Crimson/Mesh/LoadMesh.h"
// -----------------------------------
// 
//----------features------------------
#include "Crimson/Renderer/CubeMapEnvironment.h"

//.....EntryPoint................................
//#include "Crimson/EntryPoint.h"
//...............................................