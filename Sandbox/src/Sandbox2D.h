#pragma once

#include <Crimson.h>

#include "Crimson/Renderer/Renderer2D.h"

class Sandbox2D : public Crimson::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Crimson::TimeStep timeStep) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Crimson::Event& e) override;
private:
	Crimson::OrthographicCameraController m_CameraController;

	 
	Crimson::Ref<Crimson::Shader> m_Shader;
	Crimson::Ref<Crimson::VertexArray> m_SquareVA;
	Crimson::Ref<Crimson::Texture2D> m_Texture;

	crm::vec4 m_Red = { 0.8f, 0.2f, 0.3f, 1.0f };

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;


};