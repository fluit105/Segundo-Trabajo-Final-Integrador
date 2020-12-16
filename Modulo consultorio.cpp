#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;


struct fecha {
  int dia;
  int mes;
  int year;
};

struct veterin {
  char apeNom[50];
  int matricula;
  int dni;
  char telefono[15];
  int rank;
};

struct turno {
  int matricula_Vet;
  fecha fecha_Turno;
  int dni;
  char detalle[380];
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

struct user {
  char usrID[10];
  char password[32];
  char name[50];
};

void toSpanish() {
  setlocale(LC_ALL, "spanish");
  SetConsoleCP(1252);
  SetConsoleOutputCP(1252);
}

int opc = 0;
int err = 0;








bool logged = false;







veterin global;

FILE *vets;
FILE *users;
FILE *mascots;
FILE *turnos;

FILE *vetTemp;
FILE *turTemp;

veterin veterinario;

void menu();
void inicS();
void visL();
void evol();
void exit();

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
	  printf("*-*-*-*-*-*-                 Modulo Consultorio                 -*-*-*-*-*-*\n\n\n");
	  printf("----------------------------------------------------------------------------\n\n\n\n");
	  if (!logged) {
      printf("Estado de Sesión: No iniciado\n\n\n\n");
    } else {
      printf("Estado de Sesión: Iniciado\n");
      printf("Usuario Actual: %s\n\n\n\n", global.apeNom);
    }
	  printf("[1] --> Iniciar Sesión\n");
	  printf("[2] --> Visualizar Lista de Espera de Turnos (informe)\n");
	  printf("[3] --> Registrar Evolución de la Mascota\n\n");
	  printf("[4] --> Cerrar la aplicación.\n\n");
	  printf("Ingrese una opción: ");
    
