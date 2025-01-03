#include "Level.h"



static crm::vec4 HSVtoRGB(const crm::vec3& hsv) {
	return { 0.0f,0.0f,0.0f,0.0f };
}

static bool PointInTri(const crm::vec2& p, crm::vec2& p0, const crm::vec2& p1, const crm::vec2& p2)
{
}


void Level::Init()
{
	m_Player.LoadAssets();

}

void Level::OnUpdate(Crimson::TimeStep ts)
{
	m_Player.OnUpdate(ts);

}

void Level::OnRender()
{
	const auto& playerPos = m_Player.GetPosition();

	Crimson::Renderer2D::DrawQuad({ playerPos.x, 0.0f, -0.8f }, { 200.0f, 200.0f }, { 0.3f, 0.3f, 0.3f, 1.0f }, Crimson::Renderer2D::QuadProperties{ 0.0f });

	m_Player.OnRender();
}

void Level::OnImGuiRender()
{
	m_Player.OnImGuiRender();
}

void Level::CreatePillar(int index, float offset)
{

}

bool Level::CollisionTest()
{
	return false;
}

void Level::GameOver()
{
	m_GameOver = true;
}

void Level::Reset()
{
	m_GameOver = false;

	m_Player.Reset();

	
}