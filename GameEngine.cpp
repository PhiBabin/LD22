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

#include "GameEngine.hpp"
GameEngine::GameEngine(sf::RenderWindow &app):m_app(app),m_running(true),m_vip(0){
    init();
    loop();
}
/**
    Initialisation du moteur
**/
void GameEngine::init(){
   cout<<"  /GameStates::Init"<<endl;
    m_gameState.push_back(new PlayState(this));
}
/**
    Boucle du Moteur
**/
void GameEngine::loop(){
    //! Set the seed
    srand((unsigned)time(0));
   cout<<"  /GameEngine::loop start"<<endl;
    while(m_app.IsOpened()&&m_running){
        sf::Event event;
        while(m_app.PollEvent(event)){
                switch(event.Type){
                  case sf::Event::Closed:       //! Window closed
                    m_running=false;
                    break;
                  case sf::Event::GainedFocus:  //! Window gained focus
                    m_gameState[m_vip]->resume();
                    break;
                  case sf::Event::LostFocus:    //! Window lost focus
                    m_gameState[m_vip]->pause();
                    break;
                  case sf::Event::Resized:      //! Window resized
                    break;
                  default:                      //! Current active state will handle
                    m_gameState[m_vip]->GetEvents(event);
              }
        }
        m_gameState[m_vip]->loop();
        m_app.Clear(sf::Color::Black);

        m_gameState[m_vip]->draw();
        m_app.Display();
    }
    m_app.Close();
   cout<<"  /GameEngine::loop end"<<endl;
}
/**
    Boucle du Moteur
**/
void GameEngine::changeState(unsigned int frontState){
    if(frontState<m_gameState.size()){
        m_gameState[m_vip]=m_gameState[frontState];
    }

}
GameEngine::~GameEngine(){
//    for(unsigned int i=1;i<m_gameState.size();i++){
//        delete m_gameState.at(i);
//    }
   cout<<"  /GameEngine::delete"<<endl;
}

