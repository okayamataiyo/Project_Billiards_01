#pragma once
#include "Engine/GameObject.h"

class Ready : public GameObject
{
public:
	Ready(GameObject* parent);
	~ Ready();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	int hImage;
};

