#pragma once

namespace Hovel
{
	class TimeStep
	{
	public:
		TimeStep(float ts = 0)
			: m_TimeStep(ts)
		{}

		float GetSeconds() { return m_TimeStep; }
		float GetMilliseconds() { return m_TimeStep * 1000; }

		operator float() { return m_TimeStep; }
	private:
		float m_TimeStep;
	};
}