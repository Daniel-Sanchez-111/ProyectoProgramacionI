#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#define izquierda 75
#define derecha 77
#define arriba 72
#define abajo 80
#define esc 27
#define enter 13
using namespace std;
/*HANDLE cons;
cons = GetStdHandle(STD_OUTPUT_HANDLE); Solo una vez por funcion
SetConsoleTextAttribute(cons,14);
Con esto se modifica el color de los caracteres ponganlo antes de los caracteres con el color que quieren poner y despues del texto con el color blanco otra vez
*/
//Funcion para moverse
void gotoxy(int x, int y){
    HANDLE consola;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X =x;
    pos.Y = y;
    SetConsoleCursorPosition(consola,pos);

}

//Clase para crear la nave
class Nave
{
    int x,y;
    int vidas;
public:
    Nave(int x_, int y_,int vidas_): x(x_),y(y_),vidas(vidas_){}
    void crear();
    void borrador();
    void mover();
    void corazon();
    void muerte();
};


//Crea la nave
void Nave::crear()
{
    gotoxy(x,y);  printf("  %c",94);
    gotoxy(x,y+1);printf(" %c%c%c",40,238,41);
    gotoxy(x,y+2);printf("  %c",176);
}
//Borra el rastro de la nave
void Nave::borrador()
{
    gotoxy(x,y);printf("      ");
    gotoxy(x,y+1);printf("      ");
    gotoxy(x,y+2);printf("      ");

}
void Nave::mover()
{
    //Detecta si se ha presionado una tecla, sirve para moverse
        if(kbhit()){
            char tecla = getch();
            borrador();
            //Compara la variable tecla para determinar hacia donde se mueve flecha izquierda = izquierda flecha derecha =Derecha
            if(tecla==izquierda && x>5){
                x-=3;
            }
            if(tecla==derecha && x<69){
                x+=3;
            }
            if(tecla=='e'){
                vidas--;
            }
            crear();
        }
}
void Nave::corazon()
{
    HANDLE consola;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(10,2);printf("Vidas:");
    gotoxy(16,2);printf("     ");
    for(int i=0;i<vidas;i++){
        SetConsoleTextAttribute(consola,12);
        gotoxy(16+i,2);printf("%c",3);
    }
    SetConsoleTextAttribute(consola,15);

}
void Nave::muerte()
{
    if(vidas==0){
        borrador();
        gotoxy(x,y);  printf("   **  ");
        gotoxy(x,y+1);printf("  ****  ");
        gotoxy(x,y+2);printf("   **   ");
        Sleep(300);

        borrador();
        gotoxy(x,y);  printf("* ** *");
        gotoxy(x,y+1);printf(" **** ");
        gotoxy(x,y+2);printf("* ** *");
        Sleep(300);
        borrador();

    }
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
    gotoxy(64, 30); cout << "+";  gotoxy(45, 14); cout << "+";
    gotoxy(22, 27); cout << "+";  gotoxy(58, 24); cout << "+";
    gotoxy(8, 8); cout << "+";  gotoxy(58, 10); cout << "+";
    gotoxy(26, 15); cout << "+";  gotoxy(15, 13); cout << "+";
    gotoxy(30, 9); cout << "+";  gotoxy(50, 29); cout << "+";
    gotoxy(10, 27); cout << "+";  gotoxy(13, 17); cout << "+";
    gotoxy(19, 6); cout << "+";  gotoxy(29, 6); cout << "+";
    gotoxy(50, 4); cout << "+";  gotoxy(70, 7); cout << "+";
    gotoxy(73, 10); cout << "+";  gotoxy(69, 12); cout << "+";
    gotoxy(45, 11); cout << "+";  gotoxy(45, 20); cout << "+";
    gotoxy(55, 18); cout << "+";  gotoxy(57, 14); cout << "+";
    gotoxy(67, 17); cout << "+";  gotoxy(66, 21); cout << "+";
    gotoxy(72, 25); cout << "+";  gotoxy(39, 29); cout << "+";
    gotoxy(15, 30); cout << "+";  gotoxy(27, 31); cout << "+";
    gotoxy(34, 26); cout << "+";  gotoxy(28, 23); cout << "+";
    gotoxy(23, 19); cout << "+";
}

//Funcion para crear el menu
int menu(const char *titulo,const char *opciones[],int n)
{

    HANDLE cons;
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
    gotoxy(38,1);printf("Creditos\n");
    SetConsoleTextAttribute(cons,7);
    gotoxy(20,5);printf("Universidad Autonoma de Baja California Sur\n");
    gotoxy(17,7);printf("Departamento Academico de Sistemas Computacionales\n");
    gotoxy(35,10);printf("Moon Cresta\n");
    gotoxy(27,13);printf("Integrantes:\n");
    gotoxy(27,15);printf("-Cota Verdugo Isael\n");
    gotoxy(27,17);printf("-Juarez Sotelo Jesus Xavier\n");
    gotoxy(27,19);printf("-Sanchez Carrillo Daniel Eduardo\n");
    gotoxy(34,22);printf("Programacion I\n");
    gotoxy(29,25);printf("Prof. Jonathan Soto Munoz\n");
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal\n");
    gotoxy(26,30);printf("Presione otra tecla para salir\n");
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

void cancionMenu()
{
    PlaySound(TEXT("menu.wav"),NULL,SND_ASYNC);
}
void cancionCred()
{
    PlaySound(TEXT("cred.wav"),NULL,SND_ASYNC);
}
void cancionJuego()
{
    PlaySound(TEXT("juego.wav"),NULL,SND_ASYNC);
}

void instrucciones()
{


    HANDLE cons;
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    limpiarPantalla();
    SetConsoleTextAttribute(cons,14);
    gotoxy(35,1);printf("Instrucciones\n");
    SetConsoleTextAttribute(cons,7);
    gotoxy(8,5);printf("El objetivo principal de Moon Cresta es destruir a los alienigenas.\n");
    gotoxy(27,10);printf("Controles\n");
    gotoxy(27,12);printf("<- Moverse a la izquierda\n");
    gotoxy(27,14);printf("-> Moverse a la derecha\n");
    gotoxy(27,16);printf("[A] Disparar\n");
    gotoxy(27,18);printf("[ESC] Menu de pausa\n");
    gotoxy(20,28);printf("Presione ENTER para volver al menu principal\n");
    gotoxy(26,30);printf("Presione otra tecla para salir\n");
    estrellas();
}

int main()
{
    //Crear el objeto
    Nave ob(38,27,3);
    cursor_ocultar();
    const char *titulo = "Moon Cresta";
    const char *opciones[] = {"Jugar","Instrucciones","Creditos","Salir"};
    int n = 4;
    int tecla;
    int opcion;
    bool fin = false;
    bool men = true;
    while(men)
    {
    cancionMenu();
    opcion = menu(titulo,opciones,n);
    limpiarPantalla();
    PlaySound(NULL,NULL,0);
    switch(opcion){
        case 1:
            limites();
            cancionJuego();
            //Llamar a los metodos de la clase
            ob.crear();
            //Hace que el juego se siga ejecutando
            while(!fin){
                ob.corazon();
                ob.mover();
                ob.muerte();
                Sleep(30);

            }
        case 2:
            instrucciones();
            tecla=getch();
            if(tecla==enter)
            {
                break;
            }else
            {
                return 0;
            }
        case 3:
            creditos();
            cancionJuego();
            tecla=getch();
            if(tecla==enter)
            {
                break;
            }else
            {
                return 0;
            }
        case 4:
            return 0;
            break;

    }
    }


    return 0;
}
