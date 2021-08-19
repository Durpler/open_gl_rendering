//
// Created by Durpler on 12/08/2021.
//

#ifndef OGLE_SHADERMANAGER_H
#define OGLE_SHADERMANAGER_H

namespace ogle
{
    typedef enum eShaderTypes
    {
        SHADER_TYPE_BASE,
        SHADER_TYPE_MAX,
    } SHADER_TYPE;
    class ShaderManager
    {
    public:
        ShaderManager();
        ~ShaderManager();

    bool compileShaders();

    private:
        std::map<SHADER_TYPE, GLuint /*sID*/> m_Shaders;

    };
}

#endif //OGLE_SHADERMANAGER_H
