#pragma once
#include "render/Renderer.h"
namespace MiyaApp {

	class InitImp : public Miya::Renderer {
	public:
		virtual void Render();
		virtual void Init();
		virtual void Destory();
	private:

	};
}