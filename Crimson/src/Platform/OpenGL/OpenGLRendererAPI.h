#pragma once

#include "Crimson/Renderer/RendererAPI.h"

namespace Crimson {

	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Clear() override;
		virtual void SetClearColor(const crm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}