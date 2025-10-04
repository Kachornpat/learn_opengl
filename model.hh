#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "shader.hh"
#include "mesh.hh"

using namespace std;

class Model
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader &shader);
        unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
    private:

        vector<Mesh> meshes;
        vector<Texture> textures_loaded;
        string directory;
        
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};
#endif