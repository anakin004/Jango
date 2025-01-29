#include "Player.h"

#include "Crimson/Core/KeyCodes.h"
#include "Crimson/Renderer/Renderer2D.h"

#include <crm_mth.h>
#include "imgui/imgui.h"

using namespace Crimson;

Player::Player()
{
	// Smoke
	m_SmokeParticle.Position = { 0.0f, 0.0f };
	m_SmokeParticle.Velocity = { -2.0f, 0.0f }, m_SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
	m_SmokeParticle.SizeBegin = 0.35f, m_SmokeParticle.SizeEnd = 0.0f, m_SmokeParticle.SizeVariation = 0.15f;
	m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_SmokeParticle.LifeTime = 4.0f;

	// Flames
	m_EngineParticle.Position = { 0.0f, 0.0f };
	m_EngineParticle.Velocity = { -2.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
	m_EngineParticle.SizeBegin = 0.5f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
	m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
	m_EngineParticle.LifeTime = 1.0f;
}

void Player::LoadAssets()
{
	m_ShipTexture = Texture2D::Create("assets/textures/Ship.png");
}

void Player::OnUpdate(Crimson::TimeStep ts)
{
	m_Time += ts;

	if (Input::IsKeyPressed(CRIMSON_KEY_SPACE))
	{

		m_Velocity.y += m_EnginePower;
		if (m_Velocity.y < 0.0f)
			m_Velocity.y += m_EnginePower * 2.0f;

		// Flames
		crm::vec2 emissionPoint = { 0.0f, -0.6f };
		crm::vec4 rotated = crm::Mul(crm::ZRotation(GetRotation()), crm::vec4(emissionPoint.x, emissionPoint.y, 0.0f, 1.0f));
		m_EngineParticle.Position = crm::Add(m_Position, crm::vec2{ rotated.x, rotated.y });
		m_EngineParticle.Velocity.y = -m_Velocity.y * 0.2f - 0.2f;
		m_ParticleSystem.Emit(m_EngineParticle);
	}

	else
	{
		m_Velocity.y -= m_Gravity;
	}

		// player position updating

	m_Velocity.y = std::clamp(m_Velocity.y, -19.0f, 19.0f);
	m_Position = crm::Add(m_Position, crm::Mul(m_Velocity, ts * 1/2.f));

	// Particles
	if (m_Time > m_SmokeNextEmitTime)
	{
		m_SmokeParticle.Position = m_Position;
		m_ParticleSystem.Emit(m_SmokeParticle);
		m_SmokeNextEmitTime += m_SmokeEmitInterval;
	}

	m_ParticleSystem.OnUpdate(ts);

}

void Player::OnRender()
{
	m_ParticleSystem.OnRender();
	Renderer2D::DrawQuad(crm::vec3{ m_Position.x, m_Position.y, 0.5f }, crm::vec2{ 1.0f, 1.3f }, m_ShipTexture, Renderer2D::QuadProperties{ GetRotation()});
}

void Player::OnImGuiRender()
{

	ImGui::Begin("Settings");
	ImGui::SliderFloat2("Ship Velocity", &m_Velocity.x, 0.1f, 10.f, "%.3f");
	ImGui::SliderFloat("Engine Power", &m_EnginePower, 0.1f, 10.f, "%.3f");
	ImGui::SliderFloat("Gravity", &m_Gravity, 0.1f, 10.f, "%.3f");

	ImGui::ColorEdit4("Particle Color Begin", &m_EngineParticle.GetColorBegin().r);
	ImGui::ColorEdit4("Particle Color End", &m_EngineParticle.GetColorEnd().r);
	ImGui::SliderFloat2("Particle Velocity", &m_EngineParticle.GetVelocity().x, -10.0f, 10.f, "%.3f");
	ImGui::SliderFloat("Particle Lifetime", m_EngineParticle.GetLifeTime(), 0.1f, 10.f, "%.3f");
	ImGui::SliderFloat("Size Variation", m_EngineParticle.GetSizeVariation(), 0.0f, 50.f, "%.3f");


	ImGui::End();

}

void Player::Reset()
{
	m_Position = { -10.0f, 0.0f };
	m_Velocity = { 5.0f, 0.0f };
}