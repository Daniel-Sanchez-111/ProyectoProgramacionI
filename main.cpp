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
HANDLE cons;
int i=0;
//Funcion para moverse
void gotoxy(int x, int y){
    HANDLE consola;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X =x;
    pos.Y = y;
    SetConsoleCursorPosition(consola,pos);

}
//Clase para crear al alien

//Clase para crear la nave
void disparoSound()
{
    PlaySound(TEXT("disparo.wav"),NULL,SND_ASYNC);
}
void disparoSound2()
{
    PlaySound(TEXT("disparo4.wav"),NULL,SND_ASYNC);
}
void muertesound()
{
    PlaySound(TEXT("muerte.wav"),NULL,SND_ASYNC);
}
class Nave
{
    int x,y;
    int vidas;
    int salud;
public:
    Nave(int x_, int y_,int vidas_,int salud_): x(x_),y(y_),vidas(vidas_),salud(salud_){}
    int X();
    int Y();
    void crear();
    void borrador();
    void mover();
    void corazon();
    void disminuirCorazon();
    void muerte();
    int rVidas();
    int rSalud();
};
int Nave::rSalud()
{
    return salud;
}
int Nave::X()
{
    return x;
}
int Nave::Y()
{
    return y;
}

int Nave::rVidas()
{
    return vidas;
}

//Crea la nave
void Nave::crear()
{
    cons = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(cons, 8);
    gotoxy(x, y); printf("  %c", 30);
    SetConsoleTextAttribute(cons, 7);
    gotoxy(x, y+1); printf("%c   %c", 40, 41);
    SetConsoleTextAttribute(cons, 11);
    gotoxy(x+1, y+1); printf(" %c", 207);
    SetConsoleTextAttribute(cons, 8);
    gotoxy(x, y+2); printf("%c", 30);
    SetConsoleTextAttribute(cons, 15);
    gotoxy(x+1, y+2); printf("%c %c",190, 190);
    SetConsoleTextAttribute(cons, 8);
    gotoxy(x+4, y+2); printf("%c", 30);
    SetConsoleTextAttribute(cons, 12);
    gotoxy(x, y+3); printf(" %c %c  ",176, 176);
}
//Borra el rastro de la nave
void Nave::borrador()
{
    gotoxy(x-1,y);printf("       ");
    gotoxy(x-2,y+1);printf("        ");
    gotoxy(x-2,y+2);printf("        ");
    gotoxy(x-2,y+3);printf("        ");

}
void Nave::mover()
{
    //Detecta si se ha presionado una tecla, sirve para moverse
        if(kbhit()){
            char tecla = getch();
            borrador();
            //Compara la variable tecla para determinar hacia donde se mueve flecha izquierda = izquierda flecha derecha =Derecha
            if(tecla==izquierda && x>7){
                x-=3;
            }
            if(tecla==derecha && x<70){
                x+=3;
            }
            if(tecla=='e'){
                salud--;
            }
            crear();
        }
}
void Nave::corazon()
{
    HANDLE consola;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consola,10);
    gotoxy(65,2);printf("Vidas: %d",vidas);
    gotoxy(7,2);printf("Salud:");
    gotoxy(13,2);printf("     ");
    for(int i=0;i<salud;i++){
        SetConsoleTextAttribute(consola,12);
        gotoxy(13+i,2);printf("%c",3);
    }
    SetConsoleTextAttribute(consola,15);

}
void Nave::disminuirCorazon()
{
    salud--;
}
void Nave::muerte()
{
    SetConsoleTextAttribute(cons,15);
    if(salud<=0){
        borrador();
        gotoxy(x,y);  printf("  **  ");
        gotoxy(x,y+1);printf(" **** ");
        gotoxy(x,y+2);printf("  **  ");
        Sleep(200);

        borrador();
        gotoxy(x,y);  printf("* ** *");
        gotoxy(x,y+1);printf(" **** ");
        gotoxy(x,y+2);printf("* ** *");
        muertesound();
        Sleep(300);
        borrador();
        vidas--;
        salud=3;
        corazon();
        crear();
    }


}

