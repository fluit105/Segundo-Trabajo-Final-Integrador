#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <iostream>

void toSpanish() {
	setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
}

void printing() {
	printf("Modulo Consultorio Veterinario\n");
	printf("=========================\n\n");
	printf("1.- Iniciar Sesión\n");
	printf("2.- Visualizar Lista de Espera de Turnos (informe)\n");
	printf("3.- Registrar Evolución de la Mascota\n\n");
	printf("4.- Cerrar la aplicación.\n\n");
	printf("Ingrese una opción:\n");
}

void menu();

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
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-  Bienvenido a la consola de juegos del grupo 1JK6  -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		printf("**Puntaje Global: %d pts**", puntaje);
		printf("\n\n\n\nSeleccione la categoria de juego con el que le gustaria comenzar:\n\n");
		printf("[1] --> Juegos numericos\n[2] --> Juegos de letras\n\n[0] --> Salir");
		printf("\n\nSeleccionar: ");
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
			if(opc == 1 || opc == 2 || opc == 0) {
				err = 0;
				if(opc == 1) menuNumeros();
				if(opc == 2) menuLetras();
				if(opc == 0) terminar();
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
