#include "Xpch.h"

#include "Runtime/Renderer/IndexBuffer.h"
#include "Runtime/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace X
{
    Ref<IndexBuffer> IndexBuffer::Create(uint32_t count)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPI::RendererAPIType::None:    return nullptr;
        case RendererAPI::RendererAPIType::OpenGL:  return CreateRef<OpenGLIndexBuffer>(count);
        }
        X_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPI::RendererAPIType::None:    return nullptr;
        case RendererAPI::RendererAPIType::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, count);
        }
        X_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}