#pragma once
#include "Crimson/Core/Core.h"
#include "Crimson/Core/UUID.h"

namespace Crimson {
	class Texture
	{
	public:
		uint64_t uuid;
		Texture() = default;
		virtual ~Texture() = default;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetID() const = 0;
		virtual void Bind(int slot) const = 0;
	};
	class Texture2D :public Texture {
	public:

		static bool ValidateTexture(const std::string& path);
		virtual void UnBind()const = 0;
		virtual unsigned short* GetTexture() = 0;
		virtual unsigned int GetChannels() = 0;
		static Ref<Texture2D> Create(const std::string& path, bool bUse16BitTexture = false);
		static Ref<Texture2D> Create(const unsigned int Width, const unsigned int Height, unsigned int);
	};
	class Texture2DArray : public Texture {
	public:
		virtual void UnBind() const = 0;
		//default number of materials =1 , number of channels = 3
		static Ref<Texture2DArray> Create(const std::vector<std::string>& paths, int numMaterials = 1, int numChannels = 3, bool bUse16BitTexture = false);
	};
}
