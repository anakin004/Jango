#include "cnpch.h"
#include "Camera.h"
#include "EditorCamera.h"
#include "SceneCamera.h"
namespace Crimson {

	Ref<Camera> Camera::GetCamera(CameraType type)
	{
		switch (type)
		{
		case CameraType::EDITOR_CAMERA:
			return MakeRef<EditorCamera>();
		case CameraType::SCENE_CAMERA:
			return MakeRef<SceneCamera>();
		default:
			CN_CORE_ERROR("Select a valid Camera Type");
			return nullptr;
		}
	}
}
