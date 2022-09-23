#pragma once 
#include "MiyaEngine.h"
#include "AppLayer.h"

namespace MiyaApp {
	class App : public Miya::Application
	{
	public:
		App();
		void Init();
		inline static AppLayer* GetAppLayer() { return m_nlayer; }
		inline static void SetAppLayer(AppLayer* applayer) { m_nlayer = applayer; }
	private:
		static AppLayer* m_nlayer;
	};
}