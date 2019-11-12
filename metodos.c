#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
char BUFFER[MAX]={'\0'};

struct cliente{
		int numero;
		char *calle, *municipio;
	
	int ID, telefono, estado/*1 alta 0, baja*/;
	char *nombre, *correo;
	char* notas;
	struct cliente* next;
};
typedef struct cliente CLIENTE_N;
typedef CLIENTE_N* CLIENTES;

struct libro{
	int ID, anio_p, ISBN, tipo, precio;
	char *titulo, *autor, *editorial, *notas;
	struct libro* next;
};
typedef struct libro LIBRO_N;
typedef LIBRO_N* LIBROS;

char* stringProcess();
int agregarClientes(CLIENTES*, int);
int agregarLibros(LIBROS*, int);
void imprimirClientes(CLIENTES);
void imprimirLibros(LIBROS);


int agregarCliente(CLIENTES* lista_c, int ID){
	CLIENTE_N* nodo_n = (CLIENTE_N*) malloc(sizeof(CLIENTE_N));
	nodo_n->ID = ++ID; 
	nodo_n->estado = 1;
	nodo_n->next = NULL; 
	printf("Ingresa el nombre completo: ");fflush(stdin);
	nodo_n->nombre = stringProcess();
	printf("Ingresa el correo: ");fflush(stdin);
	nodo_n->correo = stringProcess();
	printf("Ingresa el numero de telefono: ");fflush(stdin);
	scanf("%d", &nodo_n->telefono);
	printf("\t--- D I R E C C I O N ---\nIngresa el municipio : "); fflush(stdin);
	nodo_n->municipio = stringProcess();
	printf("Ingresa la calle: ");fflush(stdin);
	nodo_n->calle = stringProcess();
	printf("Ingresa el numero de casa: ");fflush(stdin);
	scanf("%d", &(nodo_n->numero));
	if(*lista_c == NULL)
		*lista_c = nodo_n;
	else{
		nodo_n->next = *lista_c;
		*lista_c = nodo_n; 
	}
	
	return ID;
}

int agregarLibro(LIBROS* lista_l, int ID){
	LIBRO_N* nodo_l = (LIBRO_N*) malloc(sizeof(LIBRO_N));
	nodo_l->ID = ++ID;
	nodo_l->next = NULL; fflush(stdin);
	do{
		printf("Tipo de libro:\n1 - Renta\n2 - Venta\n3 - Solo lectura\nOPCION: ");fflush(stdin);
		scanf("%d", &(nodo_l->tipo));
	}while(nodo_l->tipo >0 && nodo_l->tipo <4);
	printf("Ingresa el titulo del libro: ");
	nodo_l->titulo = stringProcess();
	printf("Ingresa el autor: ");
	nodo_l->autor = stringProcess();
	printf("Ingresa la editorial: ");
	nodo_l->editorial = stringProcess();
	printf("Ingresa el a%co de publicacion: ", 164);
	scanf("%d", &(nodo_l->anio_p));
	printf("Ingresa el ISBN: ");
	scanf("%d", &(nodo_l->ISBN));
	printf("Ingresa el precio: ");
	scanf("%d", &(nodo_l->precio));	
	if(*lista_l == NULL){
		*lista_l = nodo_l;
	}else{
		nodo_l->next = *lista_l;
		*lista_l = nodo_l;
	}
	
	return ID;
}

void imprimirLibro(LIBROS lista_l){
	while(lista_l != NULL){
		printf("ID: %d\nTipo: ", lista_l->ID);
		printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista_l->titulo, lista_l->autor, lista_l->editorial);
		printf("A%co de publicacion: %d\nISBN: %d\nPPrecio: ", 164, lista_l->anio_p, lista_l->ISBN, lista_l->precio);
	}
}

void editarCliente(CLIENTES lista_c){
	int opcion, flag=1;
	printf("\t--- CLIENTES ---\n");
	while(lista_c != NULL){
		if(lista_c->estado == 1){
			printf("ID: %d\t-\t%s\n", lista_c->ID, lista_c->nombre);
		}
		lista_c = lista_c->next;
	}
		printf("0 \t-\t Salir\tSELECCIONE(ID): "); fflush(stdin);
	do{
		scanf("%d", &opcion);
		while(lista_c != NULL){
			if(lista_c->ID == opcion || opcion == 0){
				flag=0;
				break;
			}
			lista_c = lista_c->next;
		}
		if(flag){
			printf("ID no dado de alta. Ingrese un ID valido: "); fflush(stdin);
		}
	}while(flag);
	if(opcion == 0){
		return;
	}
	flag = 0;
	printf("[1] - Nombre: %s\n[2] - Correo: %s\n[3] - Telefono: %d\n", lista_c->nombre, lista_c->correo, lista_c->telefono);
	printf("[4] - Calle: %s\n[5] - Municipio: %s\n[6] - Numero de casa: %d", lista_c->calle, lista_c->municipio, lista_c->numero);
	printf("\tSeleccione: ");
	do
	{
		scanf("%d", &opcion);
		if(opcion < 1 && opcion > 6){
			printf("Ingrese una opcion valida: "); fflush(stdin);
			flag = 1;
		}
	}while(flag);
	switch(opcion){
		case 1: 
			printf("Nuevo nombre: "); fflush(stdin);
			free(lista_c->nombre);
			lista_c->nombre = stringProcess();
			break;
		case 2:
			printf("Nuevo correo: "); fflush(stdin);
			free(lista_c->correo);
			lista_c->correo = stringProcess();
			break;	
		case 3:
			printf("Nuevo telefono: "); fflush(stdin);
			scanf("%d", &(lista_c->telefono));
			break;
		case 4:
			printf("Nueva calle: "); fflush(stdin);
			free(lista_c->calle);
			lista_c->calle = stringProcess();
			break;
		case 5: 
			printf("Nuevo municipio: "); fflush(stdin);
			free(lista_c->municipio);
			lista_c->municipio = stringProcess();
			break;
		case 6: 
			printf("Nuevo numero de casa: "); fflush(stdin);
			scanf("%d", &(lista_c->numero));
	}
}

void imprimirClientes(CLIENTES lista_c){
	while(lista_c != NULL){
		printf("ID: %d\nNombre: %s\nCorreo: %s\nTelefono: %d\n", lista_c->ID, lista_c->nombre, lista_c->correo, lista_c->telefono);
		printf("--- DIRECCION ---\nCalle: %s\nMunicipio: %s\n Numero de casa: %d", lista_c->calle, lista_c->municipio, lista_c->numero);
		lista_c = lista_c->next;
	}
}

char* stringProcess(){
	int lng;
	fgets(BUFFER, MAX, stdin);
	lng = strlen(BUFFER);
	--lng;
	char* string = (char*)malloc(lng * sizeof(char));
	strncpy(string, BUFFER, lng);
	return string;
}
