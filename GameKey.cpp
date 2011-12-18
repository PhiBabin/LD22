


GameKey::GameKey(Player *player):
    m_player(player){
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
         if(m_key[id].reveal){

             m_key[id].reveal=false;
             if(id<10){
                 if(id>=1)m_key[id-1].visible=true;
                 if(id<9)m_key[id+1].visible=true;

                 if(id<=8)m_key[id+10].visible=true;
             }
             if(id>=10 && id<19){
                 if(id>=11)m_key[id-1].visible=true;
                 if(id<18)m_key[id+1].visible=true;

                 m_key[id-10].visible=true;

                 if(id<17)m_key[id+9].visible=true;
             }
             if(id>=19 && id<27){
                 if(id>=20)m_key[id-1].visible=true;
                 if(id<26)m_key[id+1].visible=true;

                 m_key[id-9].visible=true;

             }
         }
         if(m_key[id].heart){
             m_key[id].heart=false;
             m_player->Degat(-2);
         }

         if(m_key[id].atomBomb){

             m_key[id].atomBomb=false;
            m_listObject.push_back(new GameAnim(GameConfig::GameConfig::g_imgManag["explosion"].img,GameConfig::GameConfig::g_imgManag["explosion"].nbrCollum,GameConfig::GameConfig::g_imgManag["explosion"].nbrLine));
            m_listObject.back()->SetPosition(m_key[id].key.GetPosition());
            m_listObject.back()->setDelay(0.2);
            m_listObject.back()->Move(-15,-15);
            m_listObject.back()->SetScale(3,3);

                if(id>=0 && id<10){
                    for(int e=0;e<10;e++){
                        PressKey(e);
                    }
                }
                if(id>=10 && id<19){
                    for(int e=10;e<19;e++){
                        PressKey(e);
                    }
                }
                 if(id>=19 && id<27){
                    for(int e=19;e<27;e++){
                        PressKey(e);
                    }
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
        m_key[i].visible=false;

        pItem=rand() % 100 + 1;
        if(pItem>=0 && pItem<40){
            m_key[i].reveal=true;
        }
        if(pItem>=40 && pItem<45){
            m_key[i].atomBomb=true;
        }
        if(pItem>=50 && pItem<60){
            m_key[i].heart=true;
        }
        if(pItem>=60 && pItem<90){
            m_key[i].bomb=true;
        }
    }

}

void GameKey::AddShoot(){
    int luckyOne=rand() % m_key.size() ;
    if(!m_key[luckyOne].jump){
        m_key[luckyOne].atomBomb=false;
        m_key[luckyOne].bomb=false;
        m_key[luckyOne].reveal=false;
        m_key[luckyOne].heart=false;
        m_key[luckyOne].jump=false;
        m_key[luckyOne].visible=false;
        m_key[luckyOne].shoot=true;
    }
    else{
        AddShoot();
    }
}
void GameKey::AddJump(){
    int luckyOne=rand() % m_key.size() ;
    if(!m_key[luckyOne].shoot){
        m_key[luckyOne].atomBomb=false;
        m_key[luckyOne].bomb=false;
        m_key[luckyOne].reveal=false;
        m_key[luckyOne].heart=false;
        m_key[luckyOne].visible=false;
        m_key[luckyOne].shoot=false;
        m_key[luckyOne].jump=true;
    }
    else{
        AddJump();
    }
}

void GameKey::Draw(sf::RenderWindow *App, sf::Vector2f camera){
    for(int i=0;i<m_key.size();i++){
        if(sf::Keyboard::IsKeyPressed( m_key[i].car)){
            if(m_key[i].shoot){
                if(m_player->m_flash) m_player->Shoot();
                else m_player->m_flash=true;

            }
            else if(m_key[i].jump){
                m_player->Jump();
            }
            else{
                if(m_key[i].state==0)m_player->Degat(1);

            }
            PressKey(i);
        }

        if(m_key[i].state==1){
            if(!(m_key[i].shoot||m_key[i].jump)){
                m_key[i].key.SetSubRect( sf::IntRect( m_key[i].rect.Left, m_key[i].rect.Top+125.f,m_key[i].rect.Width, m_key[i].rect.Height) ) ;
            }
            else{
                m_key[i].key.SetSubRect( sf::IntRect( m_key[i].rect.Left, m_key[i].rect.Top+250.f,m_key[i].rect.Width, m_key[i].rect.Height) ) ;
            }
        }

        m_key[i].key.SetPosition(camera.x-50+m_key[i].rect.Left*0.25,camera.y+23+m_key[i].rect.Top*0.25);
        App->Draw(m_key[i].key);
        if(m_key[i].state==1 || m_key[i].visible){
            if(m_key[i].shoot||m_key[i].jump){
                m_key[i].key.SetSubRect( sf::IntRect( m_key[i].rect.Left, m_key[i].rect.Top+250.f,m_key[i].rect.Width, m_key[i].rect.Height) ) ;
            }
            if(m_key[i].bomb){
                m_icon[i].setAnimRow(1);
                m_icon[i].SetPosition(camera.x-49+m_key[i].rect.Left*0.25,camera.y+4+23+m_key[i].rect.Top*0.25);
                App->Draw(m_icon[i]);
            }
            if(m_key[i].reveal){
                m_icon[i].setAnimRow(0);
                m_icon[i].SetPosition(camera.x-49+m_key[i].rect.Left*0.25,camera.y+4+23+m_key[i].rect.Top*0.25);
                App->Draw(m_icon[i]);
            }
            if(m_key[i].atomBomb){
                m_icon[i].setAnimRow(2);
                m_icon[i].SetPosition(camera.x-49+m_key[i].rect.Left*0.25,camera.y+4+23+m_key[i].rect.Top*0.25);
                App->Draw(m_icon[i]);
            }
            if(m_key[i].heart){
                m_icon[i].setAnimRow(3);
                m_icon[i].SetPosition(camera.x-49+m_key[i].rect.Left*0.25,camera.y+4+23+m_key[i].rect.Top*0.25);
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
