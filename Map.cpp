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

#include "Map.hpp"
MapTile::MapTile():m_app(NULL),m_player(NULL) {}
MapTile::MapTile(sf::RenderWindow *App, Player *player):
m_width(0),m_height(0),m_app(App),m_player(player) {

    LoadMap();
}
// bool MapTile::CollisionTile(float x, float y){
//    return m_tileSet.at(x).at(y).solid;
// }

Type MapTile::Tile(float x, float y) {
    if (x>=0 && y>=0 && x<=m_width && y<=m_height) return m_tileSet.at(x).at(y);
    else {
        cerr<<"[FATAL ERROR] Tile out of range. ("<<x<<" ,"<<y<<")"<<endl;
        exit(0);
    }
}


void MapTile::RespawnMob() {
    while (m_mapMob.size()!=0) {
        delete m_mapMob.at(0);
        m_mapMob.erase(m_mapMob.begin());
    }
    for (unsigned int m=0;m<m_mobSpawner.size();m++) {
        m_mapMob.push_back(new GameMob(m_mobSpawner[m].type,m_mobSpawner[m].position));
    }
}
void MapTile::Explode(int x, int y) {
    cout<<"BOOOM!!!"<<x<<" "<<y<<endl;
    //exit(0);
    m_mapEntity.push_back(new GameAnim(GameConfig::g_imgManag["boom"].img,GameConfig::GameConfig::g_imgManag["boom"].nbrCollum,GameConfig::GameConfig::g_imgManag["boom"].nbrLine));
    m_mapEntity.back()->SetPosition(x*GameConfig::g_config["tilewidth"],y*GameConfig::g_config["tileheight"]);
    m_mapEntity.back()->setDelay(0.125);
    m_mapEntity.back()->SetColor(GameConfig::NbrToColor(m_tileSet[x][y].color));

    int xp,yp;
    if (m_tileSet[x][y].big) {
        m_tileSet[x][y]=m_typeList[VIDE];
        for (int xe=-2;xe<3&&x+xe<m_width;xe++) {
            for (int ye=-2;ye<3&&y+ye<m_height;ye++) {
                if (!(xe==0 && ye==0)&&m_tileSet[x+xe][y+ye].boomer && !m_tileSet[x+xe][y+ye].isExploded) {
                    m_tileSet[x+xe][y+ye].isExploded=true;
                    Explode(x+xe,y+ye);
                }
            }
        }
    } else {
        for (int i=0;i<4;i++) {
            if (i==0) {
                xp=1;
                yp=0;
            }
            if (i==1) {
                xp=0;
                yp=1;
            }
            if (i==2) {
                xp=-1;
                yp=0;
            }
            if (i==3) {
                xp=0;
                yp=-1;
            }
            if (m_tileSet[x+xp][y+yp].boomer && !m_tileSet[x+xp][y+yp].isExploded && m_tileSet[x+xp][y+yp].color<=m_tileSet[x][y].color) {
                m_tileSet[x+xp][y+yp].isExploded=true;
                m_tileSet[x+xp][y+yp].boom.Reset();
            }

        }
    }
    m_tileSet[x][y]=m_typeList[VIDE];
}

vector<GameEntity*> * MapTile::GetMapEntity() {
    return &m_mapEntity;
}
vector<GameMob*> * MapTile::GetMapMob() {
    return &m_mapMob;
}
vector<GameBullet*> * MapTile::GetMapBullet() {
    return &m_mapBullet;
}

