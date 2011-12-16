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
#ifndef GAMESTATE_H
#define GAMESTATE_H
class GameEngine;

class GameState{
    public:
        GameState();
        GameState(GameEngine* theGameEngine);
        virtual void init()=0;
        virtual void loop()=0;
        virtual void stop()=0;
        virtual void pause()=0;
        virtual void resume()=0;
        virtual void GetEvents(sf::Event eventNew)=0;
        virtual void draw()=0;
        virtual ~GameState();
    protected:
        GameEngine* m_gameEngine;
};

#endif // GAMESTATE_H
