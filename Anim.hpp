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
#ifndef ANIM_H
#define ANIM_H

#include <SFML/System.hpp>
#include "PausableClock.cpp"

/*!
*	\class Anim
*	Implémente la gestion des animation selon le temps.
*/
class Anim
{
public:
	Anim(void);
	virtual ~Anim(void);

	//!Change au prochain frame d'animation
	void nextFrame();

	//!Change au frame d'animation défini par 'count'
	virtual void setFrame(const unsigned int &count);

	//!Change au premier frame animation
	void reset();

	//!Retourne le frame d'animation courante
	unsigned int currentFrame() const;


	//!Définis si l'animation est en boucle (choice=true)
	void loop(const bool &choice);

	//!Retourne si l'animation est joué en boucle
	bool isLoop() const;

	//!Joue l'animation
	void play();

	//!Arrete l'animation et remet le compteur à zéro
	void stop();

	//!Met l'animation en pause et laisse le compteur où il en est.
	void pause();

	//!Retourne true si l'animation est posé
	bool isStop() const;

	//!Retourne true si l'animation joue
	bool isPlaying() const;

	//!Définis le délais en seconde entre chaque frame.
	void setDelay(const float &delay);

	//!Retourne le délai entre chaque frame
	float delay() const;

	//!Met à jour l'animation
	virtual void update();

	//!Retourne le nombre de frame de l'animation
	virtual unsigned int getSize() const=0;
protected:
	//!Timer de l'animation
	PausableClock m_time;

	//!Frame courant de l'animation
	unsigned int m_frameCount;
	//!Delai en seconde entre chaque animation
	float m_delay;
	//!Si l'animation est en boucle
	bool m_isLoop;
	//!Si l'animation est en train de jouer
	bool m_play;
};

#endif


