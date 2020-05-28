#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <list>

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
};
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

    SetConsoleTextAttribute(cons, 1);
    gotoxy(x,y);  printf("  %c ",94);
    SetConsoleTextAttribute(cons, 8);
    gotoxy(x,y+1);printf(" %c%c%c ",40,238,41);
    SetConsoleTextAttribute(cons, 12);
    gotoxy(x,y+2);printf("  %c ",176);
    SetConsoleTextAttribute(cons, 15);
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
    if(salud==0){
        borrador();
        gotoxy(x,y);  printf("  **  ");
        gotoxy(x,y+1);printf(" **** ");
        gotoxy(x,y+2);printf("  **  ");
        Sleep(200);

        borrador();
        gotoxy(x,y);  printf("* ** *");
        gotoxy(x,y+1);printf(" **** ");
        gotoxy(x,y+2);printf("* ** *");
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
    if(x>=N.X()-3&& x<=N.X()+5 && y>=N.Y()&& y<=N.Y()+3)
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

    SetConsoleTextAttribute(cons, 10);
    gotoxy(x,y);printf("%c",60);
    SetConsoleTextAttribute(cons, 12);
    gotoxy(x+1,y);printf("%c",40);
    gotoxy(x+2,y);printf("%c",41);
    SetConsoleTextAttribute(cons, 10);
    gotoxy(x+3,y);printf("%c",62);
    SetConsoleTextAttribute(cons, 15);
}
void Jefe::mover()
{
    gotoxy(x,y);printf("     ");
    y+=0.7;
    if(y>32)
    {
        x = rand()%68+5;
        y=4;
    }
    crear();
}
void Jefe::borrar()
{
    gotoxy(x,y);printf("    ");
}

