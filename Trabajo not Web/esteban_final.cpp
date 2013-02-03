#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;


class Pelicula
{
private:
	int nCliente,nRentas,nCopias,codigo,anio;
	bool flag; //Ayudara a checar si esta rentada 
	string titulo, director;
	string archivo; //Guardara la ruta del archivo donde se encuentra registrada
public:
	Pelicula (){};
	Pelicula(int c, string t, string d,int a, int nr, int nc)
		{titulo = t; director = d; codigo = c; anio = a; nRentas = nr; nCopias = nc; flag = false; }
	void setTitulo(string t)
		{ titulo = t;}
	void setDirector(string d)
		{ director = d; }
	void setNCliente(int nc)
		{ nCliente = nc; }
	void setRentas(int nr)
		{ nRentas = nr; }
	void setCopias(int nc)
		{ nCopias = nc; } // Fin de set's
	void setAnio(int a)
		{anio = a;}
	int getAnio()
		{return anio;}
	string getTitulo()
		{ return titulo;}
	string getDirector()
		{ return director; }
	int getNCliente()
		{ return nCliente; }
	int getRentas()
		{ return nRentas; }
	int getCopias()
		{ return nCopias; }
	int getCodigo()
		{ return codigo; }
	string getArchivo()
		{return archivo;}

	bool agregar(string ruta_archivo);
	bool borrar();
	bool rentar(int c);
	bool devolver();
	bool mostrar();

};

bool Pelicula::agregar(string ruta_archivo){
	//Se guardar en el archivo la informacion de la pelicula

	archivo = ruta_archivo;
	//Abre el archivo en modo "append"
	ofstream archivo_salida(archivo.c_str(),fstream::app);

	//Comprueba si se pudo abrir el archivo
	if(!archivo_salida)
		return false;

	//Imprime en el archivo la linea con el formato correspondiente
	archivo_salida<<codigo<<"|"<<titulo<<"|"<<anio<<"|"<<nRentas<<"|"<<nCopias<<endl;

	//Cierra el archivo.
	archivo_salida.close();
	return true;
}
bool Pelicula::borrar(){
	//Se elimina la pelicula del archivo
	if(flag)
		return false;
	
	/*Falta mas implementacion*/

	return true;
}
bool Pelicula::rentar(int c){
	//Comprueba si hay copias disponibles para renta
	if(nCopias == 0 || (nCopias == nRentas))
		return false;

	//Aumenta en uno la cantidad de veces rentada
	nRentas++;
	nCliente = c;
	return true;
}
bool Pelicula::devolver(){

	//Disminuye en uno la cantidad de copias rentas, y deja disponible una mas

	//Comprueba que no se intente regresar algo de lo que no se tienen copias
	//O algo que no se ha rentado
	if(nCopias == 0 || nRentas == 0) 
		return false;

	nRentas--;
	return true; //Falta
}
bool Pelicula::mostrar(){
	cout<<"\n\nDatos de la pelicula: "<<titulo<<endl;
	cout<<"\n\t Codigo: "<<codigo;
	cout<<"\n\t Director: "<<director;
	cout<<"\n\t Numero de rentas: "<<nRentas;
	cout<<"\n\t Numero de Copias: "<<nCopias<<endl;
	cout<<"\n"<<endl;
}


typedef struct nodoP { 
//Se define abreviacion (typedef) de la 
//estructura que servira para hacer el arreglo dinami
	Pelicula *p;
	struct nodoP *sig;
}Pelis;

//Inicio de la lista de peliculas
typedef struct Pila{
	Pelis *h;
}Piila;

//Busca peliculas por su numero de codigo
bool buscarPelicula(int num_peli, Piila p){
	Pelis *aux;
	aux = p.h;
	//Recorre hasta que se encuentra con un valor nulo
	//El cual indica el final de la lista
	while(aux != NULL){
		//Comprueba si el codigo lo tiene el elementos sobre el que se itera
		if(aux->p->getCodigo() == num_peli)
			return true;

		aux = aux->sig;
	}

	return false;
}

bool buscarPeliculaNombre(string titulo, Piila p){
	//Sirve para validar el que no se repitan los titulos
	Pelis *aux;
	aux = p.h;
	while(aux != NULL){
		//Comprueba si el elemento sobre el que se itera tiene el nombre buscado
		if(aux->p->getTitulo() == titulo)
			return true;

		aux = aux->sig;
	}
	return false;
}


//Regresa un apuntador a la pelicula que se busca
Pelicula * obtenerPelicula(int num_peli, Piila p){
	//Algoritmo para buscar pelicula en arreglo dinamico
	Pelis *aux;
	aux = p.h;
	while(aux != NULL){
		if(aux->p->getCodigo() == num_peli)
			return aux->p;

		aux = aux->sig;
	}
	return aux->p;
}




