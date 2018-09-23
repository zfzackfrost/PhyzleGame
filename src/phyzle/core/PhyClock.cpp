#include <phyzle/core/PhyClock.h>
#include <boost/cstdlib.hpp>
#include <iostream>
PhyClock* PhyClock::s_Inst = nullptr;
bool PhyClock::s_IsDestroyed = false;

PhyClock::PhyClock()
{
}

PhyClock::~PhyClock()
{
}

PhyClock* PhyClock::inst()
{
	if (s_Inst == nullptr)
	{
		createInstance();
		if (s_Inst == nullptr)
		{
			throw std::runtime_error("No instance available");
		}
	}
	return s_Inst;
}

void PhyClock::init()
{
	m_StartTime = Clock::now();
}

phyFloat PhyClock::now()
{
	ClockDur gameDur = Clock::now() - m_StartTime;
	SecDur gameDurSeconds = boost::chrono::duration_cast<SecDur>(gameDur);
	return gameDurSeconds.count();
}

void PhyClock::createInstance()
{
	if (s_Inst == nullptr && !s_IsDestroyed)
	{
		s_Inst = new PhyClock();
		std::atexit(&PhyClock::destroyInstance);
	}
}

void PhyClock::destroyInstance()
{
	if (!s_IsDestroyed)
	{
		delete s_Inst;
		s_Inst = nullptr;
		s_IsDestroyed = true;
	}
}

