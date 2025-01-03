#pragma once

#include "Crimson/Renderer/OrthographicCamera.h"
#include "Crimson/Renderer/Texture.h"
#include "Crimson/Renderer/RendererAPI.h"

namespace Crimson {

	class Renderer2D
	{
	public:

		struct QuadProperties {

			float rotation;

			QuadProperties(float rotation = 0.0f)
				: rotation(rotation)
			{
			}

		};


		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, const crm::vec4& color);
		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, const Ref<Texture2D> texture);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, const crm::vec4& color);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, const Ref<Texture2D> texture);

		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, float rotation, const crm::vec4& color);
		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, float rotation, const Ref<Texture2D> texture);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, float rotation, const crm::vec4& color);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, float rotation, const Ref<Texture2D> texture);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};

}