bool MapTile::CollisionGeneral(const sf::FloatRect entityRect,int color=0) {
    int maxHeight, minHeight, maxWidth, minWidth;
    minHeight=entityRect.Top/GameConfig::g_config["tileheight"];
    minWidth=entityRect.Left/GameConfig::g_config["tilewidth"];
    maxHeight=(entityRect.Top+entityRect.Height-1)/GameConfig::g_config["tileheight"];
    maxWidth=(entityRect.Left+entityRect.Width-1)/GameConfig::g_config["tilewidth"];

    if (minHeight<0)minHeight=0;
    if (maxHeight>m_height)maxHeight=m_height;
    if (minWidth<0)minWidth=0;
    if (maxWidth>m_width)maxWidth=m_width;
    for (int y=minHeight;y<=maxHeight;y++) {
        for (int x=minWidth;x<=maxWidth;x++) {
            if (!(x>=m_width or y>=m_height)) {
                if (m_tileSet[x][y].solid) {
                    sf::FloatRect  theTile(x*GameConfig::g_config["tilewidth"],y*GameConfig::g_config["tileheight"],GameConfig::g_config["tilewidth"],GameConfig::g_config["tileheight"]);
                    if (entityRect.Intersects(theTile)||theTile.Intersects(entityRect)) {
                        if (m_tileSet[x][y].boomer && m_tileSet[x][y].color<=color&& color!=0)Explode(x,y);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void MapTile::Draw() {
    //! On affiche les tiles du background
    m_app->Draw(sf::Sprite(m_background.GetTexture()));
    //! On affiche la map
    //m_app->Draw(sf::Sprite(m_map.GetTexture()));
    for (int y=0;y<m_height;y++) {
        for (int x=0;x<m_width;x++) {
//            if (m_tileSet[x][y].fall && m_tileSet[x][y].touch) {
//                alphaLevel=m_tileSet[x][y].tile.GetColor().a - 0.4*m_app->GetFrameTime();
//                if (alphaLevel<0){
//                    alphaLevel=0;
//                    m_tileSet[x][y].solid=false;
//                }
//                m_tileSet[x][y].tile.SetColor(sf::Color(255,255,255,alphaLevel));
//            }
//            if (m_tileSet[x][y].isExploded && m_tileSet[x][y].boom.GetElapsedTime()>=125) {
//                Explode(x,y);
//                m_tileSet[x][y]=m_typeList[VIDE];
//            }
            if ((m_tileSet.at(x)).at(y).visible) {
                m_app->Draw(m_tileSet.at(x).at(y).tile);
            }
        }
    }
    //! On affiche les mobs de la carte
    for (unsigned int i=0;i<m_mapMob.size();i++) {
        cout<<"l";
        if ((m_mapMob.at(i))->isDelete()) {
            delete m_mapMob.at(i);
            m_mapMob.erase( m_mapMob.begin() + i );
        }
        else {
            m_mapMob.at(i)->Update();
            m_app->Draw(*(m_mapMob.at(i)));
        }
    }
    cout<<"e"<<endl ;
    //! On affiche les objets de la carte
    for (unsigned int i=0;i<m_mapEntity.size();i++) {
        if ((m_mapEntity.at(i))->isDelete()) {
            delete m_mapEntity.at(i);
            m_mapEntity.erase( m_mapEntity.begin() + i );
        } else {
            m_app->Draw(*(m_mapEntity.at(i)));
        }
    }
    cout<<"p"<<endl ;
//    //! On affiche les flags de la carte
//    for (unsigned int i=0;i<m_flag.size();i++) {
//        m_app->Draw(*(m_flag.at(i)));
//    }
    //! On affiche les balles de la carte
    for (unsigned int i=0;i<m_mapBullet.size();i++) {
        if ((m_mapBullet.at(i))->isDelete()) {
            delete m_mapBullet.at(i);
            m_mapBullet.erase( m_mapBullet.begin() + i );
        } else {
            m_app->Draw(*(m_mapBullet.at(i)));
        }
    }


    //! On affiche le personnage et ces éléments
    m_app->Draw(*m_player);
    m_player->Drawing();
}

void MapTile::LoadMap() {
    map<string,string> levelConfig;
    const int tilewidth =GameConfig::g_config["tilewidth"];
    const int tileheight =GameConfig::g_config["tileheight"];

    //! On charge la configuration du niveau
    stringstream ss;
    ss<<GameConfig::g_config["level"];
    string pathConfig="map/level"+ ss.str()+".tmx";


    //! Initiation des textures temporaire
    sf::Texture image_schemaImg;
    m_ImgTypeTile.LoadFromFile("map/level"+ ss.str()+"/tileset.png");

    TiXmlDocument doc(pathConfig.c_str());
    doc.LoadFile();

    TiXmlHandle hRoot(&doc);
    TiXmlHandle hDoc(0);
    TiXmlElement* pElem;
    TiXmlElement* elemProp;
    hDoc=TiXmlHandle(hRoot.FirstChildElement().Element());

    //! On change les dimensions de la map
    m_width=atoi(hRoot.FirstChild("map").Element()->Attribute("width"));
    m_height=atoi(hRoot.FirstChild("map").Element()->Attribute("height"));

    //! On crée une liste de tile aux bonnes dimensions
    m_typeList.erase(m_typeList.begin(),m_typeList.end());
    m_typeList.resize((m_ImgTypeTile.GetWidth())/ tilewidth*(m_ImgTypeTile.GetHeight()/ tileheight));

    //! On charge le tileset
    pElem=hDoc.FirstChild("tileset").FirstChild().Element()->NextSiblingElement();
    for (; pElem; pElem=pElem->NextSiblingElement()) {
        int id=atoi(pElem->Attribute("id"));
        int x=id%(m_ImgTypeTile.GetWidth()/ tilewidth);
        int y=(id-id%(m_ImgTypeTile.GetWidth()/tilewidth))/(m_ImgTypeTile.GetWidth()/tilewidth);

        Type newTile;
        newTile.visible=false;
        newTile.kill=false;
        newTile.solid=true;
        newTile.isExploded=false;
        newTile.boomer=false;
        newTile.big=false;
        newTile.fall=false;
        newTile.touch=false;
        newTile.color=0;

        newTile.tile.SetTexture(m_ImgTypeTile);
        newTile.zoneRect=sf::IntRect(x*tilewidth, y*tileheight, tilewidth, tileheight);

        elemProp=TiXmlHandle(pElem).FirstChild("properties").FirstChild().Element();
        for (; elemProp; elemProp=elemProp->NextSiblingElement()) {
            if (string(elemProp->Attribute("name"))=="visible"&& atoi(elemProp->Attribute("value"))==1) {
                newTile.visible=true;
            }

            if (string(elemProp->Attribute("name"))=="kill"&& atoi(elemProp->Attribute("value"))==1) {
                newTile.kill=true;
            }

            if (string(elemProp->Attribute("name"))=="solid"&& atoi(elemProp->Attribute("value"))==0) {
                newTile.solid=false;
            }

            if (string(elemProp->Attribute("name"))=="boomer"&& atoi(elemProp->Attribute("value"))==1) {
                newTile.boomer=true;
            }

            if (string(elemProp->Attribute("name"))=="big"&& atoi(elemProp->Attribute("value"))==1) {
                newTile.big=true;
            }

            if (string(elemProp->Attribute("name"))=="fall"&& atoi(elemProp->Attribute("value"))==1) {
                newTile.fall=true;
            }

            if (string(elemProp->Attribute("name"))=="color") {
                newTile.color=atoi(elemProp->Attribute("value"));
            }
        }
        m_typeList[id]=newTile;
    }
    //! On instansifie les entity
    pElem=hDoc.FirstChild("objectgroup").FirstChild().Element();
    for (; pElem; pElem=pElem->NextSiblingElement()) {
        //! Spawn point
        if (string(pElem->Attribute("type"))=="spawn") {
            sf::Vector2f spawnLocationOne(atoi(pElem->Attribute("x")),atoi(pElem->Attribute("y"))-GameConfig::g_config["playercollheight"]);
            m_spawnLocationOne=spawnLocationOne;
            m_player->SetPosition(m_spawnLocationOne);
        }


        //! Mobs
        if (string(pElem->Attribute("type"))=="mob") {
            MobSpawner newMob;
            newMob.position=sf::Vector2f(atoi(pElem->Attribute("x")) ,atoi(pElem->Attribute("y")));
            elemProp=TiXmlHandle(pElem).FirstChild("properties").FirstChild().Element();
            for (; elemProp; elemProp=elemProp->NextSiblingElement()) {
                if (string(elemProp->Attribute("name"))=="type") {
                    newMob.type=atoi(elemProp->Attribute("value"));
                }
                if (string(elemProp->Attribute("name"))=="color") {
                    newMob.color=atoi(elemProp->Attribute("value"));
                }
            }
            m_mapMob.push_back(new GameMob(newMob.type,newMob.position));
          //  m_mobSpawner.push_back(newMob);
        }
    }
    //! On charge les mobs
    //RespawnMob();
//    for (unsigned int m=0;m<m_mobSpawner.size();m++) {
//        m_mapMob.push_back(new GameMob(m_mobSpawner[m].type,m_mobSpawner[m].position));
//    }

    //! Charge le background
    m_background.Create(m_width*tilewidth,m_height*tileheight);
    pElem=hDoc.FirstChild("layer").FirstChild().FirstChild().Element();
    for (int i=0; pElem; pElem=pElem->NextSiblingElement()) {
        int x=i%(m_width);
        int y=(i-i%(m_width))/m_width;
        int id =atoi(pElem->Attribute("gid"));
        if (id !=0)id--;

        Type theNewTile = m_typeList[id];
        theNewTile.tile.SetTexture(m_ImgTypeTile);
        theNewTile.tile.SetPosition(x*tilewidth,y*tileheight);
        theNewTile.tile.SetSubRect(m_typeList[id].zoneRect);

        if (theNewTile.visible)m_background.Draw(theNewTile.tile);
        i++;
    }
    m_background.Display();

    //! On vide la map
    vector<Type> tileListSub;
    tileListSub.resize(m_height);
    m_tileSet.erase(m_tileSet.begin(),m_tileSet.end());
    m_tileSet.resize(m_width,tileListSub);

    //! Charge le niveau
    m_map.Create(m_width*tilewidth,m_height*tileheight);
    pElem=TiXmlHandle(hDoc.FirstChild("layer").Element()->NextSiblingElement()).FirstChild().FirstChild().Element();
    for (int i=0; pElem; pElem=pElem->NextSiblingElement()) {
        int x=i%(m_width);
        int y=(i-i%(m_width))/m_width;
        int id =atoi(pElem->Attribute("gid"));
        if (id !=0)id--;

        Type theNewTile = m_typeList[id];
        theNewTile.tile.SetTexture(m_ImgTypeTile);
        theNewTile.tile.SetPosition(x*tilewidth,y*tileheight);
        theNewTile.tile.SetSubRect(m_typeList[id].zoneRect);
        m_tileSet[x][y]= theNewTile;

        //!if(m_tileSet[x][y].visible)m_map.Draw(m_tileSet[x][y].tile);
        i++;
    }
    m_blankTileSet=m_tileSet;
}
MapTile::~MapTile() {
    for (unsigned int i=0;i<m_mapEntity.size();i++) {
        delete m_mapEntity.at(i);
    }
}
