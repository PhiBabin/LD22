#include "GameItem.hpp"
#include "Player.hpp"
GameItem::GameItem(sf::Texture &img,int nbrFrame,int nbrLigne,int type):
    GameEntity(img,nbrFrame,nbrLigne,true)
    ,m_type(type){
     m_colHeight=img.GetHeight()/nbrLigne;
     m_colWidth=img.GetWidth()/nbrFrame;
    m_isLoop=false;
}
bool GameItem::isDraw(){
    return true;
}
bool GameItem::isDelete()const{
    return false;
}
bool GameItem::isCollision()const{
    return m_col;
}
bool GameItem::collisionEffect(Player &player){
    return false;
}

GameItem::~GameItem()
{
}
