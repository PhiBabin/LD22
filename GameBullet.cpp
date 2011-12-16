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
#include "GameBullet.hpp"
#include "Player.hpp"
GameBullet::GameBullet(sf::Texture &img,int nbrFrame,int nbrLigne,int degat,Player *from,float velx,float vely, bool col=false,float height=0, float width=0):
    GameEntity(img,nbrFrame,nbrLigne,col,height, width)
    ,m_degat(degat)
    ,m_from(from){
     if(height==0){
         m_colHeight=img.GetHeight()/nbrLigne;
         m_colWidth=img.GetWidth()/nbrFrame;
     }
     m_velx=velx;
     m_vely=vely;
    m_isLoop=false;
}
bool GameBullet::isDraw(){
    return true;
}
bool GameBullet::isDelete()const{
    return false;
}
bool GameBullet::isCollision()const{
    return true;
}
bool GameBullet::collisionEffect(Player &player){
    if(&player!=&(*m_from)){
        player.Degat(m_degat);
        return true;
    }
    else return false;
}

GameBullet::~GameBullet()
{
}
