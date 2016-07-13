/*
************************************
* Copyright (C) 2016 ByteForge
* IRenderer.cpp
************************************
*/

#include "IRenderer.hpp"

using namespace anvil;

void IRenderer::UpdateInstances()
{
	int size = m_instances.size();
	for (int i = 0; i < size; i++)
	{
		if (!m_instances[i]->Update())
		{
			m_instances[i]->Unlink();
			m_instances.erase(m_instances.begin() + i);
			i--;
			size -= 1;
		}
	}

	m_promises.clear();
	auto updateInstances = [](std::vector<std::shared_ptr<Instance>> instances)
	{
		for (auto& instance : instances)
			instance->Update();
	};

	int cores = std::thread::hardware_concurrency();
	std::size_t const vecsize = m_instances.size() / (cores - 1);
	for (int i = 0; i < cores - 1; ++i)
	{
		std::size_t rest = 0;
		if (i + 1 == cores - 1)
			rest = m_instances.size() % (cores - 1);

		std::vector<std::shared_ptr<Instance>> sub_instances(m_instances.begin() + i*vecsize, m_instances.begin() + (i + 1)*vecsize + rest);
		m_promises.push_back(std::async(std::launch::async, updateInstances, sub_instances));
	}
}

void IRenderer::JoinInstanceThreads()
{
	for (auto& promise : m_promises)
	{
		promise.get();
	}
}