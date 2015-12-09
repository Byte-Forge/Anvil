#include "IRenderable.hpp"
#include "../Core.hpp"

using namespace hpse;

void IRenderable::Setup()
{
	//call method in Graphics insted??
	Core::GetGraphics()->GetRenderer()->Setup(*this);
}

void IRenderable::Render()
{
	//call method in Graphics insted??
	Core::GetGraphics()->GetRenderer()->Render(*this);
}

void IRenderable::Update()
{
	//call method in Graphics insted??
	Core::GetGraphics()->GetRenderer()->Update(*this);
}

void IRenderable::Delete()
{
	//call method in Graphics insted??
	Core::GetGraphics()->GetRenderer()->Delete(*this);
}