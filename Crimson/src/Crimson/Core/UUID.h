#pragma once

#include <random>

namespace Crimson
{
	class UUID
	{
	public:
		UUID()
		{
			std::uniform_int_distribution<int> random;
			std::random_device rd;
			std::default_random_engine generator(rd());
			m_uuid = random(generator);
		}
		template <typename T>
		UUID(T val) //T must-not be a custom type, (it can but there would have to be a hash implementation for said type)
		{
			std::hash<T> t_hash;
			m_uuid = t_hash(val);
		}
		operator uint64_t() { return m_uuid; }
	private:
		uint64_t m_uuid;
	};
}