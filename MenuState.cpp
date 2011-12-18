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

#include "MenuState.hpp"
#include "GameEngine.hpp"

/**
    Construction des éléments du menu
**/
MenuState::MenuState(GameEngine* theGameEngine):m_start(true),m_scaleUp(true){
    m_gameEngine=theGameEngine;

    m_pause.SetTexture(GameConfig::g_imgManag["pause"].img);
    m_pause.SetOrigin(GameConfig::g_imgManag["pause"].img.GetWidth()/2,GameConfig::g_imgManag["pause"].img.GetHeight()/2);
    m_pause.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]*0.50);

    m_press.SetTexture(GameConfig::g_imgManag["press"].img);
    m_press.SetOrigin(GameConfig::g_imgManag["press"].img.GetWidth()/2,GameConfig::g_imgManag["press"].img.GetHeight()/2);
    m_press.SetPosition(GameConfig::g_config["screenwidth"]/2,GameConfig::g_config["screenheight"]*0.90);

    m_main_menu.SetTexture(GameConfig::g_imgManag["main_menu"].img);
}
/**
    Initialisation des éléments du menu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void MenuState::init(){
}
/**
    Exécution des éléments
**/
void MenuState::loop(){
    if(m_start){
        if(m_press.GetScale().x>1.5)m_scaleUp=false;
        if(m_press.GetScale().x<1)m_scaleUp=true;

        if(m_scaleUp)m_press.SetScale(m_press.GetScale().x+0.001*m_gameEngine->m_app.GetFrameTime(),m_press.GetScale().x+0.001*m_gameEngine->m_app.GetFrameTime());
        else m_press.SetScale(m_press.GetScale().x-0.001*m_gameEngine->m_app.GetFrameTime(),m_press.GetScale().x-0.001*m_gameEngine->m_app.GetFrameTime());
    }
    else{
        if(m_pause.GetScale().x>1.5)m_scaleUp=false;
        if(m_pause.GetScale().x<1)m_scaleUp=true;

        if(m_scaleUp)m_pause.SetScale(m_pause.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime(),m_pause.GetScale().x+0.002*m_gameEngine->m_app.GetFrameTime());
        else m_pause.SetScale(m_pause.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime(),m_pause.GetScale().x-0.002*m_gameEngine->m_app.GetFrameTime());
    }
    (*m_gameEngine).m_app.SetView((*m_gameEngine).m_app.GetDefaultView());
}
/**
    Pause le jeu
    Appelé lors d'un changement de state
**/
void MenuState::pause(){
}
/**
    Démarrage après une pause
**/
void MenuState::resume(){
}
/**
    Remet à zéro
**/
void MenuState::stop(){
}
/**
    Utilisation des entrés
**/
void MenuState::GetEvents(sf::Event Event){
    if (Event.Type == sf::Event::KeyPressed){
        if(m_start)m_start=false;
        m_gameEngine->m_gameState[0]->resume();
        m_gameEngine->changeState(0);
    }
}
/**
    Affichage des éléments
**/
void MenuState::draw(){
    if(!m_start){
        (*m_gameEngine).m_app.Draw(m_pause);
    }
    else {
        (*m_gameEngine).m_app.Draw(m_main_menu);
        (*m_gameEngine).m_app.Draw(m_press);
    }
}

MenuState::~MenuState(){
}
