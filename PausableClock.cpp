/**
Copyright (C) 2011 babin philippe

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/
#include "PausableClock.hpp"

//using namespace core;

PausableClock::PausableClock() : m_elapsedTime(0.f), m_pause(false)
{

}

void PausableClock::Pause()
{
	if(!m_pause)
	{
		m_pause=true;
		m_elapsedTime+=sf::Clock::GetElapsedTime();
	}
}

void PausableClock::Play()
{
	if(m_pause)
	{
		m_pause=false;
		sf::Clock::Reset();
	}
}

bool PausableClock::Toggle()
{
	if(m_pause)
	{
		Play();
		return true;
	}
	Pause();
	return false;
}

void PausableClock::Stop()
{
	Reset();
	m_pause=true;
	m_elapsedTime=0;
}

void PausableClock::Reset()
{
	m_elapsedTime=0;
	sf::Clock::Reset();
	m_pause=false;
	Play();
}

float PausableClock::GetElapsedTime()
{
	if(m_pause)
		return m_elapsedTime;
	return sf::Clock::GetElapsedTime() + m_elapsedTime;
}

