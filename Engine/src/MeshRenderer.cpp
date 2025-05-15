#include "MeshRenderer.h"
MeshRenderer::MeshRenderer()
{
    VAO = 0;
    posesVBO = 0;
    colorsVBO = 0;
    uvVBO = 0;
    EBO = 0;
}
MeshRenderer::~MeshRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &posesVBO);
    glDeleteBuffers(1, &colorsVBO);
    glDeleteBuffers(1, &EBO);
}
void MeshRenderer::Render()
{
    glBindVertexArray(VAO);
    drawSettings.useVertsColors = mesh->useVertsColors;
    material->shader->Activate();
    material->shader->setBool("useVertsColors", drawSettings.useVertsColors);
    material->shader->setUInt("id", this->owner->id);
    int useTexture = material->texture ? 1 : 0;
    material->shader->setInt("useTex", useTexture);
    material->shader->setVec3("mainColor", material->mainColor);
    if (useTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material->texture->texId);
        material->shader->setInt("texture1", 0);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, owner->transform.worldPosition);
    model = glm::rotate(model, glm::radians(owner->transform.eulerAngles.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(owner->transform.eulerAngles.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(owner->transform.eulerAngles.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, owner->transform.worldScale);

    material->shader->setMat4("model", model);
    material->shader->setMat4("view", SceneCamera::Instance().VIEW_MAT);
    material->shader->setMat4("proj", SceneCamera::Instance().PROJ_MAT);
    int isSelected = 0;
    if (Globals::Instance().selectedEnt != nullptr)
    {
        if (owner->id == Globals::Instance().selectedEnt->id)
        {
            isSelected = 1;
        }
        else
        {
            isSelected = 0;
        }
    }
    material->shader->setInt("isSelected", isSelected);

    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
void MeshRenderer::BindMesh(Mesh* ptr)
{
    this->mesh = ptr;
    if (this->mesh->useVertsColors)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &posesVBO);
        glGenBuffers(1, &colorsVBO);
        glGenBuffers(1, &EBO);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Bind and set up the position VBO
        glBindBuffer(GL_ARRAY_BUFFER, posesVBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertCount * sizeof(float), mesh->vertsPoses.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Bind and set the colour VBO
        glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertCount * sizeof(float), mesh->vertsColors.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);


        // Bind and set up the EBO (Element Buffer Object)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);
    }
    else
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &posesVBO);
        glGenBuffers(1, &colorsVBO);
        glGenBuffers(1, &EBO);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Bind and set up the position VBO
        glBindBuffer(GL_ARRAY_BUFFER, posesVBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertCount * sizeof(float), mesh->vertsPoses.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        // Bind and set up the EBO (Element Buffer Object)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);
    }
    RecalculateUV();
}
void MeshRenderer::RecalculateUV()
{
    //Bind to the VAO of th current mesh
    glBindVertexArray(VAO);

    //Generate the buffer
    glGenBuffers(1, &uvVBO);

    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->uv.size() * sizeof(float), mesh->uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(2);
}
void MeshRenderer::Serialize()
{
    if (ImGui::CollapsingHeader("MeshRenderer"))
    {
        ImGui::BeginChild("Material", ImVec2(0, 100), true);

        ImGui::Text("Material");
        ImGui::SameLine();


        if (ImGui::Selectable(material->name.c_str(), false))
        {
            ImGui::OpenPopup("MaterialsPopUp");
        }

        if (ImGui::BeginPopup("MaterialsPopUp"))
        {
            for (const auto& pair : AssetsHandler::Instance().MATERIALS)
            {
                Material* mat = pair.second;
                if (ImGui::MenuItem(mat->name.c_str()))
                {
                    if (Globals::Instance().selectedEnt->GetComponent<MeshRenderer>() != nullptr)
                    {
                        Globals::Instance().selectedEnt->GetComponent<MeshRenderer>()->material = mat;
                    }
                }
            }
            ImGui::EndPopup();
        }
        ImGui::EndChild();
    }
}