int main(){
	char op;
	int pls = 0;

	Piila peliculas;
	peliculas.h = NULL;

	while(op != '6'){
		//El programa sale hasta que se digite 6 (salir)
		system("CLS");

		cout<<"Seleccione una opcion: "<<endl;
		cout<<" \t 1) Agregar pelicula "<<endl;
		cout<<" \t 2) Borrar pelicula "<<endl;
		cout<<" \t 3) Rentar "<<endl;
		cout<<" \t 4) Devolver "<<endl;
		cout<<" \t 5) Mostrar  "<<endl;
		cout<<" \t 6) Salir "<<endl;
		cout<<" \n\n\t\t Opcion => ";
		cin>>op; //Se solicita opcion al usuario
			
		switch(op){
			case '1':{ //Se agrega pelicula
				int nCliente,nRentas,nCopias;
				string archivo, titulo, director;
				pls++;
				system("CLS");
				//Se solicita la informacion de la pelicula
				cout<<"Ingrese los datos: "<<endl;
				cout<<"\t Titulo: ";
				cin>>ws;
				getline(cin,titulo);
				cout<<"\n\t Director: ";
				getline(cin,director);
				cout<<"\n\t Numero de rentas: ";
				cin>>nRentas;
				cout<<"\n\t Numero de Copias: ";
				cin>>nCopias;


				if(buscarPeliculaNombre(titulo,peliculas)){
					//Busca el nombre de la pelicula, si existe no permite continuar
					cout<<"La pelicula YA EXISTE.\n\n"<<endl;
					system("PAUSE");
					continue;
				}

				//Se crea objeto Pelicula para almacenar en arreglo
				Pelicula *p = new Pelicula(pls,titulo,director,nCliente,nRentas,nCopias); 

				//Se agrega al arreglo

				system("CLS");
				//Se le indica al objeto que se guarde en archivo
				
				if(!p->agregar("altas.txt")) //Se comprueba que se haya guardado en el archivo
					cout<<" Ha ocurrido un error al guardar la pelicula"<<titulo<<". \n";
				else{
					cout<<"Se ha guardado la pelicula "<<titulo<<" de manera exitosa \n\n";
					//Se guarda en logica del programa.
					Pelis *nueva;

					//Crea memoria dinamica para el nuevo elemento de la lista
					if((nueva = (Pelis *)malloc(sizeof(Pelis))) == NULL ){
						cout<<" Ha ocurrido un error al guardar la pelicula"<<titulo<<". \n";
						continue;
					}

					//Si la lista esta vacia entonces el elemento que le sigue sera nulo
					if(peliculas.h == NULL)
						nueva->sig = NULL;
					else //Si ya hay elementos, se guarda la direccion 
						//del elemento registrado una vez antes
						nueva->sig = peliculas.h;

					nueva->p = p;
					peliculas.h = nueva;	
				}

				system("PAUSE");
			} 
			break;
			case '2': {
				system("CLS");
				int code;
				cout<<"BORRAR Pelicula \n\t Codigo de la pelicula: ";
				cin>>code; //Se solicita el codigo de la pelicula a borrar

				//Se verifica que exista una pelicula con ese codigo
				Pelicula *p;
				if(buscarPelicula(code,peliculas)){ 
					//Se guarda la referencia al objeto
					p = obtenerPelicula(code,peliculas);
				}else{
					cout<<"La pelicula NO EXISTE.\n\n"<<endl;
					system("PAUSE");
					continue;
				}

				if(!p->borrar()){ //Intenta borrar la pelicula del archivo
					cout<<"\n\n Ha ocurrido un error al borrar la pelicula #"<<code<<". \n";				
				}else{
					cout<<"Se ha borrado la pelicula #"<<code<<" de manera exitosa \n";
					//Se incluira codigo para eliminar la pelicula 
					// de la parte logica del programa
				}
				system("PAUSE");
			}//Se borra una pelicula
			break;
			case '3':{ //Se renta una pelicula

				system("CLS");
				int c,cd;
				cout<<"RENTAR Pelicula \n\t Codigo de la pelicula: ";
				cin>>cd;

				cout<<" \n\t Cliente: ";
				cin>>c;
				
				Pelicula *p;
				//Se verifica que exista la pelicula
				if(buscarPelicula(cd,peliculas)){
					p = obtenerPelicula(cd,peliculas);
				}else{
					cout<<"La pelicula NO EXISTE.\n\n"<<endl;
					system("PAUSE");
					continue;
				}

				//Se verifica que ha sido posible y guardado el cambio de renta
				if(!p->rentar(c))
					cout<<"La pelicula esta en renta o no hay copias suficientes\n\n"<<endl;
				else
					cout<<"La pelicula se ha rentado \n\n"<<endl;

				system("PAUSE");
			}
			break;
			case '4':{ //Se devuelve una pelicula
				system("CLS");
				int code;
				cout<<"DEVOLVER Pelicula \n\t Codigo de la pelicula: ";
				cin>>code; //Se solicita el codigo de la pelicula a devolver


				//Buscar pelicula y regresar apuntador a objeto Pelicula
				//Se verifica que exista una pelicula con ese codigo
				Pelicula *p;
				if(buscarPelicula(code,peliculas)){ 
					//Se guarda la referencia al objeto
					p = obtenerPelicula(code,peliculas);
				}else{
					cout<<"La pelicula NO EXISTE.\n\n"<<endl;
					system("PAUSE");
					continue;
				}

				//Se verifica que haya guardado el cambio de devolucion en el archivo
				if(!p->devolver())
					cout<<"Ha ocurrido un error. \n\n"<<endl;
				else
					cout<<"Cambios guardados \n\n"<<endl;

				system("PAUSE");
			}
			break;
			case '5':{
				system("CLS");

				//Comprueba si se han agregado peliculas
				// "pls" contiene el numero total de peliculas registradas
				if(pls <= 0){
					cout<<"No se han agregado peliculas\n\n";
					system("PAUSE");
					continue;
				}

				//Buscar pelicula y regresar objeto Pelicula
				Pelis *aux;
				aux = peliculas.h;

				//Itera hasta encontrar el final de la lista
				while(aux != NULL){
					//Invoca al metodo que muestra la informacion del elemento Pelicula
					if(aux->p->getRentas() > 0) //Comprueba que se haya rentado
						aux->p->mostrar();
					aux = aux->sig;
				} 

				system("PAUSE");
				//Se muestran las peliculas
			}
			break;
			default:
				//Si no es ninguna opcion del menu, continua.
				continue;
			break;
		}
	}
	return 0;
}
