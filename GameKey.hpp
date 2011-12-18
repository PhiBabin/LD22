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

#ifndef KEYY_HPP_INCLUDED
#define KEYY_HPP_INCLUDED
struct Key{
    //! Propriétés
    sf::Sprite key;
    sf::IntRect rect;
    sf::Keyboard::Key car;
	//! Propriété pour de son état
	int state;
	bool visible;

	bool bomb;
	bool atomBomb;
	bool reveal;
	bool heart;
	bool shoot;
	bool jump;};
class GameKey{
    public:
        GameKey(Player *player);
        void AddKey(sf::Keyboard::Key name, float x1, float y1, float x2, float y2);
        void PressKey(int id);
        void Reload();
        void AddShoot();
        void AddJump();

        void Draw(sf::RenderWindow *App, sf::Vector2f camera);
        ~GameKey();
        vector<GameAnim*> m_listObject;
    private:
        vector<Key> m_key;
        vector<ImgAnim> m_icon;
        Player *m_player;
};
#endif
