#include "IRenderable.hpp"
#include "../Core.hpp"

using namespace hpse;

void IRenderable::Setup()
{
	Core::GetGraphics()->Setup(*this);
}

void IRenderable::Render()
{
	Core::GetGraphics()->Render(*this);
}

void IRenderable::Update()
{
	Core::GetGraphics()->Update(*this);
}

void IRenderable::Delete()
{
	Core::GetGraphics()->Delete(*this);
}