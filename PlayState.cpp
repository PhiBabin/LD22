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

#include "PlayState.hpp"
#include "GameEngine.hpp"

/**
    Construction des éléments du jeu
**/
PlayState::PlayState(GameEngine* theGameEngine): m_player(0),m_map(0)
,m_gameEngine(theGameEngine){


    m_player= new Player(&(*m_gameEngine).m_app,&m_map);
    m_player->AddColor(1);
    m_player->AddColor(2);
    m_player->AddColor(3);
    m_player->AddColor(4);
    m_player->AddColor(5);
    m_player->AddColor(6);

    GameEntity::m_map=&m_map;
    GameEntity::m_app=&(*m_gameEngine).m_app;

    m_map =new MapTile(&(*m_gameEngine).m_app,m_player);

    m_mapMob=m_map->GetMapMob();
    m_mapBullet=m_map->GetMapBullet();

    m_mapEntity=m_map->GetMapEntity();
    m_player->SetMapObject(m_mapBullet);

    m_camera = m_gameEngine->m_app.GetDefaultView();
    m_camera.Zoom(0.5);
     m_gameEngine->m_app.SetView(m_camera);
}
/**
    Initialisation des éléments du jeu
    Cette méthode est appelé lors démarrage ou du redémarrage du state
**/
void PlayState::init(){
    resume();
}
/**
    Exécution des éléments
**/
void PlayState::loop(){

    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::E))
        cout<<"FPS="<<floor(1.f/(m_gameEngine->m_app.GetFrameTime())*1000)<<endl
        <<"Joueur 1 x="<<m_player->GetPosition().x<<" y="<<m_player->GetPosition().y<<endl
        <<"Velx="<<m_player->GetVelx()<<endl
        <<"Vely="<<m_player->GetVely()<<endl<<endl;

    /**
        Gestion des entrées claviers
    */


    //! Control du joueur 1
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::M))m_player->Jump();
    m_player->TurnUp(sf::Keyboard::IsKeyPressed(sf::Keyboard::W));
    m_player->Turn(sf::Keyboard::IsKeyPressed(sf::Keyboard::A),sf::Keyboard::IsKeyPressed(sf::Keyboard::D));
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::N))m_player->Shoot();

    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Num1))m_player->SwitchColor(1);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Num2))m_player->SwitchColor(2);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Num3))m_player->SwitchColor(3);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Num4))m_player->SwitchColor(4);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Num5))m_player->SwitchColor(5);
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Num6))m_player->SwitchColor(6);

//    const sf::Input &Input =m_gameEngine->m_app.GetInput();
//
//    //! Control du joueur 1
//    if(Input.IsKeyDown(sf::Key::L))m_player->Degat(-40);
//    if(Input.IsKeyDown(sf::Key::X))m_player->Jump();
//    if(Input.IsKeyDown(sf::Key::Z))m_player->Shoot();
//    m_player->TurnUp(Input.IsKeyDown(sf::Key::Up));
//    m_player->Turn(Input.IsKeyDown(sf::Key::Left),Input.IsKeyDown(sf::Key::Right));


    /**
        Gestion des personnages et objets
    */

 //! Déplacement du personnage 1
    m_player->MovePlayer();
//    movePlayer(*m_player);

 //! Déplacement de la caméra
  //  m_gameEngine->m_app.SetView(sf::View(m_player->GetViewRect()));
//    m_camera.SetCenter(sf::Vector2f(m_map->GetPlateau().x*GameConfig::g_config["platwidth"]*GameConfig::g_config["tilewidth"]+GameConfig::g_config["screenwidth"]/2,
//                        m_map->GetPlateau().y*GameConfig::g_config["platheight"]*GameConfig::g_config["tileheight"]));
    m_camera=sf::View(sf::FloatRect(m_map->GetPlateau().x*GameConfig::g_config["platwidth"]*GameConfig::g_config["tilewidth"],
                    m_map->GetPlateau().y*GameConfig::g_config["platheight"]*GameConfig::g_config["tileheight"],
                    GameConfig::g_config["screenwidth"]/2,
                    GameConfig::g_config["screenheight"]/2));
    m_gameEngine->m_app.SetView(m_camera);
 //! Déplacement des objets
    moveObject();
 //! Déplacement des mobs
    moveMob();
 //! Déplacement des mobs
    moveBullet();
}
/**
    Pause le jeu
    Appelé lors d'un changement de state
**/
void PlayState::pause(){
    m_player->Pause();
    for(unsigned int i=0;i<m_mapEntity->size();i++){
        m_mapEntity->at(i)->pause();
    }
    //! On change le state principale
    m_gameEngine->changeState(2);
}
/**
    Démarrage après une pause
**/
void PlayState::resume(){
    m_player->Resume();
    for(unsigned int i=0;i<m_mapEntity->size();i++){
        if(!m_mapEntity->at(i)->isStop())m_mapEntity->at(i)->play();
    }
}
/**
    Remet à zéro
**/
void PlayState::stop(){
}
/**
    Utilisation des entrés
**/
void PlayState::GetEvents(sf::Event){
}
/**
    Affichage des éléments
**/
void PlayState::draw(){
    m_map->Draw();
}
/**
    Déplacement des Mobs
**/
void PlayState::moveMob(){
    for(unsigned int i=0;i<m_mapMob->size();i++){
        sf::FloatRect Rect=m_mapMob->at(i)->GetRect();

        if(m_player->GetPlayerRect().Intersects(Rect)){
            m_player->Degat(2);
        }
        bool dies=false;
        for(unsigned int v=0;v<m_mapBullet->size()&&!dies;v++){
            sf::FloatRect RectBullet=m_mapBullet->at(v)->GetRect();
            if(Rect.Intersects(RectBullet)){
                dies=true;
                delete m_mapMob->at(i);
                m_mapMob->erase( m_mapMob->begin() + i );
                i--;
                delete m_mapBullet->at(v);
                m_mapBullet->erase( m_mapBullet->begin() + v );
            }

        }
    }
}

