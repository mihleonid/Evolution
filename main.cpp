#include <iostream>
#include <SDL.h>
#include <thread>
#include <cstdlib>
#include <list>
#include <vector>
#include <chrono>
#include <list>
#include <stack>
#define byte uint8_t


enum Type { TDel, TFood, TEater, TWall, TEnergy, TBact, TGood, TFighter, TUniversal, TZed, TClean, TNeuro, TMove, TPaste, TCopy};
#include "cfv.h"
class MainWindow;
class GameObject;
class Food;
class Pools;
class Eater;
class Wall;
class Energy;
class Bact;
class Good;
class Fighter;
class Universal;
class Zed;
class Clean;
class Neuro;
#include "pools.h"

#include "go.h"
#include "mainwindow.h"
#include "field.h"
void GameObject::DeleteSelf(MainWindow* mw) {
    mw->Delete(x, y);
}
#include "food.h"
#include "energy.h"
#include "eater.h"
#include "bact.h"
#include "good.h"
#include "fighter.h"
#include "universal.h"
#include "zed.h"
#include "clean.h"
#include "neuro.h"
GO_STD_DELETE(Wall)
#include "poolsdef.h"

int main(int argc, char * argv[])
{
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    for (int i = 0; i < RND; i++) {
        rando[i] = rand();
    }
    //SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);//or HIGH_PRIORITY_CLASS
    MainWindow m;
    //FreeConsole();
    while (m.ex) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2241));
    }
    return 0;
}
