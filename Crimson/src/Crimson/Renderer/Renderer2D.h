#pragma once

#include "Crimson/Renderer/OrthographicCamera.h"
#include "Crimson/Renderer/Texture.h"
#include "Crimson/Renderer/RendererAPI.h"

namespace Crimson {

	class Renderer2D
	{
	public:

		struct QuadProperties {

			float tilingFactor;
			float rotation;

			crm::vec4 textureTintColor;

			QuadProperties(float tilingFactor, float rotation, const crm::vec4& textureTintColor)
				: tilingFactor(tilingFactor), rotation(rotation), textureTintColor(textureTintColor)
			{
			}

		};


		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, const crm::vec4& color, QuadProperties& qp);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, const crm::vec4& color, QuadProperties& qp);
		static void DrawQuad(const crm::vec2& position, const crm::vec2& size, const Ref<Texture2D> texture, QuadProperties& qp);
		static void DrawQuad(const crm::vec3& position, const crm::vec2& size, const Ref<Texture2D> texture, QuadProperties& qp);

		static void DrawRotatedQuad(const crm::vec2& position, const crm::vec2& size, const crm::vec4& color, QuadProperties& qp);
		static void DrawRotatedQuad(const crm::vec3& position, const crm::vec2& size, const crm::vec4& color, QuadProperties& qp);
		static void DrawRotatedQuad(const crm::vec2& position, const crm::vec2& size, const Ref<Texture2D> texture, QuadProperties& qp);
		static void DrawRotatedQuad(const crm::vec3& position, const crm::vec2& size, const Ref<Texture2D> texture, QuadProperties& qp);


		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

	};

}