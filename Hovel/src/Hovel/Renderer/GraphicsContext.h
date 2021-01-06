#pragma once
namespace Hovel {
	
	class GraphicsContext
	{
	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}