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

#include "Anim.hpp"

Anim::Anim() : m_time()
{
	m_frameCount=0;
	m_delay=0.f;
	m_isLoop=true;
	m_play=true;
}

Anim::~Anim()
{
}

bool Anim::isStop() const{
    if(m_time.m_elapsedTime==0 && m_time.m_pause)return true;
    else return false;
}
void Anim::nextFrame()
{
	if(currentFrame()==getSize()-1)
	{
			setFrame(0);
			if(!isLoop())
				stop();
	}
	else
		setFrame(currentFrame()+1);
}

void Anim::setFrame(const unsigned int &count)
{
    if(!(count==0 && !m_isLoop)){
        if(count<getSize())
            m_frameCount=count;
        else
            m_frameCount=getSize()-1;
    }
}

void Anim::reset()
{
	stop();
	play();
}

void Anim::loop(const bool &choice)
{
	m_isLoop=choice;
}

void Anim::play()
{
	m_play = true;
	m_time.Play();
}

void Anim::stop()
{
	Anim::m_play = false;
	setFrame(getSize()-1);
	m_time.Stop();
}

void Anim::pause()
{
	Anim::m_play = false;
	m_time.Pause();
}

bool Anim::isPlaying() const
{
	return m_play;
}

void Anim::setDelay(const float &delay)
{
	m_delay=delay;
}

float Anim::delay() const
{
	return m_delay*1000.f;
}

unsigned int Anim::currentFrame() const
{
	return m_frameCount;
}

bool Anim::isLoop() const
{
	return m_isLoop;
}

void Anim::update()
{
	if(isPlaying())
	{
		if(delay())
		{
			unsigned int frameCount = (unsigned int)(m_time.GetElapsedTime()/delay());
			if(!isLoop() && frameCount>getSize())
				stop();
			else
			{
				frameCount = frameCount % getSize();
				setFrame(frameCount);
			}
		}
		else nextFrame();
		//cout<< m_frameCount<<endl;
	}
}


