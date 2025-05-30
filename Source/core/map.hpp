#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <string>
#include "cell.hpp"
#include "player/player.hpp"

typedef Window Window;
class Map 
{
    bool MainWindowConnect{false};
public:
    std::string *MapName;
    Player &LinkedPlayer;
    Player *OtherPlayers;
    CellGrid *map;
    Window *MainWindow;

};


#endif //_MAP_HPP_