class Alien
{
private:
    int x;
    float y;

public:
    Alien(int x_,float y_):x(x_),y(y_){}
    void crear();
    void mover();
    void colision(class Nave &N);
    void borrar();
    int X();
    int Y();
};
int Alien::X()
{
    return x;
}
int Alien::Y()
{
    return y;
}
void Alien::crear()
{
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(cons, 10);
    gotoxy(x,y);printf("%c",60);
    SetConsoleTextAttribute(cons, 12);
    gotoxy(x+1,y);printf("%c",40);
    gotoxy(x+2,y);printf("%c",41);
    SetConsoleTextAttribute(cons, 10);
    gotoxy(x+3,y);printf("%c",62);
    SetConsoleTextAttribute(cons, 15);
}
void Alien::mover()
{
    gotoxy(x,y);printf("     ");
    y+=0.7;
    if(y>32)
    {
        x = rand()%66+4;
        y=4;
    }
    crear();
}
void Alien::borrar()
{
    gotoxy(x,y);printf("    ");
}
void Alien::colision(class Nave &N)
{
    if(x>=N.X()-4&& x<=N.X()+5 && y>=N.Y()&& y<=N.Y()+4)
    {
        N.disminuirCorazon();
        borrar();
        N.crear();
        N.corazon();
        x = rand()%68+5;
        y=4;
    }
}
class Alien2
{
private:
    int x;
    float y;

public:
    Alien2(int x_,float y_):x(x_),y(y_){}
    void crear();
    void mover();
    void colision(class Nave &N);
    void borrar();
    int X();
    int Y();
};
int Alien2::X()
{
    return x;
}
int Alien2::Y()
{
    return y;
}
void Alien2::crear()
{
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(cons, 13);
    gotoxy(x,y);printf("%c",195);
    SetConsoleTextAttribute(cons, 11);
    gotoxy(x+1,y);printf("%c",91);
    gotoxy(x+2,y);printf("%c",93);
    SetConsoleTextAttribute(cons, 13);
    gotoxy(x+3,y);printf("%c",180);
    SetConsoleTextAttribute(cons, 15);
}
void Alien2::mover()
{
    gotoxy(x,y);printf("     ");
    y+=0.7;
    if(y>32)
    {
        x = rand()%66+4;
        y=4;
    }
    crear();
}
void Alien2::borrar()
{
    gotoxy(x,y);printf("    ");
}
void Alien2::colision(class Nave &N)
{
    if(x>=N.X()-4&& x<=N.X()+5 && y>=N.Y()&& y<=N.Y()+4)
    {
        N.disminuirCorazon();
        borrar();
        N.crear();
        N.corazon();
        x = rand()%68+5;
        y=4;
    }
}
class Alien3
{
private:
    int x;
    float y;

public:
    Alien3(int x_,float y_):x(x_),y(y_){}
    void crear();
    void mover();
    void colision(class Nave &N);
    void borrar();
    int X();
    int Y();
};
int Alien3::X()
{
    return x;
}
int Alien3::Y()
{
    return y;
}
void Alien3::crear()
{
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(cons, 14);
    gotoxy(x,y);printf("%c",174);
    SetConsoleTextAttribute(cons, 10);
    gotoxy(x+1,y);printf("%c",203);
    gotoxy(x+2,y);printf("%c",203);
    SetConsoleTextAttribute(cons, 14);
    gotoxy(x+3,y);printf("%c",175);
    SetConsoleTextAttribute(cons, 15);
}
void Alien3::mover()
{
    gotoxy(x,y);printf("     ");
    y+=0.7;
    if(y>32)
    {
        x = rand()%66+4;
        y=4;
    }
    crear();
}
void Alien3::borrar()
{
    gotoxy(x,y);printf("    ");
}
void Alien3::colision(class Nave &N)
{
    if(x>=N.X()-4&& x<=N.X()+5 && y>=N.Y()&& y<=N.Y()+4)
    {
        N.disminuirCorazon();
        borrar();
        N.crear();
        N.corazon();
        x = rand()%68+5;
        y=4;
    }
}
class Jefe
{
private:
    int x;
    float y;

public:
    Jefe(int x_,float y_):x(x_),y(y_){}
    void crear();
    void mover();
    void colision(class Nave &N);
    void borrar();
    void muerte();
    int X();
    int Y();
};
int Jefe::X()
{
    return x;
}
int Jefe::Y()
{
    return y;
}
void Jefe::crear()
{

    cons = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(cons, 8);
    gotoxy(x,y);  printf("                  ");
    gotoxy(x+1,y+1);printf("                ");
    gotoxy(x+2,y+2);printf("              ");
    gotoxy(x+3,y+3);printf("<|          |>");
    gotoxy(x+4,y+4);printf("<|        |>");
    gotoxy(x+5,y+5);printf("<|      |>");

    SetConsoleTextAttribute(cons, 2);
    gotoxy(x+2,y);printf("%c              %c",178,178);
    gotoxy(x+3,y+1);printf("%c     %c%c     %c",178,178,178,178);
    gotoxy(x+4,y+2);printf("%c    %c%c    %c",178,178,178,178);
    gotoxy(x+5,y+3);printf("%c   %c%c   %c",178,178,178,178);
    gotoxy(x+6,y+4);printf("%c  %c%c  %c",178,178,178,178);
    gotoxy(x+7,y+5);printf("%c%c%c%c%c%c",178,178,178,178,178,178);

    SetConsoleTextAttribute(cons, 6);
    gotoxy(x+2,y-1);printf("%c              %c",190,190);
    gotoxy(x+3,y);printf("%c     %c%c     %c",190,190,190,190);

    SetConsoleTextAttribute(cons, 12);
    gotoxy(x+2,y-2);printf("%c              %c",176,176);
    gotoxy(x+3,y-1);printf("%c     %c%c     %c",176,176,176,176);

    SetConsoleTextAttribute(cons, 11);
    gotoxy(x+7,y+6);printf("%c %c%c %c",30,30,30,30);
    gotoxy(x+9,y+7);printf("%c%c",30,30);

    SetConsoleTextAttribute(cons, 8);
    gotoxy(x+18,y); printf("][][][] ]");
    gotoxy(x+17,y+1); printf("][][][]] ]");
    gotoxy(x+16,y+2); printf("][][][][] ]");

    gotoxy(x-7,y); printf("[ [][][][");
    gotoxy(x-7,y+1); printf("[ [[][][][");
    gotoxy(x-7,y+2); printf("[ [][][][][");

    gotoxy(x+24,y+6); printf("[ ]");
    gotoxy(x-7,y+6); printf("[ ]");

    SetConsoleTextAttribute(cons, 14);
    gotoxy(x+25,y); printf("I");
    gotoxy(x+25,y+1); printf("I");
    gotoxy(x+25,y+2); printf("I");
    gotoxy(x+25,y+3); printf("I");
    gotoxy(x+25,y+4); printf("I");
    gotoxy(x+25,y+5); printf("I");

    gotoxy(x-6,y); printf("I");
    gotoxy(x-6,y+1); printf("I");
    gotoxy(x-6,y+2); printf("I");
    gotoxy(x-6,y+3); printf("I");
    gotoxy(x-6,y+4); printf("I");
    gotoxy(x-6,y+5); printf("I");

    SetConsoleTextAttribute(cons, 13);
    gotoxy(x+25,y+6); printf("I");
    gotoxy(x-6,y+6); printf("I");

}
void Jefe::mover()
{
    gotoxy(x-7,y-2);printf("                                  ");
    gotoxy(x-7,y-1);printf("                                  ");
    gotoxy(x-7,y);printf("                                  ");
    gotoxy(x-7,y+1);printf("                                  ");
    gotoxy(x-7,y+2);printf("                                  ");
    gotoxy(x-7,y+3);printf("                                  ");
    gotoxy(x-7,y+4);printf("                                  ");
    gotoxy(x-7,y+5);printf("                                  ");
    gotoxy(x-7,y+6);printf("                                  ");
    gotoxy(x-7,y+7);printf("                                  ");
    y+=0.8;
    if(y+6>32)
    {
        x = rand()%41+10;
        y=6;
    }
    crear();
}
void Jefe::borrar()
{
    gotoxy(x-7,y-2);printf("                                  ");
    gotoxy(x-7,y-1);printf("                                  ");
    gotoxy(x-7,y);printf("                                  ");
    gotoxy(x-7,y+1);printf("                                  ");
    gotoxy(x-7,y+2);printf("                                  ");
    gotoxy(x-7,y+3);printf("                                  ");
    gotoxy(x-7,y+4);printf("                                  ");
    gotoxy(x-7,y+5);printf("                                  ");
    gotoxy(x-7,y+6);printf("                                  ");
    gotoxy(x-7,y+7);printf("                                  ");
}

