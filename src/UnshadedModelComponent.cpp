#include "unshaded_model_component.h"

UnshadedModelComponent::UnshadedModelComponent(std::string modelPath, std::string texturePath){
    shader.InitializeShader("unshaded_vertex.glsl", "unshaded_fragment.glsl");
    texture.InitializeFromFile(texturePath);
    model.LoadModel(modelPath);
    renderObject.IntializeRenderObject();

    renderObject.BufferData(VERTEX_BUFFER, GL_STATIC_DRAW, model.GetVertices()->data(), model.GetVertices()->size(), sizeof(f32));
    renderObject.BufferData(ELEMENT_BUFFER, GL_STATIC_DRAW, model.GetIndices()->data(), model.GetIndices()->size(), sizeof(u32));
    renderObject.AddAttribute(false, true, GL_FLOAT, 3, 8 * sizeof(float), 0);
    renderObject.AddAttribute(false, true, GL_FLOAT, 3, 8 * sizeof(float), 3 * sizeof(float));
    renderObject.AddAttribute(false, true, GL_FLOAT, 2, 8 * sizeof(float), 6 * sizeof(float));
}

UnshadedModelComponent::~UnshadedModelComponent(){
    model.DestroyModel();
    renderObject.DestroyRenderObject();
    texture.DestroyTexture();
    shader.DestroyShader();
}
    
void UnshadedModelComponent::Draw(glm::mat4 projectionView, glm::mat4 modelMatrix){
    shader.UseProgram();
    texture.ActivateTexture(0);
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(projectionView));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    renderObject.Draw(DRAW_ELEMENT, GL_TRIANGLES, model.GetIndices()->size(), 0);
}