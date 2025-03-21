#pragma once


#include "Crimson/Renderer/Water.h"


namespace Crimson {


	/*
	
		For OpenGL impl for water, I will optionally have a refraction and reflection, or a low-res version
		for a efficency and or style choice for user
		
		for reflection and refraction there will need to be two fbos

			reflection -> we will place our camera at 2 * cur distance above water down, invert camera rotation, and sample the fbo texture
						  that is above the water, we will also create a clip space using a plane equation for more efficient sampling

			refraction -> keep camera where it is and sample the scene from below the plane ( below the top of the water ) and sample that to the other fbo
						  
		with these two fbos we can sample the textures and give us a resulting texture to put on the water quad

		these fbo visualizations will be availing in imgui menu when one is created, im currently deciding wether or not water will just encomas
		the whole terrain with some height level meaning water will be visible below that line
	*/

	class OpenGLWater : public Water
	{

	public:
		OpenGLWater(const glm::vec3& dims, const glm::vec3& water_color, const glm::vec2& screen_size);
		~OpenGLWater();

		virtual void SetWaterParameters(const glm::vec3& dims, const glm::vec3& water_color) override;
		virtual void RenderWater(Camera& cam, const glm::vec2& screen_size) override;

	private:




	};



}