void Jefe::colision(class Nave &N)
{
    if(x>=N.X()-3&& x<=N.X()+5 && y>=N.Y()&& y<=N.Y()+3)
    {
        N.disminuirCorazon();
        borrar();
        N.crear();
        N.corazon();
        x = rand()%68+5;
        y=4;
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
    gotoxy(72, 25); cout << "+";  gotoxy(55, 33); cout << "+";
    gotoxy(15, 30); cout << "+";  gotoxy(27, 31); cout << "+";
    gotoxy(34, 26); cout << "+";
    gotoxy(23, 19); cout << "+";
}

//Funcion para crear el menu
int menu(const char *titulo,const char *opciones[],int n)
{
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    int opcionSeleccionada=1;
    int tecla;
    bool repetir = true;

    while(repetir)
    {

        system("cls");
        SetConsoleTextAttribute(cons,14);
        gotoxy(33,20+opcionSeleccionada);printf("-->");
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
        estrellas();
        do{
            tecla=getch();
        }while(tecla!=arriba && tecla!=abajo && tecla!=enter);

        switch(tecla)
        {
            case arriba:
                opcionSeleccionada--;
                if(opcionSeleccionada<1)
                {
                    opcionSeleccionada = n;
                }
                break;
            case abajo:
                opcionSeleccionada++;
                if(opcionSeleccionada>n)
                {
                    opcionSeleccionada=1;
                }
                break;
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
    system("cls");
    gotoxy(35,15);printf("PUNTUACION: %d",puntos);
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal");
}
void terminar(int puntos)
{
    system("cls");
    gotoxy(35,15);printf("Felicidades! Tu puntuacion es de: %d",puntos);
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal");
}
void cancionMenu()
{
    PlaySound(TEXT("menu.wav"),NULL,SND_ASYNC);
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
void instrucciones()
{



    cons = GetStdHandle(STD_OUTPUT_HANDLE);
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
    gotoxy(27,20);printf("[A] Disparar");
    gotoxy(27,22);printf("[ESC] Menu de pausa");
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal");
    gotoxy(26,30);printf("Presione otra tecla para salir");
    estrellas();
}

int main()
{
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
    int fase=1;
    int tecla;
    int opcion;
    bool fin = false;
    bool men = true;
    list<Disparo*> D;
    list<Disparo*>:: iterator i_Disparo;
    list<Alien*>A;
    list<Alien*>::iterator i_Alien;
    list<Jefe*>B;
    list<Jefe*>::iterator boss;
    for(int i=0;i<6;i++)
    {
        //Crea los objetos alien en una lista
        A.push_back(new Alien(rand()%66+4,rand()%5+4));
    }
    for(int i=0;i<1;i++)
    {
        //Crea los objetos alien en una lista
        B.push_back(new Jefe(rand()%66+4,rand()%5+4));
    }
    while(men)
    {
    //cancionMenu();
    opcion = menu(titulo,opciones,n);
    limpiarPantalla();
    PlaySound(NULL,NULL,0);
    Nave ob(38,27,3,3);

    switch(opcion){

        case 1:
            limites();
            puntos=0;
            fin=false;

            while(!fin){

                gotoxy(36,0);printf("Nivel %d",fase);
                if(kbhit())
                {
                //Crea el disparo
                if(GetAsyncKeyState(0x20)){
                    D.push_back(new Disparo(ob.X()+2, ob.Y()-1));
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
                //Controla el objeto alien


                ob.crear();
                ob.corazon();
                ob.mover();
                ob.muerte();
                if(fase==1)
                {
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                        (*i_Alien)->mover();
                        (*i_Alien)->colision(ob);
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

                               A.push_back(new Alien(rand()%66+4,4));
                               gotoxy((*i_Alien)->X(),(*i_Alien)->Y());printf("    ");
                               delete(*i_Alien);
                               i_Alien=A.erase(i_Alien);
                               puntos+=10;
                               destruidos++;
                           }
                    }
                    }
                    SetConsoleTextAttribute(cons,15);
                    nEnemigos=1;
                    Sleep(30);
                    gotoxy(5,34);printf("Enemigos Destruidos: %d/%d",destruidos,nEnemigos);
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        tecla=getch();
                        if(tecla==enter)
                        {
                            break;
                        }
                    }
                    if(destruidos==nEnemigos)
                    {

                        fase++;
                    }
                }
                if(fase==2)
                {
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                        (*i_Alien)->mover();
                        (*i_Alien)->colision(ob);
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
                               if(hit==2)
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
                    SetConsoleTextAttribute(cons,15);
                    nEnemigos=2;
                    Sleep(30);
                    gotoxy(5,34);printf("Enemigos Destruidos: %d/%d",destruidos,nEnemigos);
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        tecla=getch();
                        if(tecla==enter)
                        {
                            break;
                        }
                    }
                    if(destruidos==nEnemigos)
                    {
                        fase++;
                    }
                }
                if(fase==3)
                {
                    for(i_Alien=A.begin();i_Alien!=A.end();i_Alien++)
                    {
                        (*i_Alien)->mover();
                        (*i_Alien)->colision(ob);
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
                               if(hit==3)
                               {
                                   A.push_back(new Alien(rand()%66+4,4));
                                   gotoxy((*i_Alien)->X(),(*i_Alien)->Y());printf("    ");
                                   delete(*i_Alien);
                                   i_Alien=A.erase(i_Alien);
                                   puntos+=30;
                                   destruidos++;
                                   hit=0;
                               }

                           }
                    }
                    }
                    SetConsoleTextAttribute(cons,15);
                    nEnemigos=3;
                    Sleep(30);
                    gotoxy(5,34);printf("Enemigos Destruidos: %d/%d",destruidos,nEnemigos);
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        tecla=getch();
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
                    }
                }
                if(fase==4)
                {


                    for(boss=B.begin();boss!=B.end();boss++)
                {
                    (*boss)->mover();
                    (*boss)->colision(ob);
                 }
                 for(boss=B.begin();boss!=B.end();boss++)
                    {
                    for(i_Disparo=D.begin();i_Disparo!=D.end();i_Disparo++)
                    {
                        if((*boss)->X()==(*i_Disparo)->X()||((*boss)->X()+1==(*i_Disparo)->X()||(*boss)->X()+2==(*i_Disparo)->X()||(*boss)->X()+3==(*i_Disparo)->X())&&((*boss)->Y()+1==(*i_Disparo)->Y()|| (*boss)->Y()==(*i_Disparo)->Y()))
                           {
                               gotoxy((*i_Disparo)->X(),(*i_Disparo)->Y());printf(" ");
                               delete(*i_Disparo);
                               i_Disparo=D.erase(i_Disparo);
                               hit++;
                               if(hit==1)
                               {

                                   gotoxy((*boss)->X(),(*boss)->Y());printf("    ");
                                   delete(*boss);
                                   boss=B.erase(boss);
                                   puntos+=1000;
                                   destruidos++;
                                   hit=0;
                                   fin=true;
                                   final(puntos);
                                   //cancionFinal();
                                   Sleep(200);
                                   tecla=getch();
                                   //PlaySound(NULL, 0, 0);
                                   break;
                                    }

                               }

                           }
                    }

                    SetConsoleTextAttribute(cons,15);

                    Sleep(30);
                    gotoxy(5,34);printf("JEFE FINAL");
                    score(puntos);
                    if(ob.rVidas()==0)
                    {
                        fin=true;
                        final(puntos);
                        tecla=getch();
                        if(tecla==enter)
                        {
                            break;
                        }
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
