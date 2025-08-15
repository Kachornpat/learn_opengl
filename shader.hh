#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
    public:

        unsigned int ID;
        
        Shader(const char *vertexPath, const char *framentPath);
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, glm::vec3 value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif