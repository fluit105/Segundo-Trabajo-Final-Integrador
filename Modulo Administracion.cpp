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

void menu();
void rVet();
void rAsi();
void atenV();
void exit();

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct veterin {
	char apeNom[50];
	int matricula;
	int dni;
	char telefono[15];
};

struct user {
	char usrID[50];
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
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-               Modulo Administracion                -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		printf("[1] --> Registrar Veterinario\n");
		printf("[2] --> Registrar Usuario Asistente\n");
		printf("[3] --> Atenciones por Veterinarios\n\n");
		printf("[4] --> Cerrar la aplicación.\n\n");
		printf("Ingrese una opción: ");
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
				if(opc == 1) rVet();
				if(opc == 2) rAsi();
				if(opc == 3) atenV();
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

void rVet() {
	system("cls");
	vets = fopen("Veterinarios.dat","a+b");
	if (vets == NULL) {
		printf ("ERROR: No se pudo abrir el archivo");
	} else {
		veterin vet;
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-           Registro de nuevo Veterinario            -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		
		printf("Ingrese apellido y nombre: ");
		_flushall();
		gets(vet.apeNom);
		printf("Ingrese la matricula: ");
		scanf("%d", &vet.matricula);
		printf("Ingrese el DNI: ");
		scanf("%d", &vet.dni); 
		printf("Ingrese el numero de telefono: ");
		_flushall();
		gets(vet.telefono);
		fwrite(&vet, sizeof(veterin), 1, vets);
	}
	fclose(vets);
	printf("\n\n");
	system("pause");
	menu();
}

void rAsi() {
	system("cls");
	users = fopen("Usuarios.dat","a+b");
	if (users == NULL) {
		printf ("ERROR: No se pudo abrir el archivo");
	} else {
		user usr;
		do {
			err = 0;
			system("cls");
			printf("\n\n----------------------------------------------------------------------------\n\n\n");
			printf("*-*-*-*-*-*-            Registro de nuevo Asistente             -*-*-*-*-*-*\n\n\n");
			printf("----------------------------------------------------------------------------\n\n\n\n");
			SetConsoleTextAttribute(hConsole, 15);
			printf("-->Ingrese el ID de usuario<--\n\n");
			SetConsoleTextAttribute(hConsole, 8);
			printf("Formato\n");
			printf("-No ser repetido\n");
			printf("-Entre 6 y 10 caracteres de largo\n");
			printf("-Empezar con letra minuscula\n");
			printf("-Poseer al menos dos letras mayusculas\n");
			printf("-No tener mas de 3 digitos\n\n");
			SetConsoleTextAttribute(hConsole, 15);
			printf("-Entrada: ");
			_flushall();
			gets(usr.usrID);
		
			if(strlen(usr.usrID) > 10 || strlen(usr.usrID) < 6) {
				err = 1;
				system("cls");
				printf("\n\n\n**************************************************************************\n");
				printf("--> ERROR: El ID de usuario debe tener un largo de entre 6 y 10 caracteres\n");
				printf("**************************************************************************\n\n\n\n\n");
				system("pause");
			} else {
				if(isupper(usr.usrID[0]) || isdigit(usr.usrID[0])) {
					err = 1;
					system("cls");
					printf("\n\n\n**************************************************************************\n");
					printf("--> ERROR: El ID de usuario debe empezar con una letra minuscula\n");
					printf("**************************************************************************\n\n\n\n\n");
					system("pause");
				} else {
					int uppers=0;
					for (int i = 0; i < 10; i++) {
						if(isupper(usr.usrID[i]) && isalpha(usr.usrID[i])) {
							uppers++;
						}
					}
					printf("%d", uppers);
					if(uppers < 2) {
						err = 1;
						system("cls");
						printf("\n\n\n**************************************************************************\n");
						printf("--> ERROR: El ID de usuario debe de tener al menos dos letras mayusculas\n");
						printf("**************************************************************************\n\n\n\n\n");
						system("pause");
					}
				}
			}
			
			
		
		} while (err == 1);
		
		
		printf("Ingrese una contraseña: ");
		scanf("%d", &usr.password);
		printf("Ingrese el apellido y nombre: ");
		scanf("%d", &usr.name); 
		fwrite(&usr, sizeof(user), 1, vets);
	}
	fclose(vets);
	printf("\n\n");
	system("pause");
	menu();
}

void atenV() {}

void exit() {
	system("cls");
	printf("\n\n\n\n---------------------------------------------------------------\n\n\n");
	printf("*-*-*-*-*-*-           Fin del Programa            -*-*-*-*-*-*\n\n\n");
	printf("---------------------------------------------------------------\n\n\n\n\n\n");
	system("pause");
}
