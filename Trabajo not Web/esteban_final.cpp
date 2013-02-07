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
	archivo_salida<<codigo<<"|"<<titulo<<"|"<<director<<"|"<<anio<<"|"<<nRentas<<"|"<<nCopias<<endl;

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
	flag = true;
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


	if(nRentas == 0)
		flag = false;

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

void guardar(Piila p,string archivo){
	
	

	//Se abre el archivo para resetear y poder escribir desde cero
	ofstream archivo_salida(archivo.c_str());
	//Comprueba si se pudo abrir el archivo
	if(!archivo_salida)
		return;
	//Cierra el archivo.
	archivo_salida.close();

	if(p.h == NULL)
		return;
	
	Pelis *aux;
	aux = p.h;
	while(aux != NULL){
		if(!aux->p->agregar(archivo)) //Agrega al archivo
			cout<<"Error al guardar la pelicula: "<<aux->p->getTitulo()<<endl;

		aux = aux->sig;
	}

	//Guarda en el archivo al finalizar 
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



//Obtiene las peliculas actuales en el archivo
int inicio(Piila *p, string archivo){

	//Abre el archivo 
	ifstream archivo_lectura(archivo.c_str());
	string f;

	//Si el archivo no se puede abrir, cierra el programa
	if(!archivo_lectura){
		cout<<"Algo salio mal"<<endl;
		system("PAUSE");
		exit(1);
	}
	
	char l[100];
	int i,pos,prevpos,pls=0;
	string c,t,d,r,co,a;
	//Recorre el archivo linea por linea
	while(!archivo_lectura.eof()){
		//Obtiene una nueva linea
		archivo_lectura.getline(l,99);
		pls++; //Aumenta el numero de peliculas en archivo
		
		f = l; //Se convierte la linea a string
		i = 0;
		if(f.empty())
			continue;

		while(i<6){ //Formatea la cadena del archivo y extrae informacion de pelicula
			prevpos = pos;
			pos = f.find("|");
			if(i==0) //Primer iteracion es el codigo
				c = f.substr(0,pos);
			if(i==1) //Titulo de pelicula
				t = f.substr(0,pos);
			if(i==2) //Director
				d = f.substr(0,pos);
			if(i==3) //Año
				a = f.substr(0,pos);
			if(i==4) //Numero de rentas
				r = f.substr(0,pos);
			if(i==5) //Numero de copias disponibles
				co = f;
				
			f = f.substr(pos+1); //Cambia el string que se formatea
			i++;
		}			
		
		//Se crea un nuevo objeto 
		Pelicula *pe = new Pelicula(atoi(c.c_str()),t,d,atoi(a.c_str()),atoi(r.c_str()),atoi(co.c_str())); 


		//Una nueva estructura para guardar el objeto y el apuntador al que le sigue
		Pelis *nueva;

		//Crea memoria dinamica para el nuevo elemento de la lista
		if((nueva = (Pelis *)malloc(sizeof(Pelis))) == NULL ){
			cout<<" Ha ocurrido un error al cargar la pelicula"<<t<<". \n";
			continue;
		}

		//Si la lista esta vacia entonces el elemento que le sigue sera nulo
		if(p->h == NULL)
			nueva->sig = NULL;
		else //Si ya hay elementos, se guarda la direccion 
			//del elemento registrado una vez antes
			nueva->sig = p->h;

		

		nueva->p = pe;
		//Asigna la cabecera de la pila que se recibe por referencia
		//Y asi cambia el inicio de la pila en "int main()"
		p->h = nueva;
	}
	
	//Cierra el archivo
	archivo_lectura.close();
	return pls;
	system("PAUSE");
}

int main(){
	char op;
	int pls = 0;


	Piila peliculas;
	peliculas.h = NULL;

	pls = inicio(&peliculas,"altas.txt");


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
			case '1': 
			{ //Se agrega pelicula
				int nCliente,nRentas,nCopias,anio;
				string archivo, titulo, director;
				pls++;
				system("CLS");
				//Se solicita la informacion de la pelicula
				cout<<"Ingrese los datos: "<<endl;
				cout<<"\t Titulo: ";
				cin>>ws;
				getline(cin,titulo);
				cout<<"\t Director: ";
				getline(cin,director);
				cout<<"\t Anio: ";
				cin>>anio;
				cout<<"\t Numero de rentas: ";
				cin>>nRentas;
				cout<<"\t Numero de Copias: ";
				cin>>nCopias;


				if(buscarPeliculaNombre(titulo,peliculas) ){
					//Busca el nombre de la pelicula, si existe no permite continuar
					cout<<"La pelicula YA EXISTE.\n\n"<<endl;
					system("PAUSE");
					continue;
				}
				/*|| buscarPelicula(code,peliculas)*/
				//Se crea objeto Pelicula para almacenar en arreglo
				Pelicula *p = new Pelicula(pls,titulo,director,anio,nRentas,nCopias); 

				//Se agrega al arreglo

				system("CLS");
				//Se le indica al objeto que se guarde en archivo
				
				
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

				//Se borrara de la parte logica, en el archivo se borrara al final siempre.

				Pelis *aux,*prev,*del;
				aux = peliculas.h;
				prev = aux;
				int it = 0;
				while(aux != NULL){ //Recorre la pila y borra cuando encuentra el codigo
					if(aux->p->getCodigo() == code){
						del = aux;

						if(it == 0) 
							peliculas.h = aux->sig;
						else
							prev->sig = aux->sig;

						delete del;
						pls--; //Hay una pelicula menos

						if(pls<=0) //Si ya no hay pelicula se pone la cabecera en NULL
							peliculas.h = NULL;


						break;
					}

					it++;
					prev = aux;
					aux = aux->sig;
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

	//Guarda las peliculas al finalizar el programa
	guardar(peliculas,"altas.txt");
	
	return 0;
}


