#include"Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
Texture::Texture(const char* texturePath)
{
    path = texturePath;

    //textures
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // load image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, &width, &height, &nChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}
nlohmann::json Texture::Serialize() const
{
    nlohmann::json j = {
        "path", path
    };

    std::string path = "assets/texture.json";
    std::filesystem::path filePath(path);
    std::filesystem::path dirPath = filePath.parent_path();


    // Ensure the directory exists
    if (!std::filesystem::exists(dirPath))
    {
        std::filesystem::create_directories(dirPath);
    }

    std::ofstream file(path);
    if (file.is_open())
    {
        file << j.dump(4);
        file.close();
    }
    else
    {
        std::cerr << "Failed to open file" << "\n";
    }
    return j;
}