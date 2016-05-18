/*
************************************
* Copyright (C) 2016 ByteForge
* IModel.cpp
************************************
*/

#include "IModel.hpp"

using namespace anvil;

void IModel::AddInstance(std::shared_ptr<Instance> i) 
{ 
	m_instances.insert(i);
}

void IModel::RemoveInstance(std::shared_ptr<Instance> i) 
{
	m_instances.erase(i);
}
