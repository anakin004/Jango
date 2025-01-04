#pragma once
#include "Crimson.h"

namespace Crimson
{
	class Fog
	{
	public:
		static Ref<Fog> Create(float density, float fogStart, float fogEnd,float fogTop, float fogBottom, glm::vec2 ScreenSize = { 1024,1024 });

		virtual void SetFogParameters(float density, float fogTop, float fogEnd, glm::vec3 fogColor) = 0;
		virtual void RenderFog(Camera& cam, glm::vec2 screenSize) = 0;
	};
}