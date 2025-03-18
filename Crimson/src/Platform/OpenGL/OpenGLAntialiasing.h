#pragma once
#include "Crimson.h"
#include "Crimson/Core/Core.h"
#include "Crimson/Renderer/Antialiasing.h"

namespace Crimson
{
	class OpenGLAntialiasing:public Antialiasing
	{
	public:
		OpenGLAntialiasing(int width, int height);
		~OpenGLAntialiasing();
		void Init(int width, int height);
		void Update() override;
		void RenderQuad();
	private:
		Ref<Shader> m_TAA_shader;
		uint32_t m_current_color_buffer_ID, m_history_color_buffer_ID;
		uint32_t m_fbo, m_fbo_history;
		int m_Width, m_Height;
		int m_num_frame = 0;
	};
}