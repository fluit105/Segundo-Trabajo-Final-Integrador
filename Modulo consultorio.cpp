#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

void toSpanish() {
	setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
}

void printing() {
	printf("\n\n----------------------------------------------------------------------------\n\n\n");
	printf("*-*-*-*-*-*-                 Modulo Consultorio                 -*-*-*-*-*-*\n\n\n");
	printf("----------------------------------------------------------------------------\n\n\n\n");
	printf("[1] --> Iniciar Sesión\n");
	printf("[2] --> Visualizar Lista de Espera de Turnos (informe)\n");
	printf("[3] --> Registrar Evolución de la Mascota\n\n");
	printf("[4] --> Cerrar la aplicación.\n\n");
	printf("Ingrese una opción: ");
}

void menu();
void inicS();
void visL();
void evol();
void exit();

int opc=0;
int err=0;

main() {
	toSpanish();
    menu();
}

void menu() {
	system("color 0b");
	srand(time(NULL));
	do {
		system("cls");
		printing();
		err = 0;
		if(!(cin >> opc)) {
			cin.clear();
			cin.ignore(10000, '\n');
			err = 1;
			system("cls");
			printf("\n\n\n************************************************\n");
			printf("--> ERROR: Solo se permite el ingreso de numeros\n");
			printf("************************************************\n\n\n\n\n");
			system("pause");
		}
		if(err == 0) {
			if(opc == 1 || opc == 2 || opc == 3 || opc == 4) {
				err = 0;
				if(opc == 1) inicS();
				if(opc == 2) visL();
				if(opc == 3) visL();
				if(opc == 4) exit();
				opc = 500;
			} else {
				system("cls");
				printf("\n\n\n***********************************\n");
				printf("--> ERROR: Ingrese un numero valido\n");
				printf("***********************************\n\n\n\n\n");
				err = 1;
				system("pause");
			}
		}
	} while(err == 1);
}

void inicS() {}

void visL() {}

void evol() {}

void exit() {
	system("cls");
	printf("\n\n\n\n---------------------------------------------------------------\n\n\n");
	printf("*-*-*-*-*-*-           Fin del Programa            -*-*-*-*-*-*\n\n\n");
	printf("---------------------------------------------------------------\n\n\n\n\n\n");
	system("pause");
}
