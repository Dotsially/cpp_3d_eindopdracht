#include "model.h"
#include <fstream>
#include <streambuf>
#include <iostream>

Model::Model(){}
Model::~Model(){}


void Model::LoadModel(std::string fileName){
    using json = nlohmann::json;

    std::string filePath = "resources/models/" + fileName;
    std::ifstream gltfFile(filePath);
    jsonData = json::parse(gltfFile);
   
    //get .bin file with all the data. Needs to exist (for now)
    std::string uri = jsonData["buffers"][0]["uri"];
    std::string fileDirectory = filePath.substr(0, filePath.find_last_of('/') + 1);
    std::ifstream binaryFile(fileDirectory + uri, std::ios::binary);
    
    //read entire binary file into a string in one line because im lazy.
    std::string bytesString((std::istreambuf_iterator<char>(binaryFile)), std::istreambuf_iterator<char>());
    binaryData = std::vector<u8>(bytesString.begin(), bytesString.end());
    gltfFile.close();
    binaryFile.close();

    unsigned int positionIndex = jsonData["meshes"][0]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalIndex = jsonData["meshes"][0]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int uvIndex = jsonData["meshes"][0]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indicesIndex = jsonData["meshes"][0]["primitives"][0]["indices"];

    std::vector<float> positionData = GetVertexData(jsonData["accessors"][positionIndex]);
	std::vector<glm::vec3> positions = PackToVec3(positionData);
	std::vector<float> normalData = GetVertexData(jsonData["accessors"][normalIndex]);
	std::vector<glm::vec3> normals = PackToVec3(normalData);
	std::vector<float> uvData = GetVertexData(jsonData["accessors"][uvIndex]);
	std::vector<glm::vec2> UVs = PackToVec2(uvData);

    for(i32 i = 0; i < positions.size(); i++){
        vertices.push_back(positions[i].z);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].x);
        
        vertices.push_back(normals[i].z);
        vertices.push_back(normals[i].y);
        vertices.push_back(normals[i].x);
        
        vertices.push_back(UVs[i].x);
        vertices.push_back(UVs[i].y);
    }

    indices = GetIndexData(jsonData["accessors"][indicesIndex]);
}

void Model::DestroyModel(){


}

std::vector<f32> Model::GetVertexData(json accessor){
    std::vector<f32> data;
    //Model has multiple bufferViews for vertices, normals, uvs, etc. this is the index for accessor[0] which is vertices.
    u32 bufferViewIndex = accessor.value("bufferView", 0);

    //Get vertex data
    json bufferView = jsonData["bufferViews"][bufferViewIndex];
    u32 byteOffset = bufferView["byteOffset"];
    u32 bufferLength  = bufferView["byteLength"];

    //index of starting data is the buffer offset + byte offset in buffer
    for(i32 i = byteOffset; i < byteOffset + bufferLength; i){
        //One float value is 4 bytes 
        u8 bytes[] = {binaryData[i++], binaryData[i++], binaryData[i++], binaryData[i++]};
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        data.push_back(value);
    }

    return data;
}

std::vector<u32> Model::GetIndexData(json accessor){
    std::vector<u32> data;

    u32 bufferViewIndex = accessor.value("bufferView", 0);
    u32 componentType = accessor["componentType"];

    json bufferView = jsonData["bufferViews"][bufferViewIndex];
    u32 byteOffset = bufferView["byteOffset"];
    u32 bufferLength = bufferView["byteLength"];

    if(componentType == 5125){
        for(i32 i = byteOffset; i < byteOffset + bufferLength; i){
            //One int value is 4 bytes
            u8 bytes[] = {binaryData[i++], binaryData[i++], binaryData[i++], binaryData[i++]};
            u32 value;
            std::memcpy(&value, bytes, sizeof(u32));
            data.push_back(value);
        }
    }
    else if(componentType == 5123){
            for(i32 i = byteOffset; i < byteOffset + bufferLength; i){
                //One short value is 2 bytes
                u8 bytes[] = {binaryData[i++], binaryData[i++]};
                u16 value;
                std::memcpy(&value, bytes, sizeof(u16));
                data.push_back((u32)value);
            }
    }        

    return data;
}

std::vector<glm::vec3> Model::PackToVec3(std::vector<f32> floats){
    std::vector<glm::vec3> data;

    for (int i = 0; i < floats.size(); i){
        data.push_back(glm::vec3(floats[i++], floats[i++], floats[i++]));
    }

    return data;
}

std::vector<glm::vec2> Model::PackToVec2(std::vector<f32> floats){
    std::vector<glm::vec2> data;

    for (int i = 0; i < floats.size(); i){
        data.push_back(glm::vec2(floats[i++], floats[i++]));
    }

    return data;
}


std::vector<f32>* Model::GetVertices(){
    return &vertices;
}

std::vector<u32>* Model::GetIndices(){
    return &indices;
}