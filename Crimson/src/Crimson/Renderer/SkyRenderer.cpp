
#include "cnpch.h"
#include "SkyRenderer.h"
#include "Atmosphere.h"

namespace Crimson {
	Ref<SkyRenderer> SkyRenderer::m_skyRenderer = nullptr;
	SkyType SkyRenderer::m_skyType = SkyType::CUBE_MAP_SKY;

	void SkyRenderer::Initilize(const std::string& path)
	{
		CubeMapEnvironment::Init(path);
		Atmosphere::InitilizeAtmosphere();
	}

	void SkyRenderer::RenderSky(Camera& camera)
	{
		m_skyType = SkyType::CUBE_MAP_SKY;
		switch (m_skyType)
		{
		case SkyType::CUBE_MAP_SKY:

			CubeMapEnvironment::RenderCubeMap(camera.GetViewMatrix(),camera.GetProjectionMatrix(),camera.GetViewDirection());
			break;
		case SkyType::PROCEDURAL_SKY:
			Atmosphere::RenderAtmosphere(camera);
			break;
		default:
			return;
		}
	}
}