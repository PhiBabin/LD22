


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
    ImgAnim newIcon= ImgAnim(GameConfig::g_imgManag["items"].img,GameConfig::g_imgManag["items"].nbrCollum,GameConfig::g_imgManag["items"].nbrLine);
    newIcon.SetScale(0.25,0.25);
    m_icon.push_back(newIcon);
}
void GameKey::PressKey(int id){
    if(m_key[id].state==0){
        m_key[id].state=1;
         m_key[id].key.SetSubRect( sf::IntRect( m_key[id].rect.Left, m_key[id].rect.Top+125.f,m_key[id].rect.Width, m_key[id].rect.Height) ) ;

         if(m_key[id].bomb){

            m_listObject.push_back(new GameAnim(GameConfig::GameConfig::g_imgManag["explosion"].img,GameConfig::GameConfig::g_imgManag["explosion"].nbrCollum,GameConfig::GameConfig::g_imgManag["explosion"].nbrLine));
            m_listObject.back()->SetPosition(m_key[id].key.GetPosition());
            m_listObject.back()->setDelay(0.1);

             m_key[id].bomb=false;
             if(id<10){
                 if(id>=1)PressKey(id-1);
                 if(id<9)PressKey(id+1);

                 if(id<=8)PressKey(id+10);
             }
             if(id>=10 && id<19){
                 if(id>=11)PressKey(id-1);
                 if(id<18)PressKey(id+1);

                 PressKey(id-10);

                 if(id<17)PressKey(id+9);
             }
             if(id>=19 && id<27){
                 if(id>=20)PressKey(id-1);
                 if(id<26)PressKey(id+1);

                 PressKey(id-9);

             }
         }
    }
}
void GameKey::Reload(){
     int pItem;
    for(int i=0;i<m_key.size();i++){
        m_key[i].state=0;
        m_key[i].key.SetSubRect(m_key[i].rect);
        m_key[i].atomBomb=false;
        m_key[i].bomb=false;
        m_key[i].reveal=false;
        m_key[i].heart=false;
        m_key[i].jump=false;
        m_key[i].shoot=false;

        pItem=rand() % 100 + 1;
        cout<<pItem<<endl;
        if(pItem>=0 && pItem<30){
            m_key[i].reveal=true;
        }
        if(pItem>=30 && pItem<40){
            m_key[i].atomBomb=true;
        }
        if(pItem>=40 && pItem<60){
            m_key[i].heart=true;
        }
        if(pItem>=60 && pItem<90){
            m_key[i].bomb=true;
        }
    }

}

void GameKey::Draw(sf::RenderWindow *App, sf::Vector2f camera){
    for(int i=0;i<m_key.size();i++){
        if(sf::Keyboard::IsKeyPressed( m_key[i].car)) PressKey(i);

        m_key[i].key.SetPosition(camera.x-50+m_key[i].rect.Left*0.25,camera.y+m_key[i].rect.Top*0.25);
        App->Draw(m_key[i].key);
        if(m_key[i].state==1){
            if(m_key[i].bomb){
                m_icon[i].setAnimRow(1);
                m_icon[i].SetPosition(camera.x-49+m_key[i].rect.Left*0.25,camera.y+4+m_key[i].rect.Top*0.25);
                App->Draw(m_icon[i]);
            }
            if(m_key[i].reveal){
                m_icon[i].setAnimRow(0);
                m_icon[i].SetPosition(camera.x-49+m_key[i].rect.Left*0.25,camera.y+4+m_key[i].rect.Top*0.25);
                App->Draw(m_icon[i]);
            }
        }
    }


    for(int i=0;i<m_listObject.size();i++){
        if ((m_listObject[i])->isDelete()) {
            delete m_listObject[i];
            m_listObject.erase( m_listObject.begin() + i );
        } else {
            App->Draw(*(m_listObject.at(i)));
        }
    }
}
GameKey::~GameKey(){
}
