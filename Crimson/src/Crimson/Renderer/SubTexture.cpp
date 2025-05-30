#include "cnpch.h"
#include "SubTexture.h"

namespace Crimson {
	SubTexture2D::SubTexture2D(Ref<Texture2D> texture, glm::vec2 max, glm::vec2 min)
		:Texture(texture)
	{
		m_TextureCoordinate[0] = { min.x,min.y };
		m_TextureCoordinate[1] = { min.x,max.y };
		m_TextureCoordinate[2] = { max.x,max.y };
		m_TextureCoordinate[3] = { max.x,min.y };
		
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoordinate(Ref<Texture2D> texture, glm::vec2 ImageDimension, glm::vec2 coordinate, glm::vec2 SubImageDim , glm::vec2 ImageScale)
	{
		glm::vec2 min = { (coordinate.x * SubImageDim.x) / ImageDimension.x,(coordinate.y * SubImageDim.y) / ImageDimension.y };
		glm::vec2 max = { ((coordinate.x + ImageScale.x) * SubImageDim.x) / ImageDimension.x,((coordinate.y + ImageScale.y) * SubImageDim.y) / ImageDimension.y };
		
		Ref<SubTexture2D> subTex = MakeRef<SubTexture2D>(texture, max, min);
		return subTex;
	}
}