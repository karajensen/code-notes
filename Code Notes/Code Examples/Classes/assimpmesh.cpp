////////////////////////////////////////////////////////////////////////////////////////
// Kara Jensen - mail@karajensen.com - assimpmesh.cpp
////////////////////////////////////////////////////////////////////////////////////////

#include "assimpmesh.h"
#include "assimp/include/scene.h"
#include "assimp/include/Importer.hpp"
#include "assimp/include/postprocess.h"

Assimpmesh::Assimpmesh()
{
}

Assimpmesh::~Assimpmesh()
{
}

bool Assimpmesh::Initialise(const std::string& path, std::string& errorBuffer)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace|
        aiProcess_Triangulate|aiProcess_JoinIdenticalVertices|aiProcess_SortByPType|
        aiProcess_CalcTangentSpace|aiProcess_JoinIdenticalVertices|aiProcess_GenSmoothNormals|
        aiProcess_LimitBoneWeights|aiProcess_RemoveRedundantMaterials|aiProcess_OptimizeMeshes);

    if(!scene)
    {
        errorBuffer = "Assimp import error for mesh " + path + ": " + importer.GetErrorString();
        return false;
    }

    unsigned int numMeshes = scene->mNumMeshes;
    aiMesh** meshes = scene->mMeshes;

    // For each sub mesh
    for(unsigned int i = 0; i < numMeshes; ++i)
    {
        m_subMeshes.push_back(SubMesh());

        aiMesh* pMesh = meshes[i];
        unsigned int numVerts = pMesh->mNumVertices;
        unsigned int numFaces = pMesh->mNumFaces;

        // For each vertex
        for(unsigned int vert = 0; vert < numVerts; ++vert)
        {
            Vertex v;
            v.x = pMesh->mVertices[vert].x;
            v.y = pMesh->mVertices[vert].y;
            v.z = pMesh->mVertices[vert].z;

            v.nx = pMesh->mNormals[vert].x;
            v.ny = pMesh->mNormals[vert].y;
            v.nz = pMesh->mNormals[vert].z;

            v.u = pMesh->mTextureCoords[0][vert].x;
            v.v = pMesh->mTextureCoords[0][vert].y;

            m_subMeshes[i].vertices.push_back(v);
        }

        // For each face
        for(unsigned int face = 0; face < numFaces; ++face)
        {
            aiFace *pFace = &pMesh->mFaces[face];

            // Make sure that face is a triangle.
            if(pFace->mNumIndices != 3)
            {
                errorBuffer = "Assimp error for mesh " + path + ": not all faces are triangles";
                return false;
            }

            m_subMeshes[i].indices.push_back(pFace->mIndices[0]);
            m_subMeshes[i].indices.push_back(pFace->mIndices[1]);
            m_subMeshes[i].indices.push_back(pFace->mIndices[2]);
        }
    }

    return true;
}

Assimpmesh::Vertex::Vertex() : 
    x(0.0f),
    y(0.0f),
    z(0.0f),
    nx(0.0f),
    ny(0.0f),
    nz(0.0f),
    u(0.0f), 
    v(0.0f) 
{}