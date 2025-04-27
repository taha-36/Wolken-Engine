#include "MeshRenderer.h"
#include "Entity.h"
#include "SceneCamera.h"
void MeshRenderer::Render()
{
    if (mesh == nullptr || material == nullptr || owner == nullptr)
        return;
    glBindVertexArray(mesh->VAO);
    drawSettings.useVertsColors = mesh->useVertsColors;
    material->shader->Activate();
    material->shader->setBool("useVertsColors", drawSettings.useVertsColors);
    material->shader->setUInt("id", this->owner->id);
    int useTexture = material->texture ? 1 : 0;
    material->shader->setInt("useTex", useTexture);
    if (useTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material->texture->texId);
        material->shader->setInt("texture1", 0);
    }
    material->shader->setMat4("model", owner->transform.transMatrix);
    material->shader->setMat4("view", SceneCamera::VIEW_MAT);
    material->shader->setMat4("proj", SceneCamera::PROJ_MAT);
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}