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

#include "includes.hpp"

int main(){
   cout<<"  /App Main::Start"<<endl;

   cout<<"  /App Main::Ressources Loading"<<endl;
   GameConfig::LoadConfig();

   cout<<"  /App Main::Creating window"<<endl;
    sf::RenderWindow App(sf::VideoMode(GameConfig::g_config["screenwidth"], GameConfig::g_config["screenheight"], 32), "Toisin", sf::Style::Close | sf::Style::Titlebar );

    App.EnableVerticalSync(true);

    cout<<"  /GameEngine  Start"<<endl;
    GameEngine *Game(0);
    Game=new GameEngine(App);
    delete Game;

}
