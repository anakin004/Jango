#include "GameLayer.h"
#include <imgui/imgui.h>

#include <crm_mth.h>

using namespace Crimson;

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 20.0f);
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate(Crimson::TimeStep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
	case GameState::Play:
	{
		m_Level.OnUpdate(ts);
		break;
	}
	}

	// Render
	Crimson::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Crimson::RenderCommand::Clear();

	Crimson::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Crimson::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{

	ImGui::Begin("Settings");
	m_Level.OnImGuiRender();
	ImGui::End();

	
}

void GameLayer::OnEvent(Crimson::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(CN_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(CN_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Crimson::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Crimson::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = MakeScope<OrthographicCamera>(left, right, top, bottom);
}