#pragma once

#include "Crimson.h"
#include <filesystem>

using namespace Crimson;

class ContentBrowser
{
public:
	ContentBrowser();
	~ContentBrowser() = default;
	void OnImGuiRender();
private:
	Ref<Scene> m_scene;
	std::filesystem::path m_filePath;
};