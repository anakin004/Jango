#pragma once

#include "Crimson/Renderer/Bloom.h"

namespace Crimson {
	class OpenGLBloom : public Bloom {
	public:
		OpenGLBloom();
		~OpenGLBloom();

		void InitBloom() override;
		void Update(TimeStep ts) override;
		void GetFinalImage(const unsigned int& img, const glm::vec2& dimension) override { m_Dimension = dimension; }
		void RenderBloomTexture() override { DownSample(); UpSample(); };

	protected:
		void DownSample() override;
		void UpSample() override;

	private:
		void RenderQuad();
		void RenderRotatedQuad();

		void ExtractImageBrightParts();
	private:
		unsigned int m_FBO;
		unsigned int m_InputImage,m_BrightImage;

		glm::vec2 m_Dimension = {0,0}, m_ScreenDimension;//note Screen dimension will not change as it is the dimension with which every thing is being rendered
		Ref<Shader> m_DownSampleShader;
		Ref<Shader> m_UpSampleShader,BloomToneMapShader,ExtractBrightParts;
	};
}