void Jefe::muerte()
{
    SetConsoleTextAttribute(cons, 14);
    gotoxy(x-7,y-2);printf("   ****    ****     ****     ****");
    Sleep(50);
    gotoxy(x-7,y-1);printf("    ****     ****     ****     ");
    Sleep(50);
    gotoxy(x-7,y+1);printf("  ***********        *************  ");
    Sleep(50);
    gotoxy(x-7,y+3);printf("    ******  ******  ******  ******   ");
    Sleep(50);
    gotoxy(x-7,y+5);printf("  ******  ******  ******  ******   ");
    Sleep(50);
    gotoxy(x-7,y+7);printf("  ***********        *************    ");
    Sleep(100);
    borrar();
    gotoxy(x-7,y-2);printf("*** **** **** **** **** ***");
    Sleep(50);
    gotoxy(x-7,y-1);printf("  *****  *****   *****   ");
    Sleep(50);
    gotoxy(x-7,y+1);printf("  *********  ******  ********** ");
    Sleep(50);
    gotoxy(x-7,y+3);printf("***   ******    ******  ****** ***");
    Sleep(50);
    gotoxy(x-7,y+5);printf("  ******  ******  ******  ******   ");
    Sleep(50);
    gotoxy(x-7,y+7);printf("  ***********   ***   *************  ");
    Sleep(400);
    borrar();
}

void Jefe::colision(class Nave &N)
{
    if(x+23>=N.X()-4&& x-7<=N.X()+5 && y+7>=N.Y()&& y+7<=N.Y()+4)
    {
        N.disminuirCorazon();
        borrar();
        N.crear();
        N.corazon();
        x = rand()%41+10;
        y=6;

    }
}
class Disparo{
    int x,y;
public:
    Disparo(int x_,int y_):x(x_),y(y_){}
    void mover();
    bool eliminar();
    int X();
    int Y();
};
void Disparo::mover()
{

    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(x,y);printf(" ");
    SetConsoleTextAttribute(cons,i);
    y--;
    gotoxy(x,y);printf("%c",221);
    if(i==15)
    {
        i=0;
    }
    i++;
    SetConsoleTextAttribute(cons,15);
}
bool Disparo::eliminar()
{
   if(y==4)
   {
        return true;
   }else
   {
       return false;
   }
}
int Disparo::X()
{
    return x;
}
int Disparo::Y()
{
    return y;
}
class DisparoF2{
    int x,y;
public:
    DisparoF2(int x_,int y_):x(x_),y(y_){}
    void mover();
    bool eliminar();
    int X();
    int Y();
};
void DisparoF2::mover()
{

    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(x,y);printf(" ");
    SetConsoleTextAttribute(cons,i);
    y--;
    gotoxy(x,y);printf("%c",221);
    if(i==15)
    {
        i=0;
    }
    i++;
    SetConsoleTextAttribute(cons,15);
}
bool DisparoF2::eliminar()
{
   if(y==4)
   {
        return true;
   }else
   {
       return false;
   }
}
int DisparoF2::X()
{
    return x;
}
int DisparoF2::Y()
{
    return y;
}
class DisparoF3{
    int x,y;
public:
    DisparoF3(int x_,int y_):x(x_),y(y_){}
    void mover();
    bool eliminar();
    int X();
    int Y();
};
void DisparoF3::mover()
{

    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(x,y);printf(" ");
    SetConsoleTextAttribute(cons,i);
    y--;
    gotoxy(x,y);printf("%c",221);
    if(i==15)
    {
        i=0;
    }
    i++;
    SetConsoleTextAttribute(cons,15);
}
bool DisparoF3::eliminar()
{
   if(y==4)
   {
        return true;
   }else
   {
       return false;
   }
}
int DisparoF3::X()
{
    return x;
}
int DisparoF3::Y()
{
    return y;
}
//Funcion para ocultar el parpadeo del cursor
void cursor_ocultar()
{
    HANDLE consola;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO c;
    c.dwSize=1;
    c.bVisible = false;
    SetConsoleCursorInfo(consola,&c);
}
void estrellas() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 15);
    gotoxy(42, 7); cout << "+";  gotoxy(13, 22); cout << "+";
    gotoxy(39, 14); cout << "+";
    gotoxy(22, 27); cout << "+";  gotoxy(58, 24); cout << "+";
    gotoxy(8, 8); cout << "+";
    gotoxy(26, 15); cout << "+";  gotoxy(15, 13); cout << "+";
    gotoxy(30, 9); cout << "+";  gotoxy(50, 29); cout << "+";
    gotoxy(10, 27); cout << "+";  gotoxy(13, 17); cout << "+";
    gotoxy(29, 6); cout << "+";
    gotoxy(70, 7); cout << "+";   gotoxy(43, 31); cout << "+";
    gotoxy(73, 10); cout << "+";  gotoxy(69, 12); cout << "+";
    gotoxy(45, 11); cout << "+";  gotoxy(45, 20); cout << "+";
    gotoxy(55, 18); cout << "+";  gotoxy(57, 14); cout << "+";
    gotoxy(67, 17); cout << "+";  gotoxy(66, 21); cout << "+";
    gotoxy(72, 25); cout << "+";
    gotoxy(15, 30); cout << "+";  gotoxy(27, 31); cout << "+";
    gotoxy(34, 26); cout << "+";
    gotoxy(23, 19); cout << "+";
}

