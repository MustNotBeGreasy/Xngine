#pragma once
#include "Runtime/Camera/EditorCamera.h"
#include "Runtime/EcsFramework/Component/Mesh/StaticMeshComponent.h"
#include "Runtime/Renderer/Texture.h"

namespace X
{
    class Renderer3D
    {
    public:
        static void Init();
        static void Shutdown();

        static void DrawModel(const glm::mat4& transform, const glm::vec3& cameraPos, StaticMeshComponent& MeshComponent, int EntityID);

        static void BeginScene(const Camera& camera, const glm::mat4& transform);
        static void BeginScene(const EditorCamera& camera);
        static void EndScene();
    };
}