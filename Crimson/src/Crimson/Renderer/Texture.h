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
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
		virtual unsigned int GetID() = 0;
		virtual void Bind(int slot)const = 0;
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
		virtual void UnBind()const = 0;
		//default number of materials =1 , number of channels = 3
		static Ref<Texture2DArray> Create(const std::vector<std::string>& paths, int numMaterials = 1, int numChannels = 3, bool bUse16BitTexture = false);
	};
}

// #pragma once
// 
// #include "Crimson/Core/Core.h"
// #include <string>
// 
// namespace Crimson {
// 
// 	class Texture
// 	{
// 	public:
// 
// 		virtual ~Texture() = default;
// 
// 		virtual uint32_t GetWidth() const = 0;
// 		virtual uint32_t GetHeight() const = 0;
// 
// 		virtual void SetData(void* data, uint32_t size) const = 0;
// 
// 		virtual void Bind(uint32_t slot = 0) const = 0;
// 
// 		virtual bool operator==(const Texture& other) const = 0;
// 	};
// 
// 
// 	class Texture2D : public Texture
// 	{
// 	public:
// 		static Ref<Texture2D> Create(const std::string& path);
// 		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
// 
// 		
// 	};
// }