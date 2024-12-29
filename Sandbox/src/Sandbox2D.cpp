#include "Crimson/Core/EntryPoint.h"

#include "Sandbox2D.h"
#include "imgui/imgui.h"


#include <crm_mth.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f)
{

}


void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Crimson::TimeStep timeStep)
{
	m_CameraController.OnUpdate(timeStep);

	Crimson::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
	Crimson::RenderCommand::Clear();

	Crimson::Renderer2D::BeginScene(m_CameraController.GetCamera());


	Crimson::Renderer2D::DrawQuad(crm::vec2{ 1.0f, 2.0f }, crm::vec2{ 2.0f,2.0f }, crm::vec4{ 0.2f,0.3f ,0.6f,1.0f });
	Crimson::Renderer2D::DrawQuad(crm::vec2{ -2.0f, -2.0f }, crm::vec2{ 1.0f,2.0f }, crm::vec4{ 0.2f,0.9f ,0.6f,1.0f });
	Crimson::Renderer2D::DrawQuad(crm::vec2{ -1.0f, -1.0f }, crm::vec2{ 0.5f,2.0f }, crm::vec4{ 0.5f,0.3f ,0.1f,1.0f });

	Crimson::Renderer2D::EndScene();


}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color", m_Red.data);
	ImGui::End();
}

void Sandbox2D::OnEvent(Crimson::Event& e)
{
	m_CameraController.OnEvent(e);

}
