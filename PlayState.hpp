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

#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP
class PlayState: public GameState {
    public:
        PlayState(GameEngine* theGameEngine);
        virtual void init();
        virtual void loop();
        virtual void stop();
        virtual void pause();
        virtual void resume();
        virtual void GetEvents(sf::Event eventNew);
        virtual void draw();
        void save();
        void moveObject();
        void moveMob();
        void moveBullet();
        virtual ~PlayState();
    private:
        Player *m_player;
        MapTile *m_map;
        sf::View m_camera;
        sf::Sprite m_interface, m_light;
        bool m_start;
        ImgAnim m_lifebar;
        sf::Text m_message;
        sf::Text m_space;
        sf::Font m_font;
        int m_level;
        sf::Music m_music;
        sf::Sound m_dead,m_levelup;

        GameKey *m_key;

        vector<GameEntity*> *m_mapEntity;
        vector<GameMob*> *m_mapMob;
        vector<GameBullet*> *m_mapBullet;
        GameEngine *m_gameEngine;
};

#endif // PLAYSTATE_HPP