void cancionM(){
    PlaySound(TEXT("menu.wav"),NULL,SND_ASYNC);
}
void seleccion(){
    Beep(500,100);
}
//Funcion para crear el menu
int menu(const char *titulo,const char *opciones[],int n)
{

    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    int opcionSeleccionada=1;
    int tecla;
    bool repetir = true;
    system("cls");
    while(repetir)
    {

        estrellas();
        SetConsoleTextAttribute(cons,14);
        gotoxy(33,20+opcionSeleccionada);printf("-->");
        gotoxy(33,19+opcionSeleccionada);printf("   ");
        gotoxy(4,5);printf("#     #                          #####                                    ");
        gotoxy(4,6);printf("##   ##  ####   ####  #    #    #     # #####  ######  ####  #####   ##   ");
        gotoxy(4,7);printf("# # # # #    # #    # ##   #    #       #    # #      #        #    #  #  ");
        gotoxy(4,8);printf("#  #  # #    # #    # # #  #    #       #    # #####   ####    #   #    #   ");
        gotoxy(4,9);printf("#     # #    # #    # #  # #    #       #####  #           #   #   ###### ");
        gotoxy(4,10);printf("#     # #    # #    # #   ##    #     # #   #  #      #    #   #   #    # ");
        gotoxy(4,11);printf("#     #  ####   ####  #    #     #####  #    # ######  ####    #   #    # ");
        SetConsoleTextAttribute(cons,7);
        for(int i=0;i<n;i++)
        {
            gotoxy(37,21+i);printf(opciones[i]);
        }

        do{
            tecla=getch();
        }while(tecla!=arriba && tecla!=abajo && tecla!=enter);

        switch(tecla)
        {
            case arriba:
                {
                    opcionSeleccionada--;
                    thread selecMenu(seleccion);
                    if(opcionSeleccionada<1)
                    {
                        gotoxy(33,21);printf("   ");
                        opcionSeleccionada = n;
                    }
                }

                break;
            case abajo:
                {


                opcionSeleccionada++;
                thread selecMenu(seleccion);
                if(opcionSeleccionada>n)
                {
                    gotoxy(33,24);printf("   ");
                    opcionSeleccionada=1;
                }
                if(selecMenu.joinable()) {
                    selecMenu.join();

                }
                break;
                }
            case enter:
                repetir=false;
                system("cls");
                break;
        }

    }


    SetConsoleTextAttribute(cons,15);
    return opcionSeleccionada;
}

void limpiarPantalla()
{
    gotoxy(35,5);printf("           ");
    gotoxy(37,21);printf("        ");
    printf("\n");
    gotoxy(37,22);printf("         ");
    printf("\n");
    gotoxy(37,23);printf("         ");
}

void creditos()
{
    HANDLE cons;
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    limpiarPantalla();
    SetConsoleTextAttribute(cons,14);
    gotoxy(23,1);printf("  ____              _ _ _            ");
    gotoxy(23,2);printf(" / ___|_ __ ___  __| (_) |_ ___  ___ ");
    gotoxy(23,3);printf("| |   | '__/ _ \\/ _` | | __/ _ \\/ __|");
    gotoxy(23,4);printf("| |___| | |  __/ (_| | | || (_) \\__ \\");
    gotoxy(23,5);printf(" \\____|_|  \\___|\\__,_|_|\\__\\___/|___/");
    SetConsoleTextAttribute(cons,7);
    gotoxy(20,13);printf("Universidad Autonoma de Baja California Sur");
    gotoxy(17,15);printf("Departamento Academico de Sistemas Computacionales");
    gotoxy(35,18);printf("Moon Cresta");
    gotoxy(27,21);printf("Integrantes:");
    gotoxy(27,23);printf("-Cota Verdugo Isael");
    gotoxy(27,25);printf("-Juarez Sotelo Jesus Xavier");
    gotoxy(27,27);printf("-Sanchez Carrillo Daniel Eduardo");
    gotoxy(34,29);printf("Programacion I");
    gotoxy(29,32);printf("Prof. Jonathan Soto Munoz");
    estrellas();
}

//Crea los bordes y esquinas
void limites()
{
    for(int i=2;i<78;i++){
        gotoxy(i,3);printf("%c",205);
        gotoxy(i,33);printf("%c",205);
    }
    for(int i=4;i<33;i++){
        gotoxy(2,i);printf("%c",186);
        gotoxy(77,i);printf("%c",186);
    }
    gotoxy(2,3);printf("%c",201);
    gotoxy(2,33);printf("%c",200);
    gotoxy(77,3);printf("%c",187);
    gotoxy(77,33);printf("%c",188);
}

void score(int puntos)
{
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(cons,10);
    gotoxy(33,2);printf("Puntuacion: ");
    SetConsoleTextAttribute(cons,15);
    printf("%d",puntos);
}
void final(int puntos)
{
    Sleep(100);
    system("cls");
    gotoxy(35,15);printf("PUNTUACION: %d",puntos);
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal");
    Sleep(200);
}
void terminar(int puntos)
{
    Sleep(100);
    system("cls");
    gotoxy(35,15);printf("Felicidades! Tu puntuacion es de: %d",puntos);
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal");
    Sleep(200);
}


void cancionCred()
{
    PlaySound(TEXT("CaI.wav"),NULL,SND_ASYNC);
}
void cancionJuego()
{
    PlaySound(TEXT("juego.wav"),NULL,SND_ASYNC);
}
void cancionInstrucciones()
{
    PlaySound(TEXT("CaI.wav"),NULL,SND_ASYNC);
}
void cancionFinal()
{
    PlaySound(TEXT("final.wav"),NULL,SND_ASYNC);
}

void muerteJefeSound()
{
    PlaySound(TEXT("jefeM.wav"),NULL,SND_ASYNC);
}

void instrucciones()
{

    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    estrellas();
    limpiarPantalla();
    SetConsoleTextAttribute(cons,14);
     gotoxy(1,1);printf(" _____              _");
    gotoxy(1,2);printf("|_   _|            | |                           (_)");
    gotoxy(1,3);printf("  | |   _ __   ___ | |_  _ __  _   _   ___   ___  _   ___   _ __    ___  ___ ");
    gotoxy(1,4);printf("  | |  |  _ \\ / __|| __||  __|| | | | / __| / __|| | / _ \\ |  _ \\  / _ \\/ __|");
    gotoxy(1,5);printf(" _| |_ | | | |\\__ \\| |_ | |   | |_| || (__ | (__ | || (_) || | | ||  __/\\__ \\");
    gotoxy(1,6);printf(" \\___/ |_| |_||___/ \\__||_|    \\__,_| \\___| \\___||_| \\___/ |_| |_| \\___||___/");
    SetConsoleTextAttribute(cons,7);
    gotoxy(8,10);printf("El objetivo principal de Moon Cresta es destruir a los alienigenas.");
    gotoxy(27,14);printf("Controles");
    gotoxy(27,16);printf("<- Moverse a la izquierda");
    gotoxy(27,18);printf("-> Moverse a la derecha");
    gotoxy(27,20);printf("[C] Disparar");
    gotoxy(27,22);printf("[ESPACIO] Disparar misiles");
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal");
    gotoxy(26,30);printf("Presione otra tecla para salir");

}
bool ajustarVentana(int ancho,int alto)
{
    _COORD Coordenada;
	Coordenada.X = ancho;
	Coordenada.Y = alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = ancho - 1;
	Rect.Bottom = alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tama�o
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tama�o de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}


