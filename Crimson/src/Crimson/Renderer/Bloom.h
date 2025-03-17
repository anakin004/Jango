#pragma once
#include "Crimson.h"

namespace Crimson
{
	struct TextureMip {
		glm::vec2 dimension;
		unsigned int texture;

		TextureMip::TextureMip()
			: dimension(0.0f, 0.0f), texture(0)
		{
		}

	};

	class Bloom {
	public:
		Bloom() = default;
		virtual ~Bloom() = default;

		virtual void InitBloom() = 0;
		virtual void Update(TimeStep ts)= 0;
		virtual void GetFinalImage(const unsigned int& img, const glm::vec2& dimension) = 0;
		virtual void RenderBloomTexture() = 0;

		static Ref<Bloom> Create();
		static int NUMBER_OF_MIPS;
		static int FILTER_RADIUS;
		static float m_Exposure;
		static float m_BloomAmount;
		static float m_BrightnessThreshold;
	protected:
		virtual void DownSample()= 0;
		virtual void UpSample()= 0;

	protected:
		std::vector<TextureMip> m_MipLevels;
	};
}