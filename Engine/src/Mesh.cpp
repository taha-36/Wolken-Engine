#include "Mesh.h"
Mesh::Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies, std::vector<float> vertsColors)
{
    this->vertsPoses = vertsPoses;
    this->vertsColors = vertsColors;
    this->indices = indicies;

    vertCount = vertsPoses.size();
    indexCount = indices.size();

    useVertsColors = true;
}
Mesh::Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies)
{
    this->vertsPoses = vertsPoses;
    this->vertsColors = vertsColors;
    this->indices = indicies;

    vertCount = vertsPoses.size();
    indexCount = indices.size();

    useVertsColors = false;
}