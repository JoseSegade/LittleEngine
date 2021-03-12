#include <clocale>
#include <iostream>
#include "Engine.h"

int main(void)
{
    LittleEngine::Engine* e = new LittleEngine::Engine("Assignment 1", 1080, 720);
    e->init();
    e->run();
    return 0;
}