#include "cnpch.h"
#include "LayerStack.h"

namespace Crimson {

	LayerStack::LayerStack()
		: m_LayerIteratorOffset(0)
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}
	
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(begin() + (m_LayerIteratorOffset++), layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);

			// we wont need to check for bounds, in the case when we remove first element
			// m_LayerIteratorOffset will be offset to then next available slot for a layer
			// ... it will be at offset : 1, if there is 1 layer, so when we decrement
			// there will be no more layers and we will be at offset 0, being correct offset
			m_LayerIteratorOffset--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}