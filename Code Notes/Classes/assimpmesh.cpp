#include "assimpmesh.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

Assimpmesh::Assimpmesh()
{
}

Assimpmesh::~Assimpmesh()
{
}

bool Assimpmesh::Initialise(const std::string& path, std::string& errorBuffer)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace|aiProcess_Triangulate|
                                             aiProcess_JoinIdenticalVertices|aiProcess_SortByPType|
                                             aiProcess_CalcTangentSpace|aiProcess_JoinIdenticalVertices|
                                             aiProcess_GenSmoothNormals|aiProcess_LimitBoneWeights|
                                             aiProcess_RemoveRedundantMaterials|aiProcess_OptimizeMeshes);
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

        // Load the textures
        aiMaterial* material = scene->mMaterials[pMesh->mMaterialIndex];
        
        aiString textureName;
        if(aiGetMaterialString(material, AI_MATKEY_TEXTURE_DIFFUSE(0), &textureName) == AI_SUCCESS)
        {
            m_subMeshes[i].textures[DIFFUSE] = textureName.data;
        }

        textureName.Clear();
        if(aiGetMaterialString(material, AI_MATKEY_TEXTURE_NORMALS(0), &textureName) == AI_SUCCESS)
        {
            m_subMeshes[i].textures[NORMAL] = textureName.data;
        }

        textureName.Clear();
        if(aiGetMaterialString(material, AI_MATKEY_TEXTURE_SPECULAR(0), &textureName) == AI_SUCCESS)
        {
            m_subMeshes[i].textures[SPECULAR] = textureName.data;
        }

        textureName.Clear();
        if(aiGetMaterialString(material, AI_MATKEY_TEXTURE_REFLECTION(0), &textureName) == AI_SUCCESS)
        {
            m_subMeshes[i].textures[ENVIRON] = textureName.data;
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