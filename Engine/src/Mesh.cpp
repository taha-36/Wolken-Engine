#include "../Headers/Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Mesh::Mesh(std::vector<float> vertsPoses, std::vector<unsigned int> indicies, std::vector<float> vertsColors)
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




    //textures coordinates
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

    //textures

    //glGenTextures(1, &texture1);
    //glBindTexture(GL_TEXTURE_2D, texture1);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //// load image
    //int width, height, nChannels;
    //stbi_set_flip_vertically_on_load(true);
    //unsigned char* data = stbi_load("assets/tex.jpg", &width, &height, &nChannels, 0);

    //if (data)
    //{
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else
    //{
    //    std::cout << "Failed to load texture" << std::endl;
    //}

}

void Mesh::Render() {
    // Activate the VAO
    glBindVertexArray(VAO);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture1);

    material->shader->Activate();
    material->shader->setBool("useVertsColors", useVertsColors);
    //shader.setInt("texture1", 0);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    // Unbind VAO (optional)
    glBindVertexArray(0);
}