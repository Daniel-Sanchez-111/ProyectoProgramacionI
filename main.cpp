#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <thread>

#define izquierda 75
#define derecha 77
#define arriba 72
#define abajo 80
#define enter 13

using namespace std;
void muerteJefeSound()
{
    PlaySound(TEXT("jefeM.wav"),NULL,SND_ASYNC);
}



int main()
{
    muerteJefeSound();
    return 0;
}
