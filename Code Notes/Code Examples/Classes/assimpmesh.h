////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - assimpmesh.h
////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include <string>

/**
* Assimp mesh wrapper that is renderer API independent
*/
class Assimpmesh
{
public:

    /**
    * Vertex structure
    */
    struct Vertex
    {
        /**
        * Contructor
        */
        Vertex();

        float x,y,z;     ///< Vertex position
        float nx,ny,nz;  ///< Vertex normal
        float u,v;       ///< Vertex uvs
    };

    /**
    * SubMesh struct
    */
    struct SubMesh
    {
        std::vector<Vertex> vertices;          ///< Vertex buffer
        std::vector<unsigned long> indices;    ///< Index buffer
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
    * @param path The path of the mesh
    * @param errorBuffer The error buffer to fill if something fails
    * @return whether or not initialisation succeeded
    */
    bool Initialise(const std::string& path, std::string& errorBuffer);

    /**
    * @return the submeshes for this mesh
    */
    const std::vector<SubMesh>& GetMeshes() const { return m_subMeshes; }

private:

    /**
    * Prevent copying
    */
    Assimpmesh(const Assimpmesh&);              
    Assimpmesh& operator=(const Assimpmesh&);

    std::vector<SubMesh> m_subMeshes;  ///< sub meshes for this mesh

};