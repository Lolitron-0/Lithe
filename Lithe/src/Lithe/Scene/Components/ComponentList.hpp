#pragma once

namespace Lithe
{
    class TagComponent;
    class TransformComponent;
    class MeshRendererComponent;
    class PointLightComponent;
    class CameraComponent;

    using ComponentsList = TypeList
    <
        TagComponent,
        TransformComponent,
        MeshRendererComponent,
        PointLightComponent,
        CameraComponent
    >;
}