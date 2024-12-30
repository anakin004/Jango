#include "Crimson/Core/EntryPoint.h"

#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "Crimson/Debug/Instrumentor.h"

#include <crm_mth.h>

#include <stdio.h>

#define PROFILE_SCOPE(name) Crimson::Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f), m_ProfileResults(),
	m_QuadProperties(1.0f, 0.0f, crm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f } )
{
}


void Sandbox2D::OnAttach()
{
	CN_PROFILE_FUNCTION()

	m_Texture = Crimson::Texture2D::Create("assets/textures/linux.png");
	m_Texture->Bind(0);
}

void Sandbox2D::OnDetach()
{
	CN_PROFILE_FUNCTION()

}

void Sandbox2D::OnUpdate(Crimson::TimeStep timeStep)
{

	CN_PROFILE_FUNCTION()

	m_CameraController.OnUpdate(timeStep);


	Crimson::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
	Crimson::RenderCommand::Clear();

	Crimson::Renderer2D::BeginScene(m_CameraController.GetCamera());

	{
		CN_PROFILE_SCOPE("Sandbox2D::Render")
// 		Crimson::Renderer2D::DrawQuad(crm::vec2{ 1.0f, 2.0f }, crm::vec2{ 2.0f,2.0f }, crm::vec4{ 0.2f,0.3f ,0.6f,1.0f }, m_QuadProperties);
// 		Crimson::Renderer2D::DrawQuad(crm::vec2{ -2.0f, -2.0f }, crm::vec2{ 1.0f,2.0f }, crm::vec4{ 0.2f,0.9f ,0.6f,1.0f }, m_QuadProperties);
// 		Crimson::Renderer2D::DrawRotatedQuad(crm::vec2{ -1.0f, -1.0f }, crm::vec2{ 0.5f,2.0f }, crm::vec4{ 0.5f,0.3f ,0.1f,1.0f }, m_QuadProperties);
		Crimson::Renderer2D::DrawRotatedQuad(crm::vec3{ 0.0f, 0.0f, -0.5f }, crm::vec2{ 5.0f,5.0f }, m_Texture, m_QuadProperties);
	}

	Crimson::Renderer2D::EndScene();


}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Tint", m_QuadProperties.textureTintColor.data);

	ImGui::SliderFloat("Rotation", &m_QuadProperties.rotation, 0.1f, 360.0f, "%.2f");
	ImGui::SliderFloat("Tiling-Factor", &m_QuadProperties.tilingFactor, 1.0f, 60.0f, "%.2f");

	ImGui::End();
}

void Sandbox2D::OnEvent(Crimson::Event& e)
{
	m_CameraController.OnEvent(e);

}