/**
    Déplacement des balles
**/
void PlayState::moveBullet(){
    for(unsigned int i=0;i<m_mapBullet->size();i++){
        sf::FloatRect Rect=m_mapBullet->at(i)->GetMovedRect(
        m_mapBullet->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000.f,
        m_mapBullet->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime()/1000.f);

        if(!m_map->CollisionGeneral(Rect,GameConfig::ColorToNbr(m_mapBullet->at(i)->GetColor())))
            m_mapBullet->at(i)->Move(Rect.Left-m_mapBullet->at(i)->GetPosition().x, Rect.Top-m_mapBullet->at(i)->GetPosition().y);
        else {
            delete m_mapBullet->at(i);
            m_mapBullet->erase( m_mapBullet->begin() + i );
            i--;
        }
    }
}
/**
    Déplacement des objets
**/
void PlayState::moveObject(){
    for(unsigned int i=0;i<m_mapEntity->size();i++){
        if(m_mapEntity->at(i)->isCollision()){
            //! On affiche détermine le rectangle de l'object
            sf::FloatRect Rect=m_mapEntity->at(i)->GetMovedRect(m_mapEntity->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime()/1000.f,m_mapEntity->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime()/1000.f);
            //! On vérifie si l'object touche le joueur si oui on supprimer l'objet et crée un animation d'un explosion
            if((m_player->GetPlayerRect().Intersects(Rect) && m_mapEntity->at(i)->collisionEffect(*m_player))){
//                //! On crée l'animation
//                m_mapEntity->push_back(new GameAnim(GameConfig::g_imgManag["explosion"].img,GameConfig::GameConfig::g_imgManag["explosion"].nbrCollum,GameConfig::GameConfig::g_imgManag["explosion"].nbrLine));
//                if(m_player->GetPlayerRect().Intersects(Rect) && m_mapEntity->at(i)->collisionEffect(*m_player))
//                m_mapEntity->back()->SetPosition(m_player->GetPosition().x+rand() *-3.f /RAND_MAX + 3.f,m_player->GetPosition().y+rand() *-5.f /RAND_MAX + 2.f);
//                m_mapEntity->back()->Move(0,5);
//                m_mapEntity->back()->setDelay(0.1);
                //! On crée libère la mémoire de le l'instance de l'objet
                delete m_mapEntity->at(i);
                //! On supprime le pointeur du tableau dynamique
                m_mapEntity->erase(m_mapEntity->begin()+i);
            }
            else if(!m_map->CollisionGeneral(Rect))
                //! On déplace l'objet
                m_mapEntity->at(i)->Move(Rect.Left-m_mapEntity->at(i)->GetPosition().x, Rect.Top-m_mapEntity->at(i)->GetPosition().y);
            else {
//                //! On crée une explosion
//                m_mapEntity->push_back(new GameAnim(GameConfig::g_imgManag["explosion2"].img,GameConfig::GameConfig::g_imgManag["explosion2"].nbrCollum,GameConfig::GameConfig::g_imgManag["explosion2"].nbrLine));
//                m_mapEntity->back()->SetPosition(m_mapEntity->at(i)->GetPosition().x,m_mapEntity->at(i)->GetPosition().y);
//                m_mapEntity->back()->setDelay(0.1);
                delete m_mapEntity->at(i);
                m_mapEntity->erase( m_mapEntity->begin() + i );
                i--;
            }
        }
        else{
            m_mapEntity->at(i)->Move(m_mapEntity->at(i)->GetVelx()*m_gameEngine->m_app.GetFrameTime(),m_mapEntity->at(i)->GetVely()*m_gameEngine->m_app.GetFrameTime());
        }
    }
}


/**
    Sauveguarde de l'instant
**/
void PlayState::save(){


}
/**
    Déconstruction des éléments du jeu
**/
PlayState::~PlayState(){
    delete m_player;
    delete m_map;
}
