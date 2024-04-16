#ifndef GAME_MANAGER
#define GAME_MANAGER
#include <fstream>
#include <iostream>

#include "Dungeon.h"
#include "Entity.h"
#include "GraphicManager.h"
#include "Item.h"

bool runMenu(Dungeon *dungeon);
Object *checkEvent(Player *);
void deleteObject(Object *, Player *);
#endif