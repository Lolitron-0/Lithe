#pragma once

namespace Lithe
{
    /// Static class for general purpose platform specific functions
    class Platform
    {
    public:
        static double GetTime() { return s_Instance->GetTimeImpl(); }

    protected:
        virtual double GetTimeImpl() =0;

        static Scope<Platform> s_Instance;

    };
}