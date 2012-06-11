#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "string.h"

typedef struct mDown
{
        char a[250]; // Nombre del alumno
        char b[12]; // # Boleta
       	struct mDown *nextDown; // Siguiente alumno
}MD;


typedef struct MR
{
        char grupo[128]; // Nombre del grupo
        struct MR *nextRight; // Siguiente grupo
        struct mDown *listDown; // Lista de Alumnos

}MR;

typedef struct multiList
{
   MR *head;
}ML;


void createML(ML *);

MR *makeGroup(char []);
MD *makeItem(char [],char []);

void addNodeGroup(ML *,char []);
void addNodeItem(ML *,char [],char [],char []);

void deleteDownList(MD *);

MR *findGroup(ML ,char []);
int findItem(ML,char [],int,int);

int findSingleGroup(ML,char []);

void printML(ML);


/*-------------Extras----------------*/
char printMenu();

/*-------CONTROLADORES----------*/

void createGroup(ML *);
void deleteGroup(ML *);
void addStudent(ML *);
void deleteStudent(ML *, char []);
void modifyStudent(ML *);

main()
{
	char op;
	int i = 1;
	//Grupo
	ML E1;
	createML(&E1);

	
	//printML(E1);

	while(i)
	{	
		op = printMenu();
		fflush(stdin);
		switch(op)
		{
			case '1':
				system("CLS");
					char gName[128];

					printf("Nombre del grupo: ");
					scanf("%128s",gName);

					addNodeGroup(&E1,gName);
				printf("\n\n\t");
				system("PAUSE");
			break;
			case '2':
				deleteGroup(&E1);
				printf("\n\n\t");
				system("PAUSE");
			break;
			case '3':
				system("CLS");
				addStudent(&E1);
				printf("\n\n\t");
				system("PAUSE");
			break;
			case '4':
				system("CLS");
				char boleta[12];
				printf("Numero de boleta del alumno: \n");
				scanf("%s",boleta);

					deleteStudent(&E1,boleta);

				printf("\n\n\t");
				system("PAUSE");
			break;
			case '5':
				system("CLS");
					printML(E1);
				printf("\n\n\t");
				system("PAUSE");
			break;
			case '6':
				exit(1);
			break;
			default:
			break;
		}
	}

	getch();
}

char printMenu()
{
	system("CLS");

	char op;

	printf("\t Bienvenido al sistema de 'control escolar' \n\n");
	printf("1) Crear grupo \n");
	printf("2) Eliminar grupo \n");
	printf("3) Agregar alumno a grupo \n");
	printf("4) Eliminar alumno \n");
	printf("5) Imprimir todos los grupos \n");
	printf("6) Salir \n\n");
	printf("\tQue desea hacer?: ");

	scanf("%c",&op);

	return op;
}

void deleteGroup(ML *l)
{
	system("CLS");

	char gName[128];
	fflush(stdin);
	printf("Grupo a borrar: ");
	gets(gName);

	if(!findSingleGroup(*l,gName) || l->head == NULL)
	{
		printf("\nGrupo no encontrado\n");
		return;
	}

	int r = 0;
	MR *aux = l->head;
	MR *aux2;

	while(aux != NULL)
	{
		if( strcmp(aux->grupo,gName) == 0 && aux->nextRight == NULL)
		{

			l->head = NULL;
			free(aux);

			printf("\nGrupo Eliminado\n");
			return;
		}

		if(strcmp(aux->nextRight->grupo,gName) == 0)
			break;

		r++;
		aux = aux->nextRight;
		return;
	}


	aux2 = aux->nextRight;

	aux->nextRight = aux2->nextRight;


	free(aux2);
	printf("\nGrupo Eliminado\n");

	return;

}

void addStudent(ML *E)
{

	char boleta[12], nombre[250],grupo[128],gName[128];	

	fflush(stdin);
	printf("Nombre del grupo: ");
	gets(gName);

	if(findSingleGroup(*E,grupo))
	{
		printf("\nEse grupo no existe.\n");
		fflush(stdin);
		return;
	}

	fflush(stdin);
	printf("Nombre del alumno: ");
	gets(nombre);

	fflush(stdin);
	printf("Numero de boleta: ");
	gets(boleta);

	if(findItem(*E,boleta,0,1))
	{	
		fflush(stdin);
		return;
	}

	addNodeItem(E,nombre,boleta,gName);
}


/*----- MULTILISTA FUNCIONES -----*/

void createML(ML *E)
{
	E->head = NULL;
	return;
}

//Imprimir todos los grupos
void printML(ML E)
{	
	if(E.head == NULL)
	{
		printf("No existe ningun grupo. \n");
		return;
	}

	MR *group;
	MD *alumno;
	group = E.head;

	while(group != NULL)
	{
		printf("Grupo: %s \n\n",group->grupo);

		alumno = group->listDown;

		if(alumno == NULL)
		{
			printf("No hay ningun alumno en este grupo.\n");
		}

		while(alumno != NULL)
		{
			printf("\t %s - %s \n",alumno->b,alumno->a);

			alumno = alumno->nextDown;
		}

		group = group->nextRight;

		printf("\n\n");
	}
}




//Crear grupo
MR* makeGroup(char gName[])
{
   	 MR *newMR;
     
     if((newMR = (MR *) malloc(sizeof(MR))) == NULL)
     {
		printf("No hay memoria disponible");
		exit(0);
     }

     strcpy(newMR->grupo,gName);

     newMR->nextRight = NULL;
     newMR->listDown = NULL;

     return newMR;
}

