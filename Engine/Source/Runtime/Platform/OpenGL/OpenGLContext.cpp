#include "Xpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace X
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        X_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        X_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        X_CORE_ASSERT(status, "Failed to initialize Glad!");

        X_CORE_INFO("OpenGL Info:");
        X_CORE_INFO("  Vendeor: {0}", glGetString(GL_VENDOR));
        X_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        X_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        X_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }
}