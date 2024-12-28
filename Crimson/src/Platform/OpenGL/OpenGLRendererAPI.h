#pragma once

#include "Crimson/Renderer/RendererAPI.h"

namespace Crimson {

	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Clear() override;
		virtual void SetClearColor(const crm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};

}