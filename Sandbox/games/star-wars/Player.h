#pragma once
#pragma once

#include <Crimson.h>

#include "Color.h"
#include "Random.h"

#include "ParticleSystem.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Crimson::TimeStep ts);
	void OnRender();

	void OnImGuiRender();

	void Reset();

	float GetRotation() { return -m_Velocity.y * 4.0f + 90.f; }
	const crm::vec2& GetPosition() const { return m_Position; }

	uint32_t GetScore() const { return (uint32_t)(m_Position.x + 10.0f) / 10.0f; }

private:
	crm::vec2 m_Position = { -10.0f, 0.0f };
	crm::vec2 m_Velocity = { 6.0f, 3.0f };

	float m_EnginePower = 0.5f;
	float m_Gravity = 0.4f;

	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	ParticleProps m_SmokeParticle, m_EngineParticle;
	ParticleSystem m_ParticleSystem;

	Crimson::Ref<Crimson::Texture2D> m_ShipTexture;
};