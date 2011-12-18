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

#include "EndState.hpp"
#include "GameEngine.hpp"

/**
    Construction des éléments du menu
**/
EndState::EndState(GameEngine* theGameEngine):m_win(false),m_end(GameConfig::g_imgManag["end"].img,GameConfig::g_imgManag["end"].nbrCollum,GameConfig::g_imgManag["end"].nbrLine){
    m_gameEngine=theGameEngine;

    m_end.SetOrigin(GameConfig::g_imgManag["end"].img.GetWidth()/2,GameConfig::g_imgManag["end"].img.GetHeight()/2);
    m_end.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]*0.50);
}
/**
    Initialisation des éléments du menu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void EndState::init(){
    m_wait.Reset();
    m_win=false;
}
/**
    Exécution des éléments
**/
void EndState::loop(){
    if(m_wait.GetElapsedTime()>3000 && !m_win){
        m_gameEngine->m_gameState[0]=new PlayState(m_gameEngine);
        m_gameEngine->changeState(0);
    }
    if(m_wait.GetElapsedTime()>8000 && m_win){
        m_gameEngine->m_gameState[0]=new PlayState(m_gameEngine);
        m_gameEngine->changeState(1);
    }
    (*m_gameEngine).m_app.SetView((*m_gameEngine).m_app.GetDefaultView());
}
/**
    Pause le jeu
    Appelé lors d'un changement de state
**/
void EndState::pause(){
}
/**
    Démarrage après une pause
**/
void EndState::resume(){
}
/**
    Remet à zéro
**/
void EndState::stop(){
    m_wait.Reset();
    m_win=true;
}
/**
    Utilisation des entrés
**/
void EndState::GetEvents(sf::Event Event){
}
/**
    Affichage des éléments
**/
void EndState::draw(){
    if(m_win)m_end.setAnimRow(1);
    else m_end.setAnimRow(0);

    (*m_gameEngine).m_app.Draw(m_end);
}

EndState::~EndState(){
}

