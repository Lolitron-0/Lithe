#pragma once

namespace Lithe
{
    class TagComponent;
    class TransformComponent;
    class MeshRendererComponent;
    class SkyboxComponent;
    class PointLightComponent;
    class DirLightComponent;
    class CameraComponent;

    using ComponentsList = TypeList
    <
        TagComponent,
        TransformComponent,
        MeshRendererComponent,
        SkyboxComponent,
        PointLightComponent,
        DirLightComponent,
        CameraComponent
    >;
}