#pragma once
#include "ComponentBase.hpp"

namespace Lithe
{

    class TagComponent : public ComponentBase
    {
        MAKE_COMPONENT(TagComponent)

    public:
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent& other) = default;
        TagComponent(const std::string& tag)
            :Tag(tag)
        {}

        void OnImGuiPropertiesDraw() override;
    };

}