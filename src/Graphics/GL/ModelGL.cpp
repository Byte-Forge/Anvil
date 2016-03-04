/*
************************************
* Copyright (C) 2016 ByteForge
* ModelGL.cpp
************************************
*/

#include "ModelGL.hpp"
#include "MeshGL.hpp"
#include <iostream>

using namespace anvil;

GL::ModelGL::ModelGL()
{

}

GL::ModelGL::~ModelGL()
{

}

void GL::ModelGL::Render(IShader& shader)
{

}

void GL::ModelGL::Update()
{
	for (std::shared_ptr<IMesh> mesh : m_meshes)
	{
		mesh->Update(); 
	}
}