#include <Lithe.hpp>
#include <Lithe/Core/EntryPoint.hpp>
#include "EditorLayer.hpp"

namespace Lithe
{

    class LitheEditor : public Lithe::Application
    {
    public:
        LitheEditor()
        {
            Ref<EditorLayer> myLayer{std::make_shared<EditorLayer>()};
            this->PushLayer(std::make_shared<EditorLayer>());
        }

        ~LitheEditor()
        {

        }
    };

    Application* CreateApplication()
    {
        return new LitheEditor();
    }

}