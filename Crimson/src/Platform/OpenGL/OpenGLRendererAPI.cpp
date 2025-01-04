#include "cnpch.h"
#include "OpenGlRendererAPI.h"
#include "glad/glad.h"

namespace Crimson {
	OpenGLRendererAPI::OpenGLRendererAPI()
	{
	}
	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}
	void OpenGLRendererAPI::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawIndex(VertexArray& vertexarray)
	{
		vertexarray.Bind();
		glDrawElements(GL_TRIANGLES, vertexarray.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (const void*)0);
	}
	void OpenGLRendererAPI::DrawArrays(VertexArray& vertexarray, size_t count, int first)
	{
		vertexarray.Bind();
		glDrawArrays(GL_TRIANGLES, first, count);
	}

	void OpenGLRendererAPI::DrawArrays(VertexArray& vertexarray, size_t count, unsigned int renderingMode, int first)
	{
		vertexarray.Bind();
		glDrawArrays(renderingMode, first, count);
	}

	void OpenGLRendererAPI::DrawInstancedArrays(VertexArray& vertexarray, size_t count, size_t instance_count, int first)
	{
		vertexarray.Bind();
		glDrawArraysInstanced(GL_TRIANGLES, first, count, instance_count);
		int size = sizeof(int) * 4;
	}
	void OpenGLRendererAPI::DrawArraysIndirect(VertexArray& vertexarray, uint32_t& indirectBufferID)
	{
		glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferID);
		vertexarray.Bind();
		glDrawArraysIndirect(GL_TRIANGLES, 0);
	}
	void OpenGLRendererAPI::DrawLine(VertexArray& vertexarray, uint32_t count)
	{
		vertexarray.Bind();
		glDrawArrays(GL_LINES, 0, count);
	}
	void OpenGLRendererAPI::Init()
	{
		int MaxTextureImageUnits;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureImageUnits);
		CN_CORE_INFO("Number of texture slots available are :- {}", MaxTextureImageUnits);

		//glEnable(GL_DEBUG_OUTPUT);
		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//glDebugMessageCallback(glDebugOutput, nullptr);
		//glEnable(GL_MULTISAMPLE);
		//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE_ARB);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glEnable(GL_STENCIL_TEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}
	void OpenGLRendererAPI::SetViewPort(unsigned int Width, unsigned int Height)
	{
		glViewport(0, 0, Width, Height);
	}
	glm::vec2 OpenGLRendererAPI::GetViewportSize()
	{
		float arr[4];
		glGetFloatv(GL_VIEWPORT, arr);
		return { arr[2],arr[3] };//the index 2 and 3 gives the width and height of the viewport
	}
}

// #include "cnpch.h"
// #include "OpenGLRendererAPI.h"
// 
// 
// #include <Glad/glad.h>
// 
// namespace Crimson {
// 
// 
// 	void OpenGLRendererAPI::Init()
// 	{
// 		glEnable(GL_BLEND);
// 		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 		glEnable(GL_DEPTH_TEST);
// 	}
// 
// 	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
// 	{
// 		glViewport(x, y, width, height);
// 	}
// 
// 	void OpenGLRendererAPI::Clear()
// 	{
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	}
// 
// 	void OpenGLRendererAPI::SetClearColor(const crm::vec4& color)
// 	{
// 		glClearColor(color.r, color.b, color.g, color.a);
// 	}
// 
// 	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
// 	{
// 
// 		uint32_t count = !indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
// 		vertexArray->Bind();
// 		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
// 	}
// 
// 	
// 
// }