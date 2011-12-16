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
#ifndef PAUSABLECLOCK_H
#define PAUSABLECLOCK_H


class PausableClock : public sf::Clock
{
public:
	//!Initialise le timer et le start
	PausableClock();
	//!Met en pause le timer
	void Pause();
	//!Met en marche le timer
	void Play();
	//!Change l'état du timer (pause<->marche)
	bool Toggle();
	//!Arrete le timer et le remet à zéro
	void Stop();
	//!Remet le timer à zéro et le met en marche
	void Reset();
	//!Retourne le temps écouler depuis la dernière fois qu'il à été mis en marche (avec Reset ou Play).
	float GetElapsedTime();

	float m_elapsedTime;

	bool m_pause;

};
#endif