int main()
{

    ajustarVentana(80,35);
    SetConsoleTitleA("Moon Cresta");
    const char *titulo = "Moon Cresta";
    const char *opciones[] = {"Jugar","Instrucciones","Creditos","Salir"};
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    cursor_ocultar();
    int puntos=0;
    int hit=0;
    int n = 4;
    int destruidos=0;
    int nEnemigos=0;
    int fase=0;
    int tecla;
    int opcion;

    bool fin = false;
    bool men = true;
    list<Disparo*> D;
    list<Disparo*>:: iterator i_Disparo;
    list<DisparoF2*> D2;
    list<DisparoF2*>:: iterator i_Disparo2;
    list<DisparoF3*> D3;
    list<DisparoF3*>:: iterator i_Disparo3;
    list<Alien*>A;
    list<Alien*>::iterator i_Alien;
    list<Alien2*>A2;
    list<Alien2*>::iterator i_Alien2;
    list<Alien3*>A3;
    list<Alien3*>::iterator i_Alien3;
    list<Jefe*>B;
    list<Jefe*>::iterator boss;
    for(int i=0;i<9;i++)
    {
        //Crea los objetos alien en una lista
        A.push_back(new Alien(rand()%66+4,rand()%5+4));
    }
    for(int i=0;i<9;i++)
    {
        //Crea los objetos alien en una lista
        A2.push_back(new Alien2(rand()%66+4,rand()%5+4));
    }
    for(int i=0;i<9;i++)
    {
        //Crea los objetos alien en una lista
        A3.push_back(new Alien3(rand()%66+4,rand()%5+4));
    }
    for(int i=0;i<1;i++)
    {
        B.push_back(new Jefe(rand()%66+4,rand()%5+4));
    }
    while(men)
    {
    thread menuS(cancionM);

    opcion = menu(titulo,opciones,n);
    limpiarPantalla();
    PlaySound(NULL,NULL,0);
    Nave ob(38,27,3,3);
    if(menuS.joinable()) {
        menuS.join();
    }

    switch(opcion){

        case 1:

            limites();
            puntos=0;
            fin=false;

            while(!fin){
                estrellas();
                //Controla el objeto alien
                ob.crear();
                ob.corazon();
                ob.mover();
                ob.muerte();
                score(puntos);
                if(fase==0)
                {
                    Sleep(2000);
                    fase++;
                }
                gotoxy(36,0);printf("Nivel %d",fase);
                if(fase==1)
                {
                    if(ob.rVidas()==3)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                    }
                    if(ob.rVidas()==2)
                    {
                       if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    if(ob.rVidas()==1)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                        if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo2)->mover();
                        if((*i_Disparo2)->eliminar())
                        {
                            gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                            delete(*i_Disparo2);
                            i_Disparo2=D2.erase(i_Disparo2);
                        }
                    }
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo3)->mover();
                        if((*i_Disparo3)->eliminar())
                        {
                            gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                            delete(*i_Disparo3);
                            i_Disparo3=D3.erase(i_Disparo3);
                        }
                    }
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        if((*i_Alien)->X()==(*i_Disparo2)->X()||((*i_Alien)->X()+1==(*i_Disparo2)->X()||(*i_Alien)->X()+2==(*i_Disparo2)->X()||(*i_Alien)->X()+3==(*i_Disparo2)->X())&&((*i_Alien)->Y()+1==(*i_Disparo2)->Y()|| (*i_Alien)->Y()==(*i_Disparo2)->Y()))
                           {
                               gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                               delete(*i_Disparo2);
                               i_Disparo2=D2.erase(i_Disparo2);
                               hit++;
                               if(hit==1)
                               {
                                   A.push_back(new Alien(rand()%66+4,4));
                                   gotoxy((*i_Alien)->X(),(*i_Alien)->Y());printf("    ");
                                   delete(*i_Alien);
                                   i_Alien=A.erase(i_Alien);
                                   puntos+=20;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        if((*i_Alien)->X()==(*i_Disparo3)->X()||((*i_Alien)->X()+1==(*i_Disparo3)->X()||(*i_Alien)->X()+2==(*i_Disparo3)->X()||(*i_Alien)->X()+3==(*i_Disparo3)->X())&&((*i_Alien)->Y()+1==(*i_Disparo3)->Y()|| (*i_Alien)->Y()==(*i_Disparo3)->Y()))
                           {
                               gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                               delete(*i_Disparo3);
                               i_Disparo3=D3.erase(i_Disparo3);
                               hit++;
                               if(hit==1)
                               {
                                   A.push_back(new Alien(rand()%66+4,4));
                                   gotoxy((*i_Alien)->X(),(*i_Alien)->Y());printf("    ");
                                   delete(*i_Alien);
                                   i_Alien=A.erase(i_Alien);
                                   puntos+=20;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo)->mover();
                        if((*i_Disparo)->eliminar())
                        {
                            gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                            delete(*i_Disparo);
                            i_Disparo=D.erase(i_Disparo);
                        }
                    }
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        if((*i_Alien)->X()==(*i_Disparo)->X()||((*i_Alien)->X()+1==(*i_Disparo)->X()||(*i_Alien)->X()+2==(*i_Disparo)->X()||(*i_Alien)->X()+3==(*i_Disparo)->X())&&((*i_Alien)->Y()+1==(*i_Disparo)->Y()|| (*i_Alien)->Y()==(*i_Disparo)->Y()))
                           {
                               gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                               delete(*i_Disparo);
                               i_Disparo=D.erase(i_Disparo);
                               hit++;
                               if(hit==1)
                               {
                                   A.push_back(new Alien(rand()%66+4,4));
                                   gotoxy((*i_Alien)->X(),(*i_Alien)->Y());printf("    ");
                                   delete(*i_Alien);
                                   i_Alien=A.erase(i_Alien);
                                   puntos+=10;
                                   destruidos++;
                                   hit=0;
                               }
                           }
                    }
                    }
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                        (*i_Alien)->mover();
                        (*i_Alien)->colision(ob);
                    }

                    SetConsoleTextAttribute(cons,15);
                    nEnemigos=10;
                    Sleep(30);
                    gotoxy(5,34);printf("Enemigos Destruidos: %d/%d",destruidos,nEnemigos);

                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        Sleep(100);
                        tecla=getch();
                        fase=0;
                        if(tecla==enter)
                        {
                            break;
                        }
                    }
                    if(destruidos==nEnemigos)
                    {
                        system("cls");
                        limites();
                        estrellas();
                        fase++;
                    }
                }
                if(fase==2)
                {
                //Crea el disparo
                    if(ob.rVidas()==3)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                    }
                    if(ob.rVidas()==2)
                    {
                       if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    if(ob.rVidas()==1)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                        if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo2)->mover();
                        if((*i_Disparo2)->eliminar())
                        {
                            gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                            delete(*i_Disparo2);
                            i_Disparo2=D2.erase(i_Disparo2);
                        }
                    }
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo3)->mover();
                        if((*i_Disparo3)->eliminar())
                        {
                            gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                            delete(*i_Disparo3);
                            i_Disparo3=D3.erase(i_Disparo3);
                        }
                    }
                    for(i_Alien2=A2.begin();i_Alien2!=A2.end();i_Alien2++)
                    {
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        if((*i_Alien2)->X()==(*i_Disparo2)->X()||((*i_Alien2)->X()+1==(*i_Disparo2)->X()||(*i_Alien2)->X()+2==(*i_Disparo2)->X()||(*i_Alien2)->X()+3==(*i_Disparo2)->X())&&((*i_Alien2)->Y()+1==(*i_Disparo2)->Y()|| (*i_Alien2)->Y()==(*i_Disparo2)->Y()))
                           {
                               gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                               delete(*i_Disparo2);
                               i_Disparo2=D2.erase(i_Disparo2);
                               hit++;
                               if(hit==3)
                               {
                                   A2.push_back(new Alien2(rand()%66+4,4));
                                   gotoxy((*i_Alien2)->X(),(*i_Alien2)->Y());printf("    ");
                                   delete(*i_Alien2);
                                   i_Alien2=A2.erase(i_Alien2);
                                   puntos+=20;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    for(i_Alien2=A2.begin();i_Alien2!=A2.end();i_Alien2++)
                    {
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        if((*i_Alien2)->X()==(*i_Disparo3)->X()||((*i_Alien2)->X()+1==(*i_Disparo3)->X()||(*i_Alien2)->X()+2==(*i_Disparo3)->X()||(*i_Alien2)->X()+3==(*i_Disparo3)->X())&&((*i_Alien2)->Y()+1==(*i_Disparo3)->Y()|| (*i_Alien2)->Y()==(*i_Disparo3)->Y()))
                           {
                               gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                               delete(*i_Disparo3);
                               i_Disparo3=D3.erase(i_Disparo3);
                               hit++;
                               if(hit==3)
                               {
                                   A2.push_back(new Alien2(rand()%66+4,4));
                                   gotoxy((*i_Alien2)->X(),(*i_Alien2)->Y());printf("    ");
                                   delete(*i_Alien2);
                                   i_Alien2=A2.erase(i_Alien2);
                                   puntos+=20;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo)->mover();
                        if((*i_Disparo)->eliminar())
                        {
                            gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                            delete(*i_Disparo);
                            i_Disparo=D.erase(i_Disparo);
                        }
                    }
                    for(i_Alien2=A2.begin();i_Alien2!=A2.end();i_Alien2++)
                    {
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        if((*i_Alien2)->X()==(*i_Disparo)->X()||((*i_Alien2)->X()+1==(*i_Disparo)->X()||(*i_Alien2)->X()+2==(*i_Disparo)->X()||(*i_Alien2)->X()+3==(*i_Disparo)->X())&&((*i_Alien2)->Y()+1==(*i_Disparo)->Y()|| (*i_Alien2)->Y()==(*i_Disparo)->Y()))
                           {
                               gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                               delete(*i_Disparo);
                               i_Disparo=D.erase(i_Disparo);
                               hit++;
                               if(hit==3)
                               {
                                   A2.push_back(new Alien2(rand()%66+4,4));
                                   gotoxy((*i_Alien2)->X(),(*i_Alien2)->Y());printf("    ");
                                   delete(*i_Alien2);
                                   i_Alien2=A2.erase(i_Alien2);
                                   puntos+=10;
                                   destruidos++;
                                   hit=0;
                               }
                           }
                    }
                    }
                    for(i_Alien2=A2.begin();i_Alien2!=A2.end();i_Alien2++)
                    {
                        (*i_Alien2)->mover();
                        (*i_Alien2)->colision(ob);
                    }
                    SetConsoleTextAttribute(cons,15);
                    nEnemigos=20;
                    Sleep(30);
                    gotoxy(5,34);printf("Enemigos Destruidos: %d/%d",destruidos,nEnemigos);
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        tecla=getch();
                        fase=0;
                        if(tecla==enter)
                        {
                            break;
                        }
                    }
                    if(destruidos==nEnemigos)
                    {
                        system("cls");
                        limites();
                        estrellas();
                        fase++;
                    }
                }
                if(fase==3)
                {
                    if(ob.rVidas()==3)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                    }
                    if(ob.rVidas()==2)
                    {
                       if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    if(ob.rVidas()==1)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                        if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo2)->mover();
                        if((*i_Disparo2)->eliminar())
                        {
                            gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                            delete(*i_Disparo2);
                            i_Disparo2=D2.erase(i_Disparo2);
                        }
                    }
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo3)->mover();
                        if((*i_Disparo3)->eliminar())
                        {
                            gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                            delete(*i_Disparo3);
                            i_Disparo3=D3.erase(i_Disparo3);
                        }
                    }
                    for(i_Alien3=A3.begin();i_Alien3!=A3.end();i_Alien3++)
                    {
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        if((*i_Alien3)->X()==(*i_Disparo2)->X()||((*i_Alien3)->X()+1==(*i_Disparo2)->X()||(*i_Alien3)->X()+2==(*i_Disparo2)->X()||(*i_Alien3)->X()+3==(*i_Disparo2)->X())&&((*i_Alien3)->Y()+1==(*i_Disparo2)->Y()|| (*i_Alien3)->Y()==(*i_Disparo2)->Y()))
                           {
                               gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                               delete(*i_Disparo2);
                               i_Disparo2=D2.erase(i_Disparo2);
                               hit++;
                               if(hit==6)
                               {
                                   A3.push_back(new Alien3(rand()%66+4,4));
                                   gotoxy((*i_Alien3)->X(),(*i_Alien3)->Y());printf("    ");
                                   delete(*i_Alien3);
                                   i_Alien3=A3.erase(i_Alien3);
                                   puntos+=20;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    for(i_Alien3=A3.begin();i_Alien3!=A3.end();i_Alien3++)
                    {
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        if((*i_Alien3)->X()==(*i_Disparo3)->X()||((*i_Alien3)->X()+1==(*i_Disparo3)->X()||(*i_Alien3)->X()+2==(*i_Disparo3)->X()||(*i_Alien3)->X()+3==(*i_Disparo3)->X())&&((*i_Alien3)->Y()+1==(*i_Disparo3)->Y()|| (*i_Alien3)->Y()==(*i_Disparo3)->Y()))
                           {
                               gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                               delete(*i_Disparo3);
                               i_Disparo3=D3.erase(i_Disparo3);
                               hit++;
                               if(hit==6)
                               {
                                   A3.push_back(new Alien3(rand()%66+4,4));
                                   gotoxy((*i_Alien3)->X(),(*i_Alien3)->Y());printf("    ");
                                   delete(*i_Alien3);
                                   i_Alien3=A3.erase(i_Alien3);
                                   puntos+=20;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo)->mover();
                        if((*i_Disparo)->eliminar())
                        {
                            gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                            delete(*i_Disparo);
                            i_Disparo=D.erase(i_Disparo);
                        }
                    }
                    for(i_Alien3=A3.begin();i_Alien3!=A3.end();i_Alien3++)
                    {
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        if((*i_Alien3)->X()==(*i_Disparo)->X()||((*i_Alien3)->X()+1==(*i_Disparo)->X()||(*i_Alien3)->X()+2==(*i_Disparo)->X()||(*i_Alien3)->X()+3==(*i_Disparo)->X())&&((*i_Alien3)->Y()+1==(*i_Disparo)->Y()|| (*i_Alien3)->Y()==(*i_Disparo)->Y()))
                           {
                               gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                               delete(*i_Disparo);
                               i_Disparo=D.erase(i_Disparo);
                               hit++;
                               if(hit==6)
                               {
                                   A3.push_back(new Alien3(rand()%66+4,4));
                                   gotoxy((*i_Alien3)->X(),(*i_Alien3)->Y());printf("    ");
                                   delete(*i_Alien3);
                                   i_Alien3=A3.erase(i_Alien3);
                                   puntos+=10;
                                   destruidos++;
                                   hit=0;
                               }
                           }
                    }
                    }
                    for(i_Alien3=A3.begin();i_Alien3!=A3.end();i_Alien3++)
                    {
                        (*i_Alien3)->mover();
                        (*i_Alien3)->colision(ob);
                    }

                    SetConsoleTextAttribute(cons,15);
                    nEnemigos=30;
                    Sleep(30);
                    gotoxy(5,34);printf("Enemigos Destruidos: %d/%d",destruidos,nEnemigos);
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        tecla=getch();
                        fase=0;
                        if(tecla==enter)
                        {
                            break;
                        }
                    }
                    if(destruidos==nEnemigos)
                    {
                        fase++;
                        system("cls");
                        limites();
                        estrellas();
                        hit=0;
                    }
                }
                if(fase==4)
                {
                    if(ob.rVidas()==3)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                    }
                    if(ob.rVidas()==2)
                    {
                       if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    if(ob.rVidas()==1)
                    {
                        if(GetAsyncKeyState(0x43)){
                            D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
                            disparoSound();
                        }
                        if(GetAsyncKeyState(0x20)){
                            D2.push_back(new DisparoF2(ob.X(), ob.Y()));
                            D3.push_back(new DisparoF3(ob.X()+4, ob.Y()));
                            disparoSound2();
                        }
                    }
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo)->mover();
                        if((*i_Disparo)->eliminar())
                        {
                            gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                            delete(*i_Disparo);
                            i_Disparo=D.erase(i_Disparo);
                        }
                    }
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo2)->mover();
                        if((*i_Disparo2)->eliminar())
                        {
                            gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                            delete(*i_Disparo2);
                            i_Disparo2=D2.erase(i_Disparo2);
                        }
                    }
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        //Controla el disparo y  lo elimina si y es igual a 4
                        (*i_Disparo3)->mover();
                        if((*i_Disparo3)->eliminar())
                        {
                            gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                            delete(*i_Disparo3);
                            i_Disparo3=D3.erase(i_Disparo3);
                        }
                    }
                    for(boss=B.begin();boss!=B.end();boss++)
                    {
                    for(i_Disparo2=D2.begin();i_Disparo2!=D2.end();i_Disparo2++)
                    {
                        if((*boss)->X()-3==(*i_Disparo2)->X()||((*boss)->X()-2==(*i_Disparo2)->X()||(*boss)->X()-1==(*i_Disparo2)->X()||(*boss)->X()==(*i_Disparo2)->X()||(*boss)->X()+1==(*i_Disparo2)->X()||(*boss)->X()+2==(*i_Disparo2)->X()||(*boss)->X()+3==(*i_Disparo2)->X()||(*boss)->X()+4==(*i_Disparo2)->X()||(*boss)->X()+5==(*i_Disparo2)->X()||(*boss)->X()+6==(*i_Disparo2)->X()||(*boss)->X()+7==(*i_Disparo2)->X()||(*boss)->X()+8==(*i_Disparo2)->X()||(*boss)->X()+9==(*i_Disparo2)->X()||(*boss)->X()+10==(*i_Disparo2)->X()||(*boss)->X()+11==(*i_Disparo2)->X()||(*boss)->X()+12==(*i_Disparo2)->X()||(*boss)->X()+13==(*i_Disparo2)->X()||(*boss)->X()+14==(*i_Disparo2)->X()||(*boss)->X()+15==(*i_Disparo2)->X()||(*boss)->X()+16==(*i_Disparo2)->X()||(*boss)->X()+17==(*i_Disparo2)->X()||(*boss)->X()+18==(*i_Disparo2)->X()||(*boss)->X()+19==(*i_Disparo2)->X()||(*boss)->X()+20==(*i_Disparo2)->X()||(*boss)->X()+21==(*i_Disparo2)->X()||(*boss)->X()+22==(*i_Disparo2)->X()||(*boss)->X()+23==(*i_Disparo2)->X())&&((*boss)->Y()+7==(*i_Disparo2)->Y()|| (*boss)->Y()+5==(*i_Disparo2)->Y()))
                           {
                               gotoxy((*i_Disparo2)->X(),(*i_Disparo2)->Y());printf(" ");
                               delete(*i_Disparo2);
                               i_Disparo2=D2.erase(i_Disparo2);
                               hit++;
                               if(hit>=30)
                               {
                                   (*boss)->muerte();
                                   muerteJefeSound();
                                   delete(*boss);
                                   boss=B.erase(boss);
                                   puntos+=2000;
                                   hit=0;
                                   fin=true;
                                   Sleep(200);
                                   final(puntos);
                                   cancionFinal();
                                   tecla=getch();
                                   PlaySound(NULL, 0, 0);
                                   fase=0;
                                   break;
                               }

                           }
                    }
                    }
                    for(boss=B.begin();boss!=B.end();boss++)
                    {
                    for(i_Disparo3=D3.begin();i_Disparo3!=D3.end();i_Disparo3++)
                    {
                        if((*boss)->X()-3==(*i_Disparo3)->X()||((*boss)->X()-2==(*i_Disparo3)->X()||(*boss)->X()-1==(*i_Disparo3)->X()||(*boss)->X()==(*i_Disparo3)->X()||(*boss)->X()+1==(*i_Disparo3)->X()||(*boss)->X()+2==(*i_Disparo3)->X()||(*boss)->X()+3==(*i_Disparo3)->X()||(*boss)->X()+4==(*i_Disparo3)->X()||(*boss)->X()+5==(*i_Disparo3)->X()||(*boss)->X()+6==(*i_Disparo3)->X()||(*boss)->X()+7==(*i_Disparo3)->X()||(*boss)->X()+8==(*i_Disparo3)->X()||(*boss)->X()+9==(*i_Disparo3)->X()||(*boss)->X()+10==(*i_Disparo3)->X()||(*boss)->X()+11==(*i_Disparo3)->X()||(*boss)->X()+12==(*i_Disparo3)->X()||(*boss)->X()+13==(*i_Disparo3)->X()||(*boss)->X()+14==(*i_Disparo3)->X()||(*boss)->X()+15==(*i_Disparo3)->X()||(*boss)->X()+16==(*i_Disparo3)->X()||(*boss)->X()+17==(*i_Disparo3)->X()||(*boss)->X()+18==(*i_Disparo3)->X()||(*boss)->X()+19==(*i_Disparo3)->X()||(*boss)->X()+20==(*i_Disparo3)->X()||(*boss)->X()+21==(*i_Disparo3)->X()||(*boss)->X()+22==(*i_Disparo3)->X()||(*boss)->X()+23==(*i_Disparo3)->X())&&((*boss)->Y()+7==(*i_Disparo3)->Y()|| (*boss)->Y()+5==(*i_Disparo3)->Y()))
                           {
                               gotoxy((*i_Disparo3)->X(),(*i_Disparo3)->Y());printf(" ");
                               delete(*i_Disparo3);
                               i_Disparo3=D3.erase(i_Disparo3);
                               hit++;
                               if(hit>=30)
                               {
                                   (*boss)->muerte();
                                   muerteJefeSound();
                                   delete(*boss);
                                   boss=B.erase(boss);
                                   puntos+=2000;
                                   hit=0;
                                   fin=true;
                                   Sleep(200);
                                   final(puntos);
                                   cancionFinal();
                                   tecla=getch();
                                   PlaySound(NULL, 0, 0);
                                   fase=0;
                                   break;
                               }

                           }
                    }
                    }

                    for(boss=B.begin();boss!=B.end();boss++)
                    {
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        if((*boss)->X()-3==(*i_Disparo)->X()||((*boss)->X()-2==(*i_Disparo)->X()||(*boss)->X()-1==(*i_Disparo)->X()||(*boss)->X()==(*i_Disparo)->X()||(*boss)->X()+1==(*i_Disparo)->X()||(*boss)->X()+2==(*i_Disparo)->X()||(*boss)->X()+3==(*i_Disparo)->X()||(*boss)->X()+4==(*i_Disparo)->X()||(*boss)->X()+5==(*i_Disparo)->X()||(*boss)->X()+6==(*i_Disparo)->X()||(*boss)->X()+7==(*i_Disparo)->X()||(*boss)->X()+8==(*i_Disparo)->X()||(*boss)->X()+9==(*i_Disparo)->X()||(*boss)->X()+10==(*i_Disparo)->X()||(*boss)->X()+11==(*i_Disparo)->X()||(*boss)->X()+12==(*i_Disparo)->X()||(*boss)->X()+13==(*i_Disparo)->X()||(*boss)->X()+14==(*i_Disparo)->X()||(*boss)->X()+15==(*i_Disparo)->X()||(*boss)->X()+16==(*i_Disparo)->X()||(*boss)->X()+17==(*i_Disparo)->X()||(*boss)->X()+18==(*i_Disparo)->X()||(*boss)->X()+19==(*i_Disparo)->X()||(*boss)->X()+20==(*i_Disparo)->X()||(*boss)->X()+21==(*i_Disparo)->X()||(*boss)->X()+22==(*i_Disparo)->X()||(*boss)->X()+23==(*i_Disparo)->X())&&((*boss)->Y()+7==(*i_Disparo)->Y()|| (*boss)->Y()+5==(*i_Disparo)->Y()))

                           {
                               gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                               delete(*i_Disparo);
                               i_Disparo=D.erase(i_Disparo);
                               hit++;
                               if(hit>=30)
                               {
                                   (*boss)->muerte();
                                   muerteJefeSound();
                                   delete(*boss);
                                   boss=B.erase(boss);
                                   puntos+=2000;
                                   hit=0;
                                   fin=true;
                                   Sleep(200);
                                   final(puntos);
                                   cancionFinal();
                                   tecla=getch();
                                   PlaySound(NULL, 0, 0);
                                   fase=0;
                                   break;
                               }
                           }
                    }
                    }
                    for(boss=B.begin();boss!=B.end();boss++)
                    {
                        (*boss)->mover();
                        (*boss)->colision(ob);
                    }
                    SetConsoleTextAttribute(cons,15);

                    Sleep(30);
                    gotoxy(5,34);printf("JEFE FINAL");
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        Sleep(200);
                        tecla=getch();
                        break;

                    }
                }
                }


            break;
        case 2:
            instrucciones();
            //cancionInstrucciones();
            tecla=getch();
            if(tecla==enter)
            {
                break;
            }else
            {
                return 0;
            }
            break;
        case 3:
            creditos();
            //cancionCred();
            tecla=getch();
            if(tecla==enter)
            {

                break;
            }else
            {
                return 0;
            }
            break;
        case 4:
            return 0;
            break;

    }
    }


    return 0;
}
