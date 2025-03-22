#pragma once

#include "Crimson/Core/Core.h"
#include <glm/glm.hpp>

namespace Crimson {
	

		struct FrameBufferSpecification {
			glm::uvec2 viewport;
			bool SwapChainTarget = false;

			FrameBufferSpecification() = default;
			FrameBufferSpecification(unsigned int width, unsigned int height)
				: viewport(width, height)
			{
			}
		};
	class FrameBuffer
	{
	public:
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
		inline virtual const FrameBufferSpecification& GetSpecification() = 0;
		virtual void Bind()=0;
		virtual void UnBind()=0;
		inline virtual unsigned int GetSceneTextureID() = 0;
		inline virtual unsigned int GetDepthTextureID() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void ClearFrameBuffer() = 0;
		virtual void BindFramebufferTexture(int slot) = 0;
		virtual void BindFramebufferDepthTexture(int slot) = 0;

	};
}
