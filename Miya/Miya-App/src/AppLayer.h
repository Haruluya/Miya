#pragma once

#include "MiyaEngine.h"

class AppLayer : public Miya::Layer
{
public:
	AppLayer();
	virtual ~AppLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Miya::Event& event) override;
	virtual void OnUpdate(Miya::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
};