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

#ifndef INCLUDES_HPP_INCLUDED
#define INCLUDES_HPP_INCLUDED

/**
    Configuration
*/

//! Constantes
#define GAUCHE true
#define DROITE false
#define HAUT true
#define BAS false
#define BOUGE true
#define IMMOBILE false

#define VIDE 0


#define RED 1
#define YELLOW 2
#define BLUE 3
#define GREEN 4
#define VIOLET 5
#define ORANGE 6
#define WHITE 7

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml/tinyxmlerror.cpp"
#include "tinyxml/tinystr.cpp"
#include "tinyxml/tinyxmlparser.cpp"
#include "tinyxml/tinyxml.cpp"



sf::Clock Clock;
using namespace std;


#include "Anim.cpp"
#include "ImgAnim.cpp"

#include "GameConfig.cpp"

#include "GameEntity.hpp"
#include "GameAnim.hpp"
#include "GameItem.hpp"
#include "GameMob.hpp"
#include "GameBullet.hpp"
#include "GameKey.hpp"

#include "Player.hpp"
#include "Map.hpp"

#include "GameEntity.cpp"
#include "GameAnim.cpp"
#include "GameItem.cpp"
#include "GameMob.cpp"
#include "GameBullet.cpp"
#include "GameKey.cpp"

#include "Player.cpp"
#include "Map.cpp"

#include "GameState.cpp"
#include "MenuState.cpp"
#include "PlayState.cpp"
#include "EndState.cpp"
#include "GameEngine.cpp"

#endif // INCLUDES_HPP_INCLUDED
