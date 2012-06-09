#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef int listEntry;

typedef struct Node
{
        listEntry data;
        struct Node *next;
}node;

typedef struct list{
        
        node *head;
}List;

void createList(List *);
node *makeNode(listEntry);
void addNode(List *,listEntry);
void printList(List);

node* makeNode(listEntry val)
{
     node *newNode;
     if((newNode = (node *) malloc(sizeof(node))) == NULL)
     {
                printf("No hay memoria disponible");
                exit(0);
     }
     
     newNode->data = val;
     newNode->next = NULL;
     return newNode;
}

void addNode(List *l,listEntry val)
{
     node *newNode,*previous,*current;
     newNode = makeNode(val);
     /* Si la lista está vacía agregamos el nuevo nodo*/

     if(l->head == NULL)
     {
         l->head = newNode;
         return;
     }
     
     /*Si la lista no setá vacía. Insertamos el nodo en la posición según el orden ascendente en la lista */
     
     current = l->head;
     
     while(current != NULL && current->data < val)
     {
         previous = current;
         current = current->next;
     }
     
     /*Agregamos nodo al principio de la lista no vacía*/
     
     if(current == l->head)
     {
         newNode->next = l->head; // NULL
         l->head = newNode;
     }
     else
     {
         previous->next = newNode;
         newNode->next = current;
     }
}

void createList(List *l)
{
     l->head = NULL;
}

void printList(List list)
{
     node *aux;
     aux = list.head;
     
     if(aux == NULL)
     {
            printf("Lista vacía");
            return;
     }
     
     printf("\nContenido de la lista\n");
     
     while(aux != NULL)
     {
       printf(" %d ",aux->data);
       aux = aux->next;
     }
     
     printf("\n");
}

int findNode(List l,listEntry val)
{
  
  if(l.head = NULL)
    return 1;
  
  int r = 0;
  node *aux = l.head;
  
  while(aux != NULL)
  {
    if(aux->data == val)
       r++;
    aux = aux->next;
  }
  
  return r;
}

int numNode(List l,listEntry val)
{
if(l.head = NULL)
    return 0;
    
  int r = 0;
  node *aux = l.head;
  
  while(aux != NULL)
  {
    if(aux->data == val)
       r++;
    aux = aux->next;
  }
  
  return r;
}

void deleteNode(List *l,listEntry val)
{
     if(findNode(*l,val) || l->head == NULL)
     {
        printf("\nNodo no encontrado\n");
        return;
     }

     int r = 0;
      node *aux = l->head;
      node *aux2;
      
      while(aux != NULL)
      {
        if(aux->data == val && aux->next == NULL)
        {

            l->head = NULL;
            free(aux);

          
          printf("\nNodo Eliminado\n");
          return;
        }
        
           if(aux->next->data == val)
              break;

        r++;
        aux = aux->next;
        return;
      }
           
      
      aux2 = aux->next;
      
      aux->next = aux2->next;

      
      free(aux2);
      
      printf("\nNodo Eliminado\n");
      return;
      
}

void compaqList(List *l)
{int i=0,a,b;
List l2;
createList(&l2);

     node *aux = l->head;
     while(aux != NULL)
     {
         i++;
         aux = aux->next;
     }
     
     while(l->head->next != NULL)
     {
     
         b = l->head->data;
         
         for(a=0;a<i;a++)
         {        printf("%d",b);               
                  deleteNode(l,b); 
         }
                      
                           
          addNode(&l2,b);
          l->head = l->head->next;
     }
     
     addNode(&l2,l->head->data);
     
     l->head = l2.head;
     
     printf("\nLista CompaQtada\n");
     
}


main()
{
      List l1;
      createList(&l1);
      
      
      int i=1;
      int num;
      char op;
      while(1)
      {
              system("CLS");
              printf("Opciones: \n\n 1) Agregar nodo \n 2) Eliminar nodo \n 3) Buscar Nodo \n 4) Contar nodos \n 5) Compactar Lista \n 6) Imprimir Lista\n\n \t Elige una opcion: ");
              scanf("%c",&op);
              switch(op)
              {
                case '1':
                     
                     printf("Ingresa un numero: ");
                     scanf("%d",&num);
                     
                     addNode(&l1,num);
                     printf("Nodo Agregado");
                     
                     system("PAUSE");
                break;
                case '2':
                     printf("Valor del nodo a eliminar");
                     scanf("%d",&num);
                     
                     deleteNode(&l1,num);

                                    system("PAUSE");
                break;
                case '3':
                    printf("Valor del nodo a buscar: ");
                     scanf("%d",&num);
                     
                     if(findNode(l1,num))
                       printf("\nEl nodo esta en la lista");
                     else
                       printf("\nEl nodo no esta en la lista\n");
                       
                     system("PAUSE");                      
                break;
                case '4':
                     printf("Valor del nodo a buscar: ");
                     scanf("%d",&num);
                     
                     if(findNode(l1,num))
                       printf("\nEl nodo se repite %d veces en la lista",numNode(l1,num));
                     else
                       printf("\nEl nodo no esta en la lista\n");
                       
                     system("PAUSE");  
                break;
                case '5':
                     compaqList(&l1);
                     system("PAUSE");
                break;
                case '6':
                     printList(l1);
                     system("PAUSE");  
                break;
                case '7':
                     exit(0);
                break;
                default:
                        continue;
              }
      }
      
      getch();
}
