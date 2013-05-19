/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com)
* Assimp mesh wrapper that is renderer API independent
*****************************************************************/
#pragma once

#include <vector>
#include <string>

class Assimpmesh
{
public:

    /**
    * Vertex structure
    */
    struct Vertex
    {
        float x,y,z;     ///< Vertex position
        float nx,ny,nz;  ///< Vertex normal
        float u,v;       ///< Vertex uvs
        Vertex();
    };

    /**
    * Texture index ordering for 
    * the submeshes textures container
    */
    enum TextureIndex
    {
        DIFFUSE,
        NORMAL,
        SPECULAR,
        ENVIRON,
        TEXTURE_AMOUNT
    };

    /**
    * SubMesh struct
    */
    struct SubMesh
    {
        std::vector<Vertex> vertices;          ///< Vertex buffer
        std::vector<unsigned long> indices;    ///< Index buffer
        std::string textures[TEXTURE_AMOUNT];  ///< Textures for submesh
    };

    /**
    * Constructor
    */
    Assimpmesh();

    /**
    * Destructor
    */
    ~Assimpmesh();

    /**
    * Initialises the mesh
    * @param the path of the mesh
    * @param the error buffer to fill if something fails
    * @return whether or not initialisation succeeded
    */
    bool Initialise(const std::string& path, std::string& errorBuffer);

    /**
    * @return the submeshes for this mesh
    */
    const std::vector<SubMesh>& GetMeshes() const { return m_subMeshes; }

private:

    /**
    * Not implemented
    */
    Assimpmesh(const Assimpmesh&);              
    Assimpmesh& operator=(const Assimpmesh&);

    std::vector<SubMesh> m_subMeshes;  ///< sub meshes for this mesh

};