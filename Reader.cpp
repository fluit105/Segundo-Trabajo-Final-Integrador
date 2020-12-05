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
	printf("*-*-*-*-*-*-               READER                -*-*-*-*-*-*\n\n\n");
	printf("----------------------------------------------------------------------------\n\n\n\n");
	printf("[1] --> Ver Veterinarios.dat\n");
	printf("[2] --> Ver Usuarios.dat\n\n");
	printf("[3] --> Cerrar la aplicación.\n\n");
	printf("Ingrese una opción: ");
}

void menu();
void rVet();
void rUsr();
void exit();

struct veterin {
	char apeNom[50];
	int matricula;
	int dni;
	char telefono[15];
};

struct user {
	char usrID[10];
	char password[32];
	char name[50];
};

int opc=0;
int err=0;
FILE *vets;
FILE *users;

main() {
	toSpanish();
    menu();
}

void menu() {
	system("color 0f");
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
			if(opc == 1 || opc == 2 || opc == 3) {
				err = 0;
				if(opc == 1) rVet();
				if(opc == 2) rUsr();
				if(opc == 3) exit();
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

void rVet() {
	system("cls");
	vets = fopen("Veterinarios.dat","r+b");
	if (vets == NULL) {
		printf ("ERROR: No se pudo abrir el archivo");
	} else {
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-           Archivo de Veterinarios            -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		veterin vet;
		rewind(vets);
		fread(&vet, sizeof(veterin), 1, vets);
		while(!feof(vets)) {
			printf("Apellido y nombre: ");
			puts(vet.apeNom);
			printf("Matricula: %d", vet.matricula);
			printf("\nDNI: %d", vet.dni);
			printf("\nNumero de telefono: ");
			puts(vet.telefono);
			fread(&vet, sizeof(veterin), 1, vets);
			printf("\n\n");
		}
	}
	fclose(vets);
	printf("\n\n");
	system("pause");
	menu();
}

void rUsr() {
	system("cls");
	users = fopen("Usuarios.dat","r+b");
	if (users == NULL) {
		printf ("ERROR: No se pudo abrir el archivo");
	} else {
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-            Archivo de Usuarios             -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		user usr;
		rewind(users);
		fread(&usr, sizeof(user), 1, users);
		while(!feof(users)) {
			printf("ID de usuario: ");
			puts(usr.usrID);
			printf("Contraseña: ");
			puts(usr.password);
			printf("Apellido y Nombre: ");
			puts(usr.name);
			fread(&usr, sizeof(user), 1, users);
			printf("\n\n");
		}
	}
	fclose(users);
	printf("\n\n");
	system("pause");
	menu();
}

void exit() {
	system("cls");
	printf("\n\n\n\n---------------------------------------------------------------\n\n\n");
	printf("*-*-*-*-*-*-           Fin del Programa            -*-*-*-*-*-*\n\n\n");
	printf("---------------------------------------------------------------\n\n\n\n\n\n");
	system("pause");
}
