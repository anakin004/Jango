#pragma once
#include "Texture.h"
#include "glm/glm.hpp"

namespace Crimson {
	class SubTexture2D
	{
		public:
			glm::vec2 m_TextureCoordinate[4] = { {0,0} };
			Ref<Texture2D> Texture;
	public:
		SubTexture2D(Ref<Texture2D> texture, glm::vec2 max ,glm::vec2 min);
		static Ref<SubTexture2D> CreateFromCoordinate(Ref<Texture2D> texture, glm::vec2 ImageDimension, glm::vec2 coordinate, glm::vec2 SubImageDim, glm::vec2 ImageScale = {1,1});
	};
}