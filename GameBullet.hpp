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
#ifndef GAMEBULLET_H
#define GAMEBULLET_H



class GameBullet: public GameEntity{
    public:
        GameBullet(sf::Texture &img,int nbrFrame,int nbrLigne,int degat,Player *from,float velx,float vely, bool col,float height, float width);
        virtual bool isDraw();
        virtual bool isDelete()const;
        virtual bool isCollision()const;
        virtual bool collisionEffect(Player &player);
        virtual ~GameBullet();
    private:
        int m_degat;
        Player *m_from;
};

#endif // GAMEBULLET_H
