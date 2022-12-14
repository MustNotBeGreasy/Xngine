#include "Xpch.h"

#include "Runtime/EcsFramework/System/Script/PythonScriptSystem.h"
#include "Runtime/EcsFramework/Component/ComponentGroup.h"
#include "Runtime/EcsFramework/Entity/Entity.h"

#include <pybind11/embed.h>
#include <glm/glm.hpp>

namespace py = pybind11;

namespace X
{
    PYBIND11_EMBEDDED_MODULE(X, m)
    {
        py::class_<Timestep>(m, "Timestep")
            .def(py::init<float>())
            .def("GetSeconds", &Timestep::GetSeconds);

        py::class_<glm::vec3>(m, "vec3")
            .def(py::init<float, float, float>())
            .def_readwrite("x", &glm::vec3::x)
            .def_readwrite("y", &glm::vec3::y)
            .def_readwrite("z", &glm::vec3::z);

        py::class_<TransformComponent>(m, "Transform")
            .def(py::init<glm::vec3, glm::vec3, glm::vec3>())
            .def("GetTransform", &TransformComponent::GetTransform)
            .def("GetTranslation", &TransformComponent::GetTranslation)
            .def("SetTranslation", &TransformComponent::SetTranslation);
    }

    PythonScriptSystem::PythonScriptSystem(Level* level)
        :System(level)
    {
        if (std::getenv("PYTHONPATH") && std::getenv("PYTHONHOME"))
        {
            bLoadPython = true;
        }
    }
    void PythonScriptSystem::OnUpdateRuntime(Timestep ts)
    {
        if (!bLoadPython)
            return;
        auto view = mLevel->mRegistry.view<TransformComponent, PythonScriptComponent>();
        for (auto e : view)
        {
            Entity entity = { e, mLevel };
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& script = entity.GetComponent<PythonScriptComponent>();

            if (script.Path.empty())
                return;

            std::string pyScript = std::string("Scripts.") + script.Path.substr(0, script.Path.find_last_of("."));

            try
            {
                auto testModule = py::module::import(pyScript.c_str());
                auto func = testModule.attr("OnUpdateRuntime");
                TransformComponent reTrans = func(transform, ts).cast<TransformComponent>();
                transform.Translation = reTrans.Translation;
            }
            catch (py::error_already_set& e)
            {
                X_CORE_INFO(e.what());
            }
        }
    }

    void PythonScriptSystem::OnUpdateEditor(Timestep ts, EditorCamera& camera)
    {
        if (!bLoadPython)
            return;


        auto view = mLevel->mRegistry.view<TransformComponent, PythonScriptComponent>();
        for (auto e : view)
        {
            Entity entity = { e, mLevel };
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& script = entity.GetComponent<PythonScriptComponent>();

            if (script.Path.empty())
                return;

            if (!script.UseScript)
                return;

            std::string pyScript = std::string("Scripts.") + script.Path.substr(0, script.Path.find_last_of("."));

            try
            {
                auto testModule = py::module::import(pyScript.c_str());
                auto func = testModule.attr("OnUpdateEditor");
                TransformComponent reTrans = func(transform).cast<TransformComponent>();
                transform.Translation = reTrans.Translation;
            }
            catch (py::error_already_set& e)
            {
                X_CORE_INFO(e.what());
            }
        }
    }
}