#pragma once
#include "Crimson.h"
#include "Crimson/Core.h"
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
		Ref<Shader> TAA_Shader;
		uint32_t m_CurrentColorBufferID, m_HistoryColorBufferID;
		uint32_t m_fbo, m_fbo_history;
		int m_width, m_height;
		int numFrame = 0;
	};
}