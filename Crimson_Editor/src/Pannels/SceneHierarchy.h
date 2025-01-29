#pragma once
#include "Crimson/Scene/Scene.h"
#include "Crimson/Scene/Entity.h"
#include "Crimson/Core/Core.h"
#include "Crimson/Core/Log.h"

using namespace Crimson;
class Crimson::PointLight;
class SceneHierarchyPannel {
public:
	SceneHierarchyPannel();
	~SceneHierarchyPannel();
	void Context(const Ref<Scene>& context);
	void OnImGuiRender();
public:
	static Ref<Entity> m_selected_entity;
private:
	Ref<Scene> m_Context;
	PointLight* m_selected_Light = nullptr;

	glm::vec3 PointLight_position = { 0,0,0 }, PointLight_color = {1,1,1};
	//For properties pannel (camera ui)
	//glm::vec3 translation=glm::vec3(0);
private:
	void DrawHierarchyNode(const Entity* ent);
	void DrawProperties();
	void DrawTransformUI();
	void DrawCameraUI();
	void DrawTagUI();
	void DrawSpriteRendererUI();
	void DrawStaticMeshComponentUI();
	void DrawPhysicsComponentUI();
	void DrawScriptComponentUI();
	bool bDrawScript_comp = false;
};
