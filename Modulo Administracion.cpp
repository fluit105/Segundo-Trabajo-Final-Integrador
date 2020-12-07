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
		opc = 500;
		
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
					int digits=0;
					for (int i = 0; i < strlen(usr.usrID); i++) {
						if(isupper(usr.usrID[i]) && isalpha(usr.usrID[i])) {
							uppers++;
						}
						if(isdigit(usr.usrID[i])) {
							digits++;
						}
					}
					int allow = 0;
					if(uppers < 2) {
						err = 1;
						system("cls");
						printf("\n\n\n**************************************************************************\n");
						printf("--> ERROR: El ID de usuario debe de tener al menos dos letras mayusculas\n");
						printf("**************************************************************************\n\n\n\n\n");
						system("pause");
						allow = 0;
						uppers = 0;
						digits = 0;
					} else {
						allow++;
					}
					if(digits > 3) {
						err = 1;
						system("cls");
						printf("\n\n\n**************************************************************************\n");
						printf("--> ERROR: El ID de usuario no puede tener más de 3 digitos\n");
						printf("**************************************************************************\n\n\n\n\n");
						system("pause");
						allow = 0;
						uppers = 0;
						digits = 0;
					} else {
						allow++;
					}
					if(allow == 2) {
						rewind(users);
						user aux;
						fread(&aux, sizeof(user), 1, users);
						while(!feof(users)) {
							if(strcmp(usr.usrID, aux.usrID) == 0) {
								err = 1;
								system("cls");
								printf("\n\n\n**************************************************************************\n");
								printf("--> ERROR: El ID de usuario ingresado ya existe\n");
								printf("**************************************************************************\n\n\n\n\n");
								system("pause");
							}
							fread(&aux, sizeof(user), 1, users);
						}
					}
					if(err == 0) {
						for (int i = 0; i < strlen(usr.usrID); i++) {
							if(isalnum(usr.usrID[i]) || isupper(usr.usrID[i]) || usr.usrID[i] == '+' || usr.usrID[i] == '-' || usr.usrID[i] == '/' || usr.usrID[i] == '*' || usr.usrID[i] == '?' || usr.usrID[i] == '¿' || usr.usrID[i] == '!' || usr.usrID[i] == '¡') {
								
							} else {
								err = 1;
								system("cls");
								printf("\n\n\n*******************************************************************************\n");
								printf("--> ERROR: El ID de usuario solo admite los siguiente simbolos: +,-,/,*,?,¿,!,¡\n");
								printf("*******************************************************************************\n\n\n\n\n");
								system("pause");
								break;
							}
						}
						
					}
				}
			}
		} while (err == 1);
		
		do {
			err = 0;
			system("cls");
			printf("\n\n----------------------------------------------------------------------------\n\n\n");
			printf("*-*-*-*-*-*-            Registro de nuevo Asistente             -*-*-*-*-*-*\n\n\n");
			printf("----------------------------------------------------------------------------\n\n\n\n");
			SetConsoleTextAttribute(hConsole, 15);
			printf("-->Ingrese una contraseña: <--\n\n");
			SetConsoleTextAttribute(hConsole, 8);
			printf("Formato\n");
			printf("-Entre 6 y 32 caracteres de largo\n");
			printf("-Poseer al menos una letra mayúscula y una minúscula\n");
			printf("-Poseer al menos un número\n");
			printf("-No tener más de tres letras y números en orden creciente consecutivo\n\n");
			SetConsoleTextAttribute(hConsole, 15);
			printf("-Entrada: ");
			_flushall();
			gets(usr.password);
		
			if(strlen(usr.password) > 32 || strlen(usr.password) < 6) {
				err = 1;
				system("cls");
				printf("\n\n\n**************************************************************************\n");
				printf("--> La contraseña debe tener un largo de entre 6 y 10 caracteres\n");
				printf("**************************************************************************\n\n\n\n\n");
				system("pause");
			} else {
					int uppers=0;
					int lowers=0;
					int digits=0;
					for (int i = 0; i < strlen(usr.password); i++) {
						if(isupper(usr.password[i]) && isalpha(usr.password[i])) {
							uppers++;
						}
						if(islower(usr.password[i]) && isalpha(usr.password[i])) {
							lowers++;
						}
						if(isdigit(usr.password[i])) {
							digits++;
						}
					}
			
					if(uppers == 0) {
						err = 1;
						system("cls");
						printf("\n\n\n**************************************************************************\n");
						printf("--> ERROR: La contraseña debe de tener al menos una letra mayúscula\n");
						printf("**************************************************************************\n\n\n\n\n");
						system("pause");
				
					}
					if(lowers == 0) {
						err = 1;
						system("cls");
						printf("\n\n\n**************************************************************************\n");
						printf("--> ERROR: La contraseña debe de tener al menos una letra minúscula\n");
						printf("**************************************************************************\n\n\n\n\n");
						system("pause");
					
					}
					if(digits == 0) {
						err = 1;
						system("cls");
						printf("\n\n\n**************************************************************************\n");
						printf("--> ERROR: La contraseña debe tener al menos 1 dígito\n");
						printf("**************************************************************************\n\n\n\n\n");
						system("pause");
			
					}
				}
			if(err == 0) {
				int numero[3];
				int aux;
				int count = 0;
				for(int i = 0; i < strlen(usr.password) ; i++) {
			  		if(isdigit(usr.password[i])) {
			  			numero[count] = usr.password[i];
			  			count++;
					}
				}

				if(numero[0] + 1 == numero[1]){
					if(numero[0] + 2 == numero[2]){
						if(numero[0] + 3 == numero[3]) {
							err = 1;
							system("cls");
							printf("\n\n\n**************************************************************************\n");
							printf("--> ERROR: La contraseña no debe tener mas de 3 digitos consecutivos.\n");
							printf("**************************************************************************\n\n\n\n\n");
							system("pause");
							
							numero[3] = 0;
						} else {break;}
					} else {break;}
				} else {break;}
			}
			if(err == 0){
				char letra[32];
				for(int i = 0; i < strlen(usr.password); i++) {
					if(isalpha(letra[i])){
						letra[i] = usr.password[i];
						letra[i] = toupper(letra[i]);
					}
					if(i > 0){
						if(letra[i-1] + 1 == letra[i]){
									err = 1;
									system("cls");
									printf("\n\n\n**************************************************************************\n");
									printf("--> ERROR: La contraseña no debe ser alfabeticamente consecutiva.\n");
									printf("**************************************************************************\n\n\n\n\n");
									system("pause");
									break;
						}
					}
				}
				for(int j = 0; j < strlen(usr.password); j++){
					if(usr.password[j] == '.' || usr.password[j] == ',' || usr.password[j] == ';' || usr.password[j] == '"'|| usr.password[j] == '(' || usr.password[j] == ')' || usr.password[j] == '¿' || usr.password[j] == '?'
		        || usr.password[j] == '¡' || usr.password[j] == '!' || usr.password[j] == '-' || usr.password[j] == ' '){
		        				err = 1;
								system("cls");
								printf("\n\n\n**************************************************************************\n");
								printf("--> ERROR: La contraseña no debe tener signos de puntuacion, ni espacios.\n");
								printf("**************************************************************************\n\n\n\n\n");
								system("pause");
					}	
				}
			}
		} while (err == 1);
		
		system("cls");
		printf("\n\n----------------------------------------------------------------------------\n\n\n");
		printf("*-*-*-*-*-*-            Registro de nuevo Asistente             -*-*-*-*-*-*\n\n\n");
		printf("----------------------------------------------------------------------------\n\n\n\n");
		SetConsoleTextAttribute(hConsole, 15);
		printf("--> Ingrese el apellido y nombre: ");
		_flushall();
		gets(usr.name); 
		fwrite(&usr, sizeof(user), 1, users);
	}
	fclose(users);
	printf("\n\n");
	system("pause");
	_flushall();
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
