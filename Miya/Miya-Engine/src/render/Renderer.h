#pragma once
namespace Miya {
	class Renderer {
	public:
		virtual void Render(Timestep ts) {};
		virtual void Init() {};
		virtual void Destory() {};
		virtual void OnEvent(Event &e) {};
	};
}