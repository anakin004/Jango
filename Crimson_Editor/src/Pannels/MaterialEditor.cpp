#include "MaterialEditor.h"
#include "Crimson/Core/ResourceManager.h"
#include "Crimson/Scene/SceneSerializer.h"

using namespace Crimson;

uint64_t MaterialEditor::cached_materialID;
std::string MaterialEditor::cached_texturePath;

MaterialEditor::MaterialEditor()
{
    cached_materialID = 0;
	cached_texturePath = "";
}

static auto ShowTooltipOnHover = [](const std::string& text)
    {
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text.c_str());
        ImGui::EndTooltip();
    }
    };

void MaterialEditor::OnImGuiRender()
{
    // Early out if no material is selected
    Ref<Material>& materialRef = ResourceManager::allMaterials[cached_materialID];
    if (!materialRef) return;

    ImGui::Begin("Material Editor");

    // Display material name
    ImGui::Text("%s", materialRef->m_MaterialName.c_str());

    // Fetch current texture paths
    std::string albedoPath = materialRef->GetAlbedoPath();
    std::string normalPath = materialRef->GetNormalPath();
    std::string roughnessPath = materialRef->GetRoughnessPath();

    // Albedo texture slot
    ImGui::PushID(1);
    if (ImGui::Button(albedoPath.c_str(), { 120.0f, 60.0f })) {
        /* Optional: handle click */
    }
    ShowTooltipOnHover(albedoPath);
    if (ImGui::BeginDragDropTarget()) 
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Texture payload")) {
            albedoPath = *static_cast<const std::string*>(payload->Data);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::PopID();

    // Normal map slot
    ImGui::PushID(2);

    if (ImGui::Button(normalPath.c_str(), { 120.0f, 60.0f })) {}

    ShowTooltipOnHover(normalPath);
    if (ImGui::BeginDragDropTarget()) 
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Texture payload")) 
        {
            normalPath = *static_cast<const std::string*>(payload->Data);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::PopID();

    // Roughness map slot
    ImGui::PushID(3);
    if (ImGui::Button(roughnessPath.c_str(), { 120.0f, 60.0f })) {}
    ShowTooltipOnHover(roughnessPath);
    if (ImGui::BeginDragDropTarget()) 
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Texture payload")) 
        {
            roughnessPath = *static_cast<const std::string*>(payload->Data);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::PopID();

    // Apply any changed texture paths
    materialRef->SetTexturePaths(albedoPath, normalPath, roughnessPath);

    // Material attribute editors
    glm::vec4  baseColor = materialRef->GetColor();
    float      roughnessVal = materialRef->GetRoughness();
    float      metallicVal = materialRef->GetMetalness();
    float      normalStrength = materialRef->GetNormalStrength();

    ImGui::ColorEdit4("Color", glm::value_ptr(baseColor));
    ImGui::DragFloat("Roughness", &roughnessVal, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat("Metallic", &metallicVal, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat("Normal Strength", &normalStrength, 0.01f, 0.0f, 1.0f);

    materialRef->SetMaterialAttributes(baseColor, roughnessVal, metallicVal, normalStrength);

    // Save button
    if (ImGui::Button("Save Material")) {
        materialRef->SerializeMaterial("", materialRef->m_MaterialName);
    }

    ImGui::End();
}
