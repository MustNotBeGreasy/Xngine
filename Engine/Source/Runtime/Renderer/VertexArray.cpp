#include "Xpch.h"
#include "Runtime/Renderer/VertexArray.h"

#include "Runtime/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace X
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (RendererAPI::Current())
        {
        case RendererAPI::RendererAPIType::None:    X_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::RendererAPIType::OpenGL:  return std::make_shared<OpenGLVertexArray>();
        }
        X_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}