#include "ContentBrowser.h"
#include "Crimson/Scene/SceneSerializer.h"
#include "Crimson/Core/ResourceManager.h"
#include "MaterialEditor.h"

namespace fs = std::filesystem;
using namespace Crimson;

constexpr char* kAssetsDir = "Assets";

ContentBrowser::ContentBrowser()
    : m_filePath(kAssetsDir)
{}

void ContentBrowser::OnImGuiRender()
{
    ImGui::Begin("Content Browser");

    // Back button
    if (ImGui::Button("<-", { 20.0f, 20.0f }))
    {
        if (m_filePath.has_parent_path())
            m_filePath = m_filePath.parent_path();
    }

    // Directory entries
    for (const auto& entry : fs::directory_iterator(m_filePath))
    {
        const std::string fileName = entry.path().filename().string();
        const std::string fileExtension = entry.path().extension().string();

        if (entry.is_directory())
        {
            if (ImGui::Button(fileName.c_str()))
                m_filePath /= entry.path().filename();
        }
        else
        {
            // Material files (.mat)
            if (fileExtension == ".mat")
            {
                SceneSerializer serializer;
                uint64_t materialID = serializer.DeSerializeAndGetMaterialID(entry.path().string());

                if (ImGui::Button(fileName.c_str()))
                    MaterialEditor::cached_materialID = materialID;

                if (ImGui::BeginDragDropSource())
                {
                    ImGui::SetDragDropPayload(
                        "Material payload",
                        &ResourceManager::allMaterials[materialID],
                        sizeof(Material)
                    );
                    ImGui::Text("%s", fileName.c_str());
                    ImGui::EndDragDropSource();
                }
            }

            // Texture files (.png, .hdr, .jpg)
            if (fileExtension == ".png" ||
                fileExtension == ".hdr" ||
                fileExtension == ".jpg")
            {
                if (ImGui::Button(fileName.c_str()))
                {
                    // Could handle click if needed
                }

                if (ImGui::BeginDragDropSource())
                {
                    MaterialEditor::cached_texturePath = entry.path().string();
                    const auto& pathStr = MaterialEditor::cached_texturePath;
                    ImGui::SetDragDropPayload(
                        "Texture payload",
                        pathStr.c_str(),
                        pathStr.size() + 1
                    );
                    ImGui::Text("%s", fileName.c_str());
                    ImGui::EndDragDropSource();
                }
            }

            // Accept dropped items
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Material payload"))
                {
                    std::string droppedPath = *static_cast<const std::string*>(payload->Data);
                    // handle droppedPath if needed
                    (void)droppedPath;
                }
                ImGui::EndDragDropTarget();
            }

            ImGui::Text("%s", fileName.c_str());
        }
    }

    ImGui::End();
}
