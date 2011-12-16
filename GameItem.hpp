#ifndef GAMEITEM_HPP_INCLUDED
#define GAMEITEM_HPP_INCLUDED

class GameItem: public GameEntity{
    public:
        GameItem(sf::Texture &img,int nbrFrame,int nbrLigne,int type);
        virtual bool isDraw();
        virtual bool isDelete()const;
        virtual bool isCollision()const;
        virtual bool collisionEffect(Player &player);
        virtual ~GameItem();
    private:
        int m_type;
};


#endif // GAMEITEM_HPP_INCLUDED
