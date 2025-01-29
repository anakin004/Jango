#pragma once
#include "Crimson/Core/Core.h"
namespace Crimson {
		struct FrameBufferSpecification {
			unsigned int Width, Height;
			bool SwapChainTarget = false;
		};
	class FrameBuffer
	{
	public:
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
		virtual FrameBufferSpecification GetSpecification() = 0;
		virtual void Bind()=0;
		virtual void UnBind()=0;
		virtual unsigned int GetSceneTextureID() = 0;
		virtual unsigned int GetDepthTextureID() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void ClearFrameBuffer() = 0;
		virtual void BindFramebufferTexture(int slot) = 0;
		virtual void BindFramebufferDepthTexture(int slot) = 0;

	};
}
