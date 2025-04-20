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
    int useTexture = material->texture ? 1 : 0;
    material->shader->setInt("useTex", useTexture);
    if (useTexture)
    {
        material->texture->Render();
        material->shader->setInt("texture1", 0);
    }
    material->shader->setMat4("model", owner->transform.transMatrix);
    material->shader->setMat4("view", SceneCamera::VIEW_MAT);
    material->shader->setMat4("proj", SceneCamera::PROJ_MAT);
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);

    // Unbind VAO (optional)
    glBindVertexArray(0);
}