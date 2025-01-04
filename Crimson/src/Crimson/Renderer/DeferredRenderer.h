#include "Crimson.h"

namespace Crimson
{
	class DefferedRenderer
	{
	public:
		static void Init(int width, int height);
		static void GenerateGBuffers(Scene*);
		static void DeferredRenderPass();
		static Ref<Shader> GetDeferredPassShader();
		static uint32_t GetBuffers(int bufferInd);
	};
}