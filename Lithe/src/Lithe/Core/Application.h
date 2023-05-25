#pragma once
#include "Base.hpp"

namespace Lithe 
{

	class LITHE_API Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Defined in client
	Application* CreateApplication();
}