void addNodeGroup(ML *l,char gName[])
{	

	if(findSingleGroup(*l,gName))
	{
		printf("\nEse grupo ya existe.\n");
		return;
	}

     MR *newNode,*previous,*current;
     
     newNode = makeGroup(gName);


     if(l->head == NULL)
     {
         l->head = newNode;
         return;
     }
     
     /*Si la lista no esta vacía. Insertamos el nodo en la posición según el orden ascendente en la lista */
     
     current = l->head;
     
     /*Agregamos nodo al principio de la lista no vacia*/
     
     if(current == l->head)
     {
         newNode->nextRight = l->head; // NULL
         l->head = newNode;
     }

}

//Crear alumno

MD *makeItem(char nombre[],char boleta[])
{
	MD *newMD;

	if((newMD = (MD *) malloc(sizeof(MD))) == NULL)
	{
		printf("No hay memoria disponible");
		exit(0);
	}

	strcpy(newMD->a,nombre);
	strcpy(newMD->b,boleta);
	newMD->nextDown = NULL;

	return newMD;
}

void addNodeItem(ML *E,char nombre[],char boleta[],char grupo[])
{
	if(!findSingleGroup(*E,grupo))
	{
		printf("\nEse grupo no existe.\n");
		return;
	}


	MR *group_pointer;
	MD *newNode,*current;

	group_pointer = findGroup(*E,grupo);

	newNode = makeItem(nombre,boleta);


	if(group_pointer->listDown == NULL)
	{
		group_pointer->listDown = newNode;
		return;
	}

	/*Si la lista no esta vacía. Insertamos el nodo en la posición según el orden ascendente en la lista */

	current = group_pointer->listDown;

	/*Agregamos nodo al principio de la lista no vacia*/

	if(current == group_pointer->listDown)
	{
		newNode->nextDown = group_pointer->listDown; // NULL
		group_pointer->listDown = newNode;
	}
}

//Comprobar si existe un grupo
int findSingleGroup(ML l,char gName[])
{
  
  if(l.head == NULL)
    return 0;
  
  int r = 0;
  MR *aux = l.head;
 
  while(aux != NULL)
  {
    if(strcmp(aux->grupo,gName)==0)
       r++;

    aux = aux->nextRight;
  }
  
  return r;
}


//Encontrar grupo
MR *findGroup(ML E,char gName[])
{
  
  int r = 0;
  MR *aux = E.head;
 
  while(aux != NULL)
  {
    if(strcmp(aux->grupo,gName)==0)
       break;
    aux = aux->nextRight;
  }
  
  return aux;
}

//Eliminar lista completa
void deleteDownList(MD *l)
{
	MD *aux, *ant,*next;

	aux = l;

	while(aux != NULL)
	{
		printf("(.---.)");
		ant = aux;
		aux = aux->nextDown;
		free(ant);
	}
}


//Buscar Alumno
int findItem(ML E,char comp[],int b,int c)
{	
	if(E.head == NULL)
	{
		printf("No existe ningun grupo. \n");
		return 1;
	}

	MR *group;
	MD *alumno;
	group = E.head;

	char grupoC[128];
	int match = 0;

	while(group != NULL)
	{
		strcpy(grupoC,group->grupo);

		alumno = group->listDown;
		

		if(alumno == NULL)
		{
			group = group->nextRight;
			continue;
		}

		while(alumno != NULL)
		{
			if(b)
			{
				if(strcmp(alumno->a,comp))
				{
					match = 1;
					break;
				}
			}
			else if(b==0)
			{
				if(strcmp(alumno->b,comp) == 0)
				{
					match = 1;
					break;
				}
			}

			alumno = alumno->nextDown;
		}

		if(match)
			break;

		group = group->nextRight;

		printf("\n\n");
	}

	if(match && c != 3)
		printf("Ese alumno ya fue encontrado en el grupo %s \n",grupoC);

	return match;
}

void deleteStudent(ML *E,char comp[])
{	
	if(E->head == NULL)
	{
		printf("No existe ningun grupo. \n");
		return;
	}


	if(!findItem(*E,comp,0,3))
	{
		printf("El alumno no existe\n");
		return;
	}

	MR *group;
	MD *alumno,*aux,*alumno2;
	group = E->head;

	char grupoC[128];
	int match = 0;

	while(group != NULL)
	{
		strcpy(grupoC,group->grupo);

		alumno = group->listDown;
		
		if(alumno == NULL)
		{
			group = group->nextRight;
			continue;
		}

		while(alumno != NULL)
		{	
			if(strcmp(alumno->b,comp) == 0 && group->listDown->nextDown == NULL)
			{
				group->listDown = NULL;
				free(alumno);


				printf("\nAlumno Eliminado\n");
				match=2;
				break;
			}

			printf("%s == %s || %d \n",alumno->nextDown->b,comp,strcmp(alumno->nextDown->b,comp));
			if(strcmp(alumno->nextDown->b,comp) == 0)
			{
				match = 1;
				break;
			}

			alumno = alumno->nextDown;
		}

		if(match==1)
		{
			alumno2 = alumno->nextDown;
			alumno->nextDown = alumno2->nextDown;
			free(alumno2);
			printf("\nAlumno Eliminado\n");
			break;
		}
		else if(match==2)
			break;

		group = group->nextRight;

		printf("\n\n");
	}

	if(match)
	{
		printf("El alumno se ha borrado del grupo %s\n", grupoC);
	}

	return;
}

