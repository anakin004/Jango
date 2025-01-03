#pragma once

#include "Crimson.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Crimson::Layer
{
public:

	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Crimson::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Crimson::Event& e) override;
	bool OnMouseButtonPressed(Crimson::MouseButtonPressedEvent& e);
	bool OnWindowResize(Crimson::WindowResizeEvent& e);

private:

	void CreateCamera(uint32_t width, uint32_t height);

private:

	Crimson::Scope<Crimson::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};