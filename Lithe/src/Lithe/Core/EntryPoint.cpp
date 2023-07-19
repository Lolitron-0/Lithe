#include "ltpch.h"
#include "Application.hpp"
#include <Profiler.hpp>
int main(int argc, char** argv)
{
    PROFILER_BEGIN_SESSION("Startup session", "ProfilingResult-Startup.json");
    Lithe::Application* app{ Lithe::CreateApplication() };
    PROFILER_END_SESSION();

    PROFILER_BEGIN_SESSION("Runtime session", "ProfilingResult-Runtime.json");
    app->Run();
    PROFILER_END_SESSION();

    PROFILER_BEGIN_SESSION("Shutdown session", "ProfilingResult-Shutdown.json");
    LITHE_CORE_LOG_TRACE("Shutting down...");
    delete app;
    LITHE_CORE_LOG_INFO("Exited successfully!");
    PROFILER_END_SESSION();
}

