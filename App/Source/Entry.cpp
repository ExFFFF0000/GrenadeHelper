#include "Global.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    proc = new Memory();

    Render::Loop();
    return 0;
}