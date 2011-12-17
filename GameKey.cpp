


GameKey::GameKey(){
}
void GameKey::AddKey(sf::Keyboard::Key name, float x1, float y1, float x2, float y2){
    Key newKey;
    newKey.key.SetTexture(GameConfig::g_imgManag["key"].img);
    newKey.rect=sf::IntRect(x1,y1,x2-x1,y2-y1);
    newKey.key.SetSubRect(newKey.rect);
    newKey.key.SetScale(0.25,0.25);
    newKey.car=name;
    newKey.state=0;
    m_key.push_back(newKey);
}
void GameKey::PressKey(int id){
    m_key[id].state=1;
     m_key[id].key.SetSubRect( sf::IntRect( m_key[id].rect.Left, m_key[id].rect.Top+125.f,m_key[id].rect.Width, m_key[id].rect.Height) ) ;
}

void GameKey::Draw(sf::RenderWindow *App, sf::Vector2f camera){
    for(int i=0;i<m_key.size();i++){
        if(sf::Keyboard::IsKeyPressed( m_key[i].car)) PressKey(i);

        m_key[i].key.SetPosition(camera.x-50+m_key[i].rect.Left*0.25,camera.y+m_key[i].rect.Top*0.25);
        App->Draw(m_key[i].key);
    }

}
GameKey::~GameKey(){
}
