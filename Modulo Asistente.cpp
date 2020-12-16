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
  int rank;
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

struct turno {
  int matricula_Vet;
  fecha fecha_Turno;
  int dni;
  char detalle[380];
};

int opc = 0;
int err = 0;


bool logged = false;


FILE *vets;
FILE *users;
FILE *mascots;
FILE *turnos;

user asis;
int cant_masct = 0;

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
    if (!logged) {
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
      if (opc == 1 || opc == 2 || opc == 3 || opc == 4 || opc == 5) {
        err = 0;
        if (opc == 1) inicS();
        if (opc == 2) regM();
        if (opc == 3) regT();
        if (opc == 4) lstA();
        if (opc == 5) exit();
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
  users = fopen("Usuarios.dat", "r+b");
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
      int match = 0;
      user aux;
      while (!feof(users)) {
        if (strcmp(asis.usrID, busc.usrID) == 0) {
          match++;
          aux = busc;
        }
        fread(&busc, sizeof(user), 1, users);
      }
      if (match == 1) {
        int match2 = 0;
        system("cls");
        printf("\n\n----------------------------------------------------------------------------\n\n\n");
        printf("*-*-*-*-*-*-                 Iniciar Sesion                  -*-*-*-*-*-*\n\n\n");
        printf("----------------------------------------------------------------------------\n\n\n\n");

        printf("Ingrese la contraseña: ");
        _flushall();
        gets(asis.password);
        if (strcmp(asis.password, aux.password) == 0) {
          match2++;
        }
        if (match2 > 0) {
          asis = aux;
          system("cls");
          printf("\n\n----------------------------------------------------------------------------\n\n\n");
          printf("*-*-*-*-*-*-  Sesion iniciada correctamente -*-*-*-*-*-*\n\n\n");
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
    } while (err == 1);
  }
  fclose(users);
  printf("\n\n");
  system("pause");
  menu();
}

void regM() {
  if (logged) {
    system("cls");
    mascots = fopen("Mascotas.dat", "a+b");

    if (mascots == NULL) {
      printf ("ERROR: No se pudo abrir el archivo Mascotas.dat");
    } else {
      mascs masc;
      printf("\n\n----------------------------------------------------------------------------\n\n\n");
      printf("*-*-*-*-*-*-               Registrar una Mascota                -*-*-*-*-*-*\n\n\n");
      printf("----------------------------------------------------------------------------\n\n\n\n");
      printf("\nIngrese nombre de la mascota y apellido del dueño: ");
      _flushall();
      gets(masc.apeNom);
      printf("Ingrese el domicilio: ");
      _flushall();
      gets(masc.domicilio);
      printf("Ingrese el DNI del dueño: ");
      scanf("%d", &masc.dni);
      printf("Ingrese la localidad: ");
      _flushall();
      gets(masc.localidad);

      printf("\t\t**Ingrese la fecha de nacimiento de la mascota**");
      printf("\nDia: ");
      scanf("%d", &masc.nacimiento.dia);
      printf("\nMes: ");
      scanf("%d", &masc.nacimiento.mes);
      printf("\nAño: ");
      scanf("%d", &masc.nacimiento.year); //year (?
      fwrite(&masc, sizeof(mascs), 1, mascots);
      cant_masct++;
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
  if (cant_masct > 0) {
    if (logged) {
      system("cls");
      turnos = fopen("Turnos.dat", "a+b");
      vets = fopen("Veterinarios.dat", "r+b");
      if (vets == NULL) {
        printf ("ERROR: No se pudo abrir el archivo Veterinarios.dat");
      }
      if (turnos == NULL) {
        printf ("ERROR: No se pudo abrir el archivo Turnos.dat");
      }
      else {
        int match3 = 0;
        turno turns;
        veterin vet;
        system("cls");
        printf("\n\n----------------------------------------------------------------------------\n\n\n");
        printf("*-*-*-*-*-*-               Registrar un turno                -*-*-*-*-*-*\n\n\n");
        printf("----------------------------------------------------------------------------\n\n\n\n");
        rewind(vets);
        fread(&vet, sizeof(veterin), 1, vets);
        printf("Veterinarios: \n");
        while (!feof(vets)) {
          printf("Apellido y nombre: ");
          puts(vet.apeNom);
          printf("Matricula: %d\n\n", vet.matricula);
          fread(&vet, sizeof(veterin), 1, vets);
        }
        printf("\nIngrese la matricula del veterinario: ");
        scanf("%d", &turns.matricula_Vet);
        rewind(vets);
        while (!feof(vets)) {

          if (turns.matricula_Vet == vet.matricula) {
            match3++;
          }
          fread(&vet, sizeof(veterin), 1, vets);
        }
        if (match3 > 0) {

          printf("\t\t**Ingrese la fecha del turno**");
          printf("\nDia: ");
          scanf("%d", &turns.fecha_Turno.dia);
          printf("\nMes: ");
          scanf("%d", &turns.fecha_Turno.mes);
          printf("\nAño: ");
          scanf("%d", &turns.fecha_Turno.year);
          printf("Ingrese el DNI del dueño de la mascota: ");
          scanf("%d", &turns.dni);
          printf("Ingrese el detalle de la atencion: ");
          _flushall();
          gets(turns.detalle);
          fwrite(&turns, sizeof(turno), 1, turnos);
        }
        else {
          system("cls");
          printf("\t\t\tLa matricula ingresa es inexistente.");
        }
      }
      fclose(turnos);
      fclose(vets);
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
	} else {
	  system("cls");
	  printf("\n\n\n**************************************************************************\n");
	  printf("--> ERROR: Antes de realizar esta operación debe registrar mascotas\n");
	  printf("**************************************************************************\n\n\n\n\n");
	  system("pause");
	  menu();
	}
}

void lstA() {
  if (logged) {
    turnos = fopen("Turnos.dat", "r+b");
    if (turnos == NULL) {
      printf ("ERROR: No se pudo abrir el archivo Turnos.dat");
    } else {
      system("cls");
      turno turns;
      veterin vet;
      rewind(turnos);
      fread(&turns, sizeof(turno), 1, turnos);
      while (!feof(turnos)) {
        printf("Veterinario con matricula: %d\n", turns.matricula_Vet);
        printf("Dia del turno: %d/%d/%d\n", turns.fecha_Turno.dia, turns.fecha_Turno.mes, turns.fecha_Turno.year);
        printf("Detalle del turno: ");
        puts(turns.detalle);
        printf("\n\n");
        fread(&turns, sizeof(turno), 1, turnos);
      }
    }

  } else {
    system("cls");
    printf("\n\n\n**************************************************************************\n");
    printf("--> ERROR: Antes de realizar esta operación debe iniciar sesión\n");
    printf("**************************************************************************\n\n\n\n\n");
    system("pause");
    menu();
  }
  fclose(turnos);
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
