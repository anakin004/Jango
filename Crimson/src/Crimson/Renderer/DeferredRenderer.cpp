#include "cnpch.h"
#include "Platform/Opengl/OpenGlDeferredRenderer.h"
#include "DeferredRenderer.h"

namespace Crimson
{
	void DefferedRenderer::Init(int width, int height)
	{
		OpenGLDeferredRenderer::Init(width,height);
	}
	void DefferedRenderer::GenerateGBuffers(Scene* scene)
	{
		OpenGLDeferredRenderer::CreateBuffers(scene);
	}
	void DefferedRenderer::DeferredRenderPass()
	{
		OpenGLDeferredRenderer::DeferredPass();
	}
	Ref<Shader> DefferedRenderer::GetDeferredPassShader()
	{
		return OpenGLDeferredRenderer::GetDeferredShader();
	}
	uint32_t DefferedRenderer::GetBuffers(int bufferInd)
	{
		return OpenGLDeferredRenderer::GetBuffers(bufferInd);
	}
}