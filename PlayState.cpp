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
PlayState::PlayState(GameEngine* theGameEngine): m_player(0),m_map(0),m_lifebar(GameConfig::g_imgManag["lifebar"].img,GameConfig::g_imgManag["lifebar"].nbrCollum,GameConfig::g_imgManag["lifebar"].nbrLine)
,m_gameEngine(theGameEngine),m_level(1){


    m_player= new Player(&(*m_gameEngine).m_app,&m_map);

    GameEntity::m_map=&m_map;
    GameEntity::m_app=&(*m_gameEngine).m_app;

    m_map =new MapTile(&(*m_gameEngine).m_app,m_player);

    m_mapMob=m_map->GetMapMob();
    m_mapBullet=m_map->GetMapBullet();

    m_mapEntity=m_map->GetMapEntity();
    m_player->m_listObject=m_mapBullet;

    m_key=new GameKey(m_player);
    m_key->AddKey(sf::Keyboard::Q,0,0,40,43);
    m_key->AddKey(sf::Keyboard::W,40,0,81,43);
    m_key->AddKey(sf::Keyboard::E,81,0,123,43);
    m_key->AddKey(sf::Keyboard::R,123,0,164,43);
    m_key->AddKey(sf::Keyboard::T,164,0,206,43);
    m_key->AddKey(sf::Keyboard::Y,206,0,246,43);
    m_key->AddKey(sf::Keyboard::U,246,0,288,43);
    m_key->AddKey(sf::Keyboard::I,288,0,330,43);
    m_key->AddKey(sf::Keyboard::O,330,0,372,43);
    m_key->AddKey(sf::Keyboard::P,372,0,414,43);
    //!-----
    m_key->AddKey(sf::Keyboard::A,10,43,49,84);
    m_key->AddKey(sf::Keyboard::S,49,43,91,84);
    m_key->AddKey(sf::Keyboard::D,91,43,132,84);
    m_key->AddKey(sf::Keyboard::F,132,43,174,84);
    m_key->AddKey(sf::Keyboard::G,174,43,215,84);
    m_key->AddKey(sf::Keyboard::H,215,43,257,84);
    m_key->AddKey(sf::Keyboard::J,257,43,300,84);
    m_key->AddKey(sf::Keyboard::K,300,43,340,84);
    m_key->AddKey(sf::Keyboard::L,340,43,384,84);
    //!-----
    m_key->AddKey(sf::Keyboard::Z,27,84,70,125);
    m_key->AddKey(sf::Keyboard::X,70,84,111,125);
    m_key->AddKey(sf::Keyboard::C,111,84,151,125);
    m_key->AddKey(sf::Keyboard::V,151,84,193,125);
    m_key->AddKey(sf::Keyboard::B,193,84,235,125);
    m_key->AddKey(sf::Keyboard::N,235,84,278,125);
    m_key->AddKey(sf::Keyboard::M,278,84,319,125);

    srand((unsigned)time(0));
    m_key->Reload();
    //m_key->AddJump();
    m_key->AddShoot();


    m_camera = m_gameEngine->m_app.GetDefaultView();
    m_camera.Zoom(0.25);
     m_gameEngine->m_app.SetView(m_camera);

     m_interface.SetTexture(GameConfig::g_imgManag["interface"].img);
     m_interface.SetScale(0.25,0.25);

     m_light.SetTexture(GameConfig::g_imgManag["light"].img);

    m_font.LoadFromFile("font/pixel2.ttf");

     m_message.SetColor(sf::Color::White);
     m_message.SetFont(m_font);
     m_message.SetCharacterSize(24);
     m_message.Scale(0.25,0.25);


    m_music.OpenFromFile("sounds/music.wav");
    m_music.SetLoop(true);
    m_music.SetVolume(75);
    m_music.Play();

    m_dead.SetBuffer(GameConfig::g_soundManag["dead"]);
    m_levelup.SetBuffer(GameConfig::g_soundManag["levelup"]);
    m_levelup.SetVolume(75);
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
    srand((unsigned)time(0));

    if(m_level==1){
        m_message.SetString("Goal: Turn on your flash light");
        if(m_player->m_flash){
            m_levelup.Play();
            m_level=2;
            m_key->Reload();
            m_key->AddJump();
        }
    }
    if(m_level==2){
        m_message.SetString("Goal: Jump the gap");
        if(m_player->GetPosition().x>250.f){
            m_levelup.Play();
            m_level=3;
          //  m_key->Reload();
          //  m_key->AddJump();
            m_key->AddShoot();
        }
    }
    if(m_level==3){
        m_message.SetString("Goal: Shoot everything that move");
        if(m_player->GetPosition().x>880.f){
            m_levelup.Play();
            m_level=4;
        }
    }
    if(m_level==4){
        m_message.SetString("I'm not alone anymore");
        if(m_player->GetPosition().x>1050.f){
            m_levelup.Play();
            m_gameEngine->m_gameState[2]->stop();
            m_gameEngine->changeState(2);
        }
    }


    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::E))
        cout<<"FPS="<<floor(1.f/(m_gameEngine->m_app.GetFrameTime())*1000)<<endl
        <<"Joueur 1 x="<<m_player->GetPosition().x<<" y="<<m_player->GetPosition().y<<endl
        <<"Velx="<<m_player->GetVelx()<<endl
        <<"Vely="<<m_player->GetVely()<<endl<<endl;

    /**
        Gestion des entrées claviers
    */


    //! Control du joueur 1
//    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::M))m_player->Jump();
//    m_player->TurnUp(sf::Keyboard::IsKeyPressed(sf::Keyboard::W));
    if(m_level!=1) m_player->Turn(sf::Keyboard::IsKeyPressed(sf::Keyboard::A),true);
//    //if(sf::Keyboard::IsKeyPressed(sf::Keyboard::N))m_player->Shoot();
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Return))pause();


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
    if(m_player->IsDead()){
        m_gameEngine->m_gameState[2]->init();
        m_gameEngine->changeState(2);
        m_dead.Play();
    }
//    movePlayer(*m_player);

 //! Déplacement de la caméra

    m_camera.SetCenter(m_player->GetPosition().x+50.f,
                       m_player->GetPosition().y+40.f
                       );
    m_gameEngine->m_app.SetView(m_camera);
    m_interface.SetPosition(m_camera.GetCenter().x-62, m_camera.GetCenter().y-21+23);
    m_lifebar.SetPosition(m_camera.GetCenter().x-60, m_camera.GetCenter().y-55);
    m_lifebar.setAnimRow(6-m_player->GetHp());

    m_light.SetPosition(m_camera.GetCenter().x-63, m_camera.GetCenter().y-57);

    m_message.SetPosition(m_camera.GetCenter().x-60, m_camera.GetCenter().y+12);
// //! Déplacement des objets
    moveObject();
// //! Déplacement des mobs
    moveMob();
// //! Déplacement des mobs
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
    m_gameEngine->changeState(1);
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
    if(m_level!=1)m_map->Draw();

    m_gameEngine->m_app.Draw(m_interface);
    m_key->Draw(&(*m_gameEngine).m_app,m_camera.GetCenter());
    m_gameEngine->m_app.Draw(m_light);
    m_gameEngine->m_app.Draw(m_lifebar);
    m_gameEngine->m_app.Draw(m_message);
}
/**
    Déplacement des Mobs
**/
void PlayState::moveMob(){
    for(unsigned int i=0;i<m_mapMob->size();i++){
        sf::FloatRect Rect=m_mapMob->at(i)->GetRect();

        if(m_player->GetPlayerRect().Intersects(Rect)){
            m_player->Degat(100);
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
