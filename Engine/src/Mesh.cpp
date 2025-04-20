#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies, std::vector<float> vertsColors)
{
    VAO = 0;
    colorsVBO = 0;
    posesVBO = 0;
    uvVBO = 0;
    EBO = 0;

    this->vertsPoses = vertsPoses;
    this->vertsColors = vertsColors;
    this->indices = indicies;

    vertCount = vertsPoses.size();
    indexCount = indices.size();

    ActivateMesh();
}
Mesh::Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies)
{
    VAO = 0;
    colorsVBO = 0;
    posesVBO = 0;
    EBO = 0;

    this->vertsPoses = vertsPoses;
    this->vertsColors = vertsColors;
    this->indices = indicies;

    vertCount = vertsPoses.size();
    indexCount = indices.size();

    ActivateMeshColorless();
}
Mesh::~Mesh() {
    // Delete the VAO, VBO, and EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &posesVBO);
    glDeleteBuffers(1, &colorsVBO);
    glDeleteBuffers(1, &EBO);
}
void Mesh::ActivateMeshColorless()
{
    useVertsColors = false;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &posesVBO);
    glGenBuffers(1, &colorsVBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind and set up the position VBO
    glBindBuffer(GL_ARRAY_BUFFER, posesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(float), vertsPoses.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Bind and set up the EBO (Element Buffer Object)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}
void Mesh::ActivateMesh()
{
    useVertsColors = true;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &posesVBO);
    glGenBuffers(1, &colorsVBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind and set up the position VBO
    glBindBuffer(GL_ARRAY_BUFFER, posesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(float), vertsPoses.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind and set the colour VBO
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(float), vertsColors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);


    // Bind and set up the EBO (Element Buffer Object)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

}
void Mesh::SetUV(std::vector<float> uv)
{
    //Bind to the VAO of th current mesh
    glBindVertexArray(VAO);

    //Generate the buffer
    glGenBuffers(1, &uvVBO);

    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(float), uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(2);
}