#pragma once
#include <map>
#include <mutex>

namespace anvil
{
	template<class xtype, class ytype>
	class Interpolate
	{
	public:
		inline void AddPoint(const xtype x, const ytype y)
		{
			std::lock_guard<std::mutex> lock(this->m_mutex);
			m_points[x] = y;
		}

		virtual ytype GetPoint(const xtype x) = 0;
	protected:
		std::map<xtype,ytype> m_points;
		std::mutex m_mutex;
	};


	template<class xtype,class ytype>
	class LinearInterpolate : public Interpolate<xtype, ytype> //public Interpolate<int, glm::f32>
	{
	public:
		ytype GetPoint(const xtype x)
		{
			std::lock_guard<std::mutex> lock(this->m_mutex);
			const auto it = this->m_points.find(x);
			if (it != this->m_points.end())
			{
				
				return it->second;
			}
				
			const auto lastFrame = this->m_points.rbegin();
			if (x > lastFrame->first)
			{
				return lastFrame->second;
			}

			auto upper = this->m_points.lower_bound(x);
			auto lower = std::prev(this->m_points.upper_bound(x));

			const ytype pitch = (upper->second-lower->second)/(upper->first-lower->first);
			return lower->second+pitch*(upper->first-lower->first);		
		}
	};

	
}