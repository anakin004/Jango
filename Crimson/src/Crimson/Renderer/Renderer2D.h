#pragma once

#include "Crimson/Renderer/OrthographicCamera.h"

namespace Crimson {

	class Renderer2D
	{
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();


		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, const crm::vec4& color);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, const crm::vec4& color);

	};

}