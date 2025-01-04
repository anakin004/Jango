#include "Crimson.h"

namespace Crimson
{
	class OpenGLDeferredRenderer
	{
	public:
		static void Init(int width, int height);
		static void CreateBuffers(Scene* scene);
		static void DeferredPass();
		static Ref<Shader> GetDeferredShader() { return m_DefferedPassShader; }
		static uint32_t GetBuffers(int bufferInd);

	private:
		static uint32_t m_framebufferID, m_RenderBufferID, m_AlbedoBufferID,
			m_NormalBufferID , m_RoughnessMetallicBufferID, m_VelocityBufferID;
		static Ref<Shader> m_ForwardPassShader;
		static Ref<Shader> m_DefferedPassShader;
	};
}