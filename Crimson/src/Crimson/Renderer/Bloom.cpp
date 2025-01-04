#include "cnpch.h"
#include "Bloom.h"
#include "Platform/Opengl/OpenGlBloom.h"

namespace Crimson {
    Ref<Bloom> Bloom::Create()
    {
        switch (RendererAPI::GetAPI()) {
        case GraphicsAPI::OpenGL:
            return MakeRef<OpenGLBloom>();
        case GraphicsAPI::None:
            return nullptr;
        default:
            return nullptr;
        }
    }
}