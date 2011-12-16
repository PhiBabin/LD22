#ifndef GAMECONFIG_H
#define GAMECONFIG_H


struct imgAnim{
    sf::Texture img;
    int nbrCollum;
    int nbrLine;
};
struct mobType{
    int path;
    int x;
    int y;
    int width;
    int height;
};
class GameConfig
{
    public:
        GameConfig();
        static void LoadConfig();
        static sf::Color NbrToColor(int nbr);
        static int ColorToNbr(sf::Color myColor);
        ~GameConfig();

        static map<string,int> g_config;
        static map<string,imgAnim> g_imgManag;
        static map<int,mobType> g_mob;
        static map<string,sf::SoundBuffer> g_soundManag;
};

#endif // GAMECONFIG_H
