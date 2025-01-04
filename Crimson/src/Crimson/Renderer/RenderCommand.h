#pragma once

#include "RendererAPI.h"

#include <glm/glm.hpp>

namespace Crimson {

	class RenderCommand {
	public:
		inline static void Init() { s_RendererAPI->Init(); }

		static void SetViewport(unsigned int Width, unsigned int Height);

		inline static void ClearColor(const glm::vec4& color) {
			s_RendererAPI->ClearColor(color);
		}
		inline static void Clear() {
			s_RendererAPI->Clear();
		}
		inline static void DrawIndex(VertexArray& vertexarray) {
			s_RendererAPI->DrawIndex(vertexarray);
		}
		inline static void DrawArrays(VertexArray& vertexarray, size_t count, int first = 0)
		{
			s_RendererAPI->DrawArrays(vertexarray, count, first);
		}
		inline static void DrawArrays(VertexArray& vertexarray, size_t count, unsigned int renderingMode, int first = 0)
		{
			s_RendererAPI->DrawArrays(vertexarray, count, renderingMode, first);
		}
		inline static void DrawInstancedArrays(VertexArray& vertexarray, size_t count, size_t instance_count, int first = 0)
		{
			s_RendererAPI->DrawInstancedArrays(vertexarray, count, instance_count, first);
		}
		//indirectBufferID is bound to GL_DRAW_INDIRECT_BUFFER before the glDrawIndirect draw call to pass information to the gpu
		//this is used when the number of instances to draw is unknown in the cpu side but gpu produces the num instances to draw
		//so without copying the data from the gpu->cpu directly use gpu data to draw. 
		inline static void DrawArraysIndirect(VertexArray& vertexarray, uint32_t& indirectBufferID)
		{
			s_RendererAPI->DrawArraysIndirect(vertexarray, indirectBufferID);
		}
		inline static void DrawLine(VertexArray& vertexarray, uint32_t& count) {
			s_RendererAPI->DrawLine(vertexarray, count);
		}
		inline static glm::vec2 GetViewportSize()
		{
			return s_RendererAPI->GetViewportSize();
		}
	private:
		static Ref<RendererAPI> GetRendererAPI();
		static Scope<RendererAPI> s_RendererAPI;
	};

}