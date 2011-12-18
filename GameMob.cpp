GameMob::GameMob(int type,sf::Vector2f position):
    GameEntity(GameConfig::g_imgManag["mobs"].img,1,1,true)
    ,m_type(type){

    m_colWidth=GameConfig::g_mob[type].width;
    m_colHeight=GameConfig::g_mob[type].height;
    SetPosition(position);
    if(GameConfig::g_mob[type].path==0){
        m_velx=50;
        m_vely=0;
    }
    else{
        m_velx=0;
        m_vely=50;
    }
    stop();
    SetSubRect(sf::IntRect(GameConfig::g_mob[type].x,GameConfig::g_mob[type].y,m_colWidth,m_colHeight));
}
void GameMob::InverVel(){
    m_velx*=-1;
    m_vely*=-1;
}
void GameMob::Update(){
    float movHorTest=GetVelx()*m_app->GetFrameTime()/1000.f;
    float movVerTest=GetVely()*m_app->GetFrameTime()/1000.f;
    if(!CollisionGeneral( GetMovedRect( movHorTest ,movVerTest)))
        Move(movHorTest,movVerTest);
    else
        InverVel();
}
bool GameMob::isDraw(){
    return true;
}
bool GameMob::isDelete()const{
    return false;
}
bool GameMob::isCollision()const{
    return m_col;
}
bool GameMob::collisionEffect(Player &player){
    return false;
}
sf::FloatRect GameMob::GetRect()const{
    return sf::FloatRect(GetPosition().x,
                         GetPosition().y,
                         m_colWidth,m_colHeight);
}
sf::FloatRect GameMob::GetMovedRect(const float moveX,const float moveY)const{
    return sf::FloatRect(GetPosition().x+moveX,
                         GetPosition().y+moveY,
                         m_colWidth,m_colHeight);
}
bool GameMob::CollisionGeneral(const sf::FloatRect entityRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    minHeight=entityRect.Top/GameConfig::g_config["tileheight"];
    minWidth=entityRect.Left/GameConfig::g_config["tilewidth"];
    maxHeight=(entityRect.Top+entityRect.Height-1)/GameConfig::g_config["tileheight"];
    maxWidth=(entityRect.Left+entityRect.Width-1)/GameConfig::g_config["tilewidth"];

    if(minHeight<0)minHeight=0;
    if(maxHeight>(*m_map)->m_height)maxHeight=(*m_map)->m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>(*m_map)->m_width)maxWidth=(*m_map)->m_width;

    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if((*m_map)->Tile(x,y).solid){
                sf::FloatRect  theTile(x*GameConfig::g_config["tilewidth"],y*GameConfig::g_config["tileheight"],GameConfig::g_config["tilewidth"],GameConfig::g_config["tileheight"]);
                if(entityRect.Intersects(theTile)||theTile.Intersects(entityRect)){
                    return true;
                }
            }
        }
    }
    return false;
 }
GameMob::~GameMob()
{
}
