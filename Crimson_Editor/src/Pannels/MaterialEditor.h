#pragma once
#include "Crimson.h"
#include "Crimson/Renderer/Material.h"

using namespace Crimson;
class MaterialEditor
{
public:
	static uint64_t cached_materialID;
	static std::string cached_texturePath;
public:
	MaterialEditor();
	~MaterialEditor() = default;
	void OnImGuiRender();
private:
	std::filesystem::path m_filePath;
};

