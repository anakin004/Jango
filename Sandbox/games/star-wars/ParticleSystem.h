#pragma once

#include <Crimson.h>

struct ParticleProps
{
	crm::vec2 Position;
	crm::vec2 Velocity, VelocityVariation;
	crm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;

	crm::vec2& GetVelocity() { return Velocity; }
	crm::vec4& GetColorBegin() { return ColorBegin; }
	crm::vec4& GetColorEnd() { return ColorEnd; }
	float* GetSizeVariation() { return &SizeVariation; }
	float* GetLifeTime() { return &LifeTime; }
};

class ParticleSystem
{
public:
	ParticleSystem();

	void Emit(const ParticleProps& particleProps);

	void OnUpdate(Crimson::TimeStep ts);
	void OnRender();


private:
	struct Particle
	{
		crm::vec2 Position;
		crm::vec2 Velocity;
		crm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;
};