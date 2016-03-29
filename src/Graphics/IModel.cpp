/*
************************************
* Copyright (C) 2016 ByteForge
* IModel.cpp
************************************
*/

#include "IModel.hpp"

using namespace anvil;

void IModel::AddEntity(Entity* entity) 
{ 
	m_entities.insert(entity);
}

void IModel::RemoveEntity(Entity* entity) 
{
	m_entities.erase(entity);
}