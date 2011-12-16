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
#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
struct Type{
    //! Propriétés
	bool visible, solid, kill, boomer, big, isExploded, fall ,touch;
	//! Propriété pour un block explosif
	int color;
	PausableClock boom;
	//! Le rectangle visible du tileset
	sf::IntRect zoneRect;
	sf::Sprite tile;};
struct MobSpawner{
    int type;
    int color;
    sf::Vector2f position;
};
class MapTile{
	public:
        MapTile();
        MapTile(sf::RenderWindow *App,Player *playerOne);
		void LoadMap();
		void Draw();
       // bool CollisionTile(float x,float y);
        Type Tile(float x, float y);
        void Explode(int x, int y);
        void RespawnMob();
        void PlanteauTransition(sf::Vector2i n);
        vector<GameEntity*> * GetMapEntity();
        vector <GameMob*> * GetMapMob();
        vector <GameBullet*> * GetMapBullet();
        sf::Vector2i GetPlateau();
        bool CollisionGeneral(const sf::FloatRect playerRect, int color);
        ~MapTile();

        //! Public variable
		int m_width, m_height;
		sf::Vector2f m_spawnLocationOne;
		vector <vector<Type> > m_tileSet;
	private:
		sf::Vector2i m_currentPlateau;
        sf::RenderWindow *m_app;
		sf::Texture m_ImgTypeTile;
		vector <vector<Type> > m_blankTileSet;
		vector <vector<Type> > *m_foo;
		vector <Type> m_typeList;
		vector <GameEntity*> m_mapEntity;
		vector <GameMob*> m_mapMob;
		vector <GameBullet*> m_mapBullet;
		vector <GameItem*> m_flag;
		vector <MobSpawner> m_mobSpawner;
		Player *m_player;
		sf::RenderTexture m_map;
		sf::RenderTexture m_background;
};


#endif // MAP_HPP_INCLUDED
