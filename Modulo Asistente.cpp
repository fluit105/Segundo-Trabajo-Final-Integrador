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
void inicS();
void regM();
void regT();
void lstA();
void exit();

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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

struct fecha {
	int dia;
	int mes;
	int year;
};

struct mascs {
	char apeNom[50];
	char domicilio[50];
	int dni;
	char localidad[50];
	fecha nacimiento;
	float peso;
	char telefono[15];
};

int opc=0;
int err=0;
bool logged = false;

FILE *vets;
FILE *users;
FILE *mascots;

user asis;

main() {
	toSpanish();
    menu();
}

void menu() {
	system("color 0f");
	srand(time(NULL));
	do {
		opc = 500;
		system("cls");
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-                 Modulo Asistente                   -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		if(!logged) {
			printf("Estado de Sesión: No iniciado\n\n\n\n");
		} else {
			printf("Estado de Sesión: Iniciado\n");
			printf("Usuario Actual: %s\n\n\n\n", asis.name);
		}
		printf("[1] --> Iniciar Sesión\n");
		printf("[2] --> Registrar Mascota\n");
		printf("[3] --> Registrar Turno\n");
		printf("[4] --> Listado de Atenciones por Veterinario y Fecha\n\n");
		printf("[5] --> Cerrar la aplicación.\n\n");
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
			if(opc == 1 || opc == 2 || opc == 3 || opc == 4 || opc == 5) {
				err = 0;
				if(opc == 1) inicS();
				if(opc == 2) regM();
				if(opc == 3) regT();
				if(opc == 4) lstA();
				if(opc == 5) exit();
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

void inicS() {
	system("cls");
	users = fopen("Usuarios.dat","r+b");
	if (users == NULL) {
		printf ("ERROR: No se pudo abrir el archivo");
	} else {
		do {
			system("cls");
			err = 0;
			user busc;
			printf("\n\n----------------------------------------------------------------------------\n\n\n");
			printf("*-*-*-*-*-*-                  Iniciar Sesion                    -*-*-*-*-*-*\n\n\n");
			printf("----------------------------------------------------------------------------\n\n\n\n");
			
			printf("Ingrese el ID de usuario: ");
			_flushall();
			gets(asis.usrID);
			
			rewind(users);
			fread(&busc, sizeof(user), 1, users);
			int match=0;
			user aux;
			while(!feof(users)) {
				if(strcmp(asis.usrID,busc.usrID) == 0) {
					match++;
					aux = busc;
				}
				fread(&busc, sizeof(user), 1, users);
			}
			if(match == 1) {
				int match2=0;
				system("cls");
				printf("\n\n----------------------------------------------------------------------------\n\n\n");
				printf("*-*-*-*-*-*-                 Iniciar Sesion                  -*-*-*-*-*-*\n\n\n");
				printf("----------------------------------------------------------------------------\n\n\n\n");
				
				printf("Ingrese la contraseña: ");
				_flushall();
				gets(asis.password);
				if(strcmp(asis.password,aux.password) == 0) {
					match2++;
				}
				if(match2 > 0) {
					asis = aux;
					system("cls");
					printf("\n\n----------------------------------------------------------------------------\n\n\n");
					printf("*-*-*-*-*-*-	Sesion iniciada correctamente	-*-*-*-*-*-*\n\n\n");
					printf("----------------------------------------------------------------------------\n\n\n\n\n");
					printf("------->     Bienvenido %s     <-------\n\n\n\n", asis.name);
					logged = true;
				} else {
					err = 1;
					system("cls");
					printf("\n\n\n**************************************************************************\n");
					printf("--> ERROR: Contraseña incorrecta\n");
					printf("**************************************************************************\n\n\n\n\n");
					system("pause");
				}
			} else {
				err = 1;
				system("cls");
				printf("\n\n\n**************************************************************************\n");
				printf("--> ERROR: ID de usuario no encontrado\n");
				printf("**************************************************************************\n\n\n\n\n");
				system("pause");
			}
		} while(err == 1);
	}
	fclose(users);
	printf("\n\n");
	system("pause");
	menu();
}

void regM() {
	
//////////	BORRAR!!!! ////////////////////
//logged = true;
//////////	BORRAR!!!! ////////////////////
	
	if(logged) {
		system("cls");
		mascots = fopen("Mascotas.dat","a+b");
		if (mascots == NULL) {
			printf ("ERROR: No se pudo abrir el archivo");
		} else {
			mascs masc;
			printf("\n\n----------------------------------------------------------------------------\n\n\n");
			printf("*-*-*-*-*-*-               Registrar una Mascota                -*-*-*-*-*-*\n\n\n");
			printf("----------------------------------------------------------------------------\n\n\n\n");
			
			printf("Ingrese nombre de la mascota y apellido del dueño: ");
			_flushall();
			gets(masc.apeNom);
//			printf("Ingrese la matricula: ");
//			scanf("%d", &vet.matricula);
//			printf("Ingrese el DNI: ");
//			scanf("%d", &vet.dni); 
//			printf("Ingrese el numero de telefono: ");
//			_flushall();
//			gets(vet.telefono);
//			fwrite(&vet, sizeof(veterin), 1, vets);
		}
		fclose(mascots);
		printf("\n\n");
		system("pause");
		menu();
	} else {
		system("cls");
		printf("\n\n\n**************************************************************************\n");
		printf("--> ERROR: Antes de realizar esta operación debe iniciar sesión\n");
		printf("**************************************************************************\n\n\n\n\n");
		system("pause");
		menu();
	}
}

void regT() {
	if(logged) {
		
	} else {
		system("cls");
		printf("\n\n\n**************************************************************************\n");
		printf("--> ERROR: Antes de realizar esta operación debe iniciar sesión\n");
		printf("**************************************************************************\n\n\n\n\n");
		system("pause");
		menu();
	}
}

void lstA() {
	if(logged) {
		
	} else {
		system("cls");
		printf("\n\n\n**************************************************************************\n");
		printf("--> ERROR: Antes de realizar esta operación debe iniciar sesión\n");
		printf("**************************************************************************\n\n\n\n\n");
		system("pause");
		menu();
	}
}

void exit() {
	system("cls");
	printf("\n\n\n\n---------------------------------------------------------------\n\n\n");
	printf("*-*-*-*-*-*-           Fin del Programa            -*-*-*-*-*-*\n\n\n");
	printf("---------------------------------------------------------------\n\n\n\n\n\n");
	system("pause");
}
