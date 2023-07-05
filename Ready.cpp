#include "Ready.h"
#include "Engine/Image.h"
Ready::Ready(GameObject* parent)
{
}

Ready::~Ready()
{
}

void Ready::Initialize()
{
	hImage = Image::Load("ready.png");
}

void Ready::Update()
{
}

void Ready::Draw()
{
	Image::Draw(hImage);
}