    err = 0;
    if (!(cin >> opc)) {
      cin.clear();
      cin.ignore(10000, '\n');
      err = 1;
      system("cls");
      printf("\n\n\n************************************************\n");
      printf("--> ERROR: Solo se permite el ingreso de numeros\n");
      printf("************************************************\n\n\n\n\n");
      system("pause");
    }
    if (err == 0) {
      if (opc == 1 || opc == 2 || opc == 3 || opc == 4) {
        err = 0;
        if (opc == 1) inicS();
        if (opc == 2) visL();
        if (opc == 3) evol();
        if (opc == 4) exit();
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
  } while (err == 1);
}

void inicS() {
  system("cls");
  vets = fopen("Veterinarios.dat", "r+b");
  if (vets == NULL) {
    printf ("ERROR: No se pudo abrir el archivo Veterinarios.dat");
  } else {
    do {
      system("cls");
      err = 0;
      veterin busc;
      printf("\n\n----------------------------------------------------------------------------\n\n\n");
      printf("*-*-*-*-*-*-                  Iniciar Sesion                    -*-*-*-*-*-*\n\n\n");
      printf("----------------------------------------------------------------------------\n\n\n\n");

      printf("Ingrese su nombre: ");
      _flushall();
      gets(veterinario.apeNom);

      rewind(vets);
      fread(&busc, sizeof(veterin), 1, vets);
      int match = 0;
      veterin aux;
      while (!feof(vets)) {
        if (strcmp(veterinario.apeNom, busc.apeNom) == 0) {
          match++;
          aux = busc;
        }
        fread(&busc, sizeof(veterin), 1, vets);
      }
      if (match == 1) {
        int match2 = 0;
        system("cls");
        printf("\n\n----------------------------------------------------------------------------\n\n\n");
        printf("*-*-*-*-*-*-                 Iniciar Sesion                  -*-*-*-*-*-*\n\n\n");
        printf("----------------------------------------------------------------------------\n\n\n\n");

        printf("Ingrese la matricula: ");

        scanf("%d", &veterinario.matricula);
        if (veterinario.matricula == aux.matricula) {
          match2++;
        }
        if (match2 > 0) {
          veterinario = aux;
          system("cls");
          printf("\n\n----------------------------------------------------------------------------\n\n\n");
          printf("*-*-*-*-*-*-  Sesion iniciada correctamente -*-*-*-*-*-*\n\n\n");
          printf("----------------------------------------------------------------------------\n\n\n\n\n");
          printf("------->     Bienvenido %s     <-------\n\n\n\n", veterinario.apeNom);
          logged = true;
          global = veterinario;
        } else {
          err = 1;
          system("cls");
          printf("\n\n\n**************************************************************************\n");
          printf("--> ERROR: Matricula inexistente\n");
          printf("**************************************************************************\n\n\n\n\n");
          system("pause");
        }
      } else {
        err = 1;
        system("cls");
        printf("\n\n\n**************************************************************************\n");
        printf("--> ERROR: Nombre no encontrado\n");
        printf("**************************************************************************\n\n\n\n\n");
        system("pause");
      }
    } while (err == 1);
  }
  fclose(users);
  printf("\n\n");
  system("pause");
  menu();
}

void visL() {
	
	if (logged) {
	  system("cls");
		turnos = fopen("Turnos.dat","r+b");
		if (turnos == NULL) {
			printf ("ERROR: No se pudo abrir el archivo");
		} else {
			printf("\n\n----------------------------------------------------------------------------\n\n\n");
			printf("*-*-*-*-*-*-             Archivo de Turnos              -*-*-*-*-*-*\n\n\n");
			printf("----------------------------------------------------------------------------\n\n\n\n");
			turno trn;
			rewind(turnos);
			int s=0;
			fread(&trn, sizeof(turno), 1, turnos);
			while(!feof(turnos)) {
				printf("Matricula del veterinario: ");
				printf("%d", trn.matricula_Vet);
				printf("\nFecha del turno: %d/%d/%d", trn.fecha_Turno.dia, trn.fecha_Turno.mes, trn.fecha_Turno.year);
				printf("\nDNI del dueño: %d", trn.dni);
				printf("\nDetelle de la visita: ");
				puts(trn.detalle);
				fread(&trn, sizeof(turno), 1, turnos);
				printf("\n\n");
			}
		}
		fclose(turnos);
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
  system("pause");
  fclose(turnos);
  menu();
}

void evol() {

  int archs = 0;

  if (logged) {
    turnos = fopen("Turnos.dat", "a+b");
    vets = fopen("Veterinarios.dat", "r+b");
    mascots = fopen("Mascotas.dat", "r+b");
    if (vets == NULL) {
      printf ("ERROR: No se pudo abrir el archivo Veterinarios.dat");
    } else {
      archs++;
    }
    if (turnos == NULL) {
      printf ("ERROR: No se pudo abrir el archivo Turnos.dat");
    } else {
      archs++;
    }
    if (mascots == NULL) {
      printf ("ERROR: No se pudo abrir el archivo Mascotas.dat");
    } else {
      archs++;
    }
    if (archs == 3) {
      do {
      	err = 0;
        int match = 0;
        int match2 = 0;
        int i = 0;
        int j = 0;
        turno turns;
        veterin vet;
        mascs masco;
        mascs busc;

        system("cls");
        printf("\n\n----------------------------------------------------------------------------\n\n\n");
        printf("*-*-*-*-*-*-               Registrar evolución               -*-*-*-*-*-*\n\n\n");
        printf("----------------------------------------------------------------------------\n\n\n\n");
        rewind(vets);
        fread(&vet, sizeof(veterin), 1, vets);
        printf("Veterinarios: \n");
        while (!feof(vets)) {
          printf("\n--> Apellido y nombre: ");
          puts(vet.apeNom);
          printf("--> Matricula: %d\n", vet.matricula);
          fread(&vet, sizeof(veterin), 1, vets);
        }
        printf("\nIngrese la matricula del veterinario: ");
        int mat;
        scanf("%d", &mat);
        turns.matricula_Vet = mat;
        rewind(vets);
        while (!feof(vets)) {
          if (turns.matricula_Vet == vet.matricula) {
            match++;
          }
          fread(&vet, sizeof(veterin), 1, vets);
        }

        if (match > 0) {
          system("cls");
					printf("\n\n----------------------------------------------------------------------------\n\n\n");
					printf("*-*-*-*-*-*-               Registrar evolución               -*-*-*-*-*-*\n\n\n");
      	  printf("----------------------------------------------------------------------------\n\n\n\n");
          rewind(mascots);
          fread(&masco, sizeof(mascs), 1, mascots);
          while (!feof(mascots)) {
            i++;
            fread(&masco, sizeof(mascs), 1, mascots);
          }
          mascs aux[i];
          rewind(mascots);
          fread(&masco, sizeof(mascs), 1, mascots);
          while (!feof(vets)) {
            aux[j] = masco;
            j++;
            fread(&masco, sizeof(mascs), 1, mascots);
          }
          printf("Mascotas: \n");
          while (!feof(mascots)) {
            printf("\n--> Apellido y nombre: ");
            puts(masco.apeNom);
            printf("--> Dni del dueño: %d\n\n", masco.dni);
            fread(&masco, sizeof(mascs), 1, mascots);
          }
          busc = masco;
          
          mascs temp;
          printf("\nIngrese el DNI del dueño: ");
          int dniA;
          scanf("%d", &dniA);
          rewind(mascots);
          fclose(mascots);
          mascots = fopen("Mascotas.dat", "r+b");
          int ct = 0;
          while (!feof(mascots)) {
            if (busc.dni == dniA) {
              masco = busc;
            }
            fread(&busc, sizeof(mascs), 1, mascots);
            if(busc.dni == dniA) match2++;
          }
          
          if (match2 > 0) {
///////////////////////////////////////////////////////////////////////////////////////////////
						vetTemp = fopen("AuxTemp.dat", "w+b");
						int count=0;
						int countM=0;
						rewind(mascots);
          	fread(&masco, sizeof(mascs), 1, mascots);
	          while (!feof(mascots)) {
	            countM++;
	            fread(&masco, sizeof(mascs), 1, mascots);
	          }
	          mascs auxMsc[countM];
	          rewind(mascots);
	          fread(&masco, sizeof(mascs), 1, mascots);
	          int c2=0;
	          while (!feof(mascots)) {
	            auxMsc[c2] = masco;
	            fread(&masco, sizeof(mascs), 1, mascots);
	            c2++;
	          }
	          
	    /////////////////////////////////////////////////////
	          
	          rewind(vets);
          	fread(&vet, sizeof(veterin), 1, vets);
	          while (!feof(vets)) {
	            count++;
	            fread(&vet, sizeof(veterin), 1, vets);
	          }
	          veterin vetAux[count];
	          rewind(vets);
	          fread(&vet, sizeof(veterin), 1, vets);
	          int c1=0;
	          while (!feof(vets)) {
	            vetAux[c1] = vet;
	            fread(&vet, sizeof(veterin), 1, vets);
	            c1++;
	          }
	          
	          for(int i = 0; i < count; i++) {
	          	if(mat == vetAux[i].matricula) {
	          		vetAux[i].rank++;
							}
						}
						rewind(vetTemp);
						for(int i = 0; i < count; i++) {
							fwrite(&vetAux[i], sizeof(veterin), 1, vetTemp);
						}
						fclose(vets);
						if (remove("Veterinarios.dat") != 0) {
							perror("ERROR");
							system("pause");
						}
						fclose(vetTemp);
						if (rename("AuxTemp.dat", "Veterinarios.dat") != 0) {
							perror("ERROR");
							system("pause");
						}
						fclose(turnos);
////////////////////////////////////////////////////////////////////////////////////////////////
            system("cls");
            vets = fopen("Veterinarios.dat", "r+b");
            turnos = fopen("Turnos.dat", "a+b");
            char rep[380];
            printf("\n\n----------------------------------------------------------------------------\n\n\n");
						printf("*-*-*-*-*-*-               Registrar evolución               -*-*-*-*-*-*\n\n\n");
	      	  printf("----------------------------------------------------------------------------\n\n\n\n");
            printf("--> Ingrese la evolución de ");
          	puts(busc.apeNom);
            printf("\n\nEntrada: ");
            turno tmpT;
            
            _flushall();
            gets(rep);
            rewind(turnos);
            fread(&tmpT, sizeof(turno), 1, turnos);
	          while (!feof(turnos)) {
	            count++;
	            fread(&tmpT, sizeof(turno), 1, turnos);
	          }
	          turno vecT[count];
						int c3=0;
						rewind(turnos);
						fread(&tmpT, sizeof(turno), 1, turnos);
	          while (!feof(turnos)) {
	            vecT[c3] = tmpT;
	            fread(&tmpT, sizeof(turno), 1, turnos);
	            c3++;
	          }
						for(int i = 0; i < c3; i++) {
							if(vecT[i].dni == dniA) {
								strcpy(vecT[i].detalle, rep);
							}
						}
						turTemp = fopen("TurAux.dat", "w+b");
						
						for(int i = 0; i < c3; i++) {
							fwrite(&vecT[i], sizeof(turno), 1, turTemp);
						}
						
						fclose(turnos);
						if (remove("Turnos.dat") != 0) {
							perror("ERROR: ");
							system("pause");
							evol();
						}
						fclose(turTemp);
						if (rename("TurAux.dat", "Turnos.dat") != 0) {
							perror("ERROR: ");
							system("pause");
							evol();
						}
						
						fclose(users);
						fclose(mascots);
//						fclose(turnos);
						fclose(vets);
    				menu();
            
///////////////////////////////////////////////////////////////////////////////////////////////
          } else {
            system("cls");
            printf("\n\n\n**************************************************************************\n");
			   		printf("--> ERROR: El DNI ingresado es inexistente.\n");
			   	 	printf("**************************************************************************\n\n\n\n\n");
            system("pause");
            err = 1;
          }
        } else {
          system("cls");
          printf("\n\n\n**************************************************************************\n");
			    printf("--> ERROR: La matricula ingresada es inexistente.\n");
			    printf("**************************************************************************\n\n\n\n\n");
          system("pause");
          err = 1;
        }
      } while (err == 1);
    }
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
