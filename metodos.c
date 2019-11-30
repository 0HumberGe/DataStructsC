#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 150
char BUFFER[MAX]={'\0'};


struct nota{
	char *texto;
	struct nota *next;
};
typedef struct nota NOTA_N;
typedef NOTA_N *NOTAS;

struct cliente{
	int numero;
	char *calle, *municipio;
	int ID;
	unsigned long long int telefono;
	char *nombre, *correo;
	NOTAS LISTA_DE_NOTAS;
	int cantidad_de_notas;
	struct cliente* next;
};

typedef struct cliente CLIENTE_N;
typedef CLIENTE_N* CLIENTES;

struct shop_car{
	struct libro* libro;
	struct shop_car* next;
};
typedef struct shop_car SHOP_CAR_N;
typedef SHOP_CAR_N* SHOP_CAR;

struct libro{
	int ID, anio_p, tipo,estado;
	float precio;
	unsigned long long int ISBN;
	char *titulo, *autor, *editorial, *notas;
	struct libro* next;
};

typedef struct libro LIBRO_N;
typedef LIBRO_N* LIBROS;

void cargarNotas(NOTAS*);
int cargarLibros(LIBROS*,int);
char* stringProcess();

void agregarClientes(CLIENTES*);
int validarIdClientes(int, CLIENTES);

void cargarClientes(CLIENTES*);

int agregarLibros(LIBROS*, int);
void agregarNota(NOTAS*);
int idLibro(LIBROS);

void imprimirClientes(CLIENTES);

void imprimirLibros(LIBROS);
void actualizarClientes(CLIENTES);
void actualizarLibros(LIBROS);
void bajaCliente(CLIENTES*);
void bajaLibro(LIBROS*, int);
void buscarLibro(LIBROS);
void toShopCar(LIBRO_N, SHOP_CAR*);
void PrestamoSoloLectura(LIBROS, CLIENTES);
void comprarLibros(LIBROS*);
void editarCliente(CLIENTES);
void llenarBuffer();
void buscarCliente(CLIENTES);
void editarLibro(LIBROS);

FILE*archivo_viejo;
FILE*archivo_nuevo;
FILE*archivo;

void cargarClientes(CLIENTES* lista_c){
	archivo = fopen("./FILES/CLIENTES.txt","r");

	if (archivo==NULL) 
    { 
        printf("Archivo CLIENTES.txt vacio."); 
    }	
    else
    {
		while(!feof(archivo))
		{
			int size_name, size_email, size_city, size_street, cantidad_de_notas;
			fscanf(archivo, "%d %d %d %d %d ", &size_name, &size_email, &size_city, &size_street, &cantidad_de_notas);
			
			char *name = malloc(sizeof(char) * (size_name + 1));	
			name[size_name] = '\0';
	
			char *email = malloc(sizeof(char) * (size_email + 1));	
			email[size_email] = '\0';
							
			char *city = malloc(sizeof(char) * (size_city + 1));	
			city[size_city] = '\0';
	
			char *street = malloc(sizeof(char) * (size_street + 1));	
			street[size_street] = '\0';
			
			int id, numero_de_casa;
			unsigned long long int telefono;
			
			fscanf(archivo, "|%d|%150[^|]|%150[^|]|%llu|%150[^|]|%150[^|]|%d|",
			&id,
			name,
			email,
			&telefono,
			city,
			street,
			&numero_de_casa);	
			
			CLIENTE_N* nodo_n = (CLIENTE_N*) malloc(sizeof(CLIENTE_N));
			nodo_n->next = NULL; 
			nodo_n->LISTA_DE_NOTAS = NULL;
			nodo_n->ID = id; 
			nodo_n->nombre = name; 
			nodo_n->correo = email; 
			nodo_n->telefono = telefono;
			nodo_n->municipio = city; 
			nodo_n->calle = street; 		
			nodo_n->numero = numero_de_casa;
			nodo_n->cantidad_de_notas = cantidad_de_notas;
			int i;
			for(i = 0; i<cantidad_de_notas;i++){
				cargarNotas(&nodo_n->LISTA_DE_NOTAS);
			}	
			fscanf(archivo, "\n");  
			if(*lista_c == NULL)
				*lista_c = nodo_n;
			else
			{
				nodo_n->next = *lista_c;
				*lista_c = nodo_n; 
			}

		}    	
	
		fclose(archivo);
	}
}
void cargarNotas(NOTAS* LISTA_DE_NOTAS){
	NOTAS nota_n = (NOTAS) malloc(sizeof(NOTA_N));
	nota_n->next = NULL;
	
	char *auxiliarNota = malloc(sizeof(char) * (MAX));
	fscanf(archivo, "%150[^|]|", auxiliarNota);
	nota_n->texto = auxiliarNota;
	if(*LISTA_DE_NOTAS == NULL){
		*LISTA_DE_NOTAS = nota_n;
	}
	else{
		nota_n->next = *LISTA_DE_NOTAS;
		*LISTA_DE_NOTAS = nota_n; 
	}
}
int cargarLibros(LIBROS* lista_l, int ID){
	int IDD;
	
	archivo = fopen("./FILES/LIBROS.txt","r");

	if (archivo==NULL) 
    { 
        printf("COMPRUEBE QUE EL ARCHIVO LIBROS.txt ESTA CERRADO"); 
    }	
    else
    {
		while(!feof(archivo))
		{
					
			int tam_titulo,tam_autor,tam_editorial, tam_notas;
			int tipo, anio;
			float precio;
			unsigned long long int ISBN;
			
			LIBRO_N* nodo_n = (LIBRO_N*) malloc(sizeof(LIBRO_N));

			fscanf(archivo,"%d ",&tam_titulo);
			fscanf(archivo,"%d ",&tam_autor);
			fscanf(archivo,"%d ",&tam_editorial);
			fscanf(archivo,"%d ",&tam_notas);
			
			char *titulo = malloc(sizeof(char) * (tam_titulo + 1));	
			titulo[tam_titulo] = '\0';
	
			char *autor = malloc(sizeof(char) * (tam_autor + 1));	
			autor[tam_autor] = '\0';
							
			char *editorial = malloc(sizeof(char) * (tam_editorial + 1));	
			editorial[tam_editorial] = '\0';
	
			char *notas = malloc(sizeof(char) * (tam_notas + 1));	
			notas[tam_notas] = '\0';
		

			fscanf(archivo, "|%d|%d|%d|%llu|%f|%150[^|]|%150[^|]|%150[^|]|%150[^|]|\n",
			&IDD,
			&tipo,
			&anio,
			&ISBN,
			&precio,
			titulo,
			autor,
			editorial,
			notas);

			nodo_n->next = NULL; 
			nodo_n->ID = IDD;
			nodo_n->tipo = tipo; 
			nodo_n->anio_p = anio;
			nodo_n->ISBN = ISBN; 
			nodo_n->precio = precio; 
			nodo_n->titulo = titulo; 	
			nodo_n->autor = autor; 	
			nodo_n->editorial = editorial; 		
			nodo_n->notas = notas;  
							
				if(*lista_l == NULL)
					*lista_l = nodo_n;
				else
				{
					nodo_n->next = *lista_l;
					*lista_l = nodo_n; 
				}

		}    	
	
		fclose(archivo);
	}
	
	return IDD;
}
void agregarClientes(CLIENTES* lista_c)
{	
	CLIENTE_N* nodo_n = (CLIENTE_N*) malloc(sizeof(CLIENTE_N));
	nodo_n->LISTA_DE_NOTAS = NULL;
	nodo_n->cantidad_de_notas = 0;
	do{
		printf("Ingrese un id mayor a cero(unico): ");
		scanf("%d", &nodo_n->ID);
	}while(validarIdClientes(nodo_n->ID, *lista_c));
	nodo_n->next = NULL; 
	printf("Ingresa el nombre completo: ");fflush(stdin);
	nodo_n->nombre = stringProcess();
	printf("Ingresa el correo: ");fflush(stdin);
	nodo_n->correo = stringProcess();	
	printf("Ingresa el numero de telefono: ");fflush(stdin);
	scanf("%llu", &(nodo_n->telefono));
	printf("\t--- D I R E C C I O N ---\nIngresa el municipio : "); fflush(stdin);
	nodo_n->municipio = stringProcess();
	printf("Ingresa la calle: ");fflush(stdin); 
	nodo_n->calle = stringProcess();
	printf("Ingresa el numero de casa: ");fflush(stdin); 
	scanf("%d", &(nodo_n->numero));
	printf("\t--- N O T A S ---\n");
	int opcion;
	do{
		agregarNota(&nodo_n->LISTA_DE_NOTAS);
		nodo_n->cantidad_de_notas++;
		printf("Desea ingresar una nueva nota? [0]NO: ");
		scanf("%d", &opcion);
	}while(opcion != 0);
	
	if(*lista_c == NULL)
		*lista_c = nodo_n;
	else{
		nodo_n->next = *lista_c;
		*lista_c = nodo_n; 
	}
}
void agregarNota(NOTAS *LISTA_DE_NOTAS)
{
	NOTAS nota_n = (NOTAS) malloc(sizeof(NOTA_N));
	printf("\nIngresa una nota: "); fflush(stdin);
	nota_n->texto = stringProcess();
	nota_n->next = NULL;
	if(*LISTA_DE_NOTAS == NULL){
		
		*LISTA_DE_NOTAS = nota_n;
	}
	else{
		nota_n->next = *LISTA_DE_NOTAS;
		*LISTA_DE_NOTAS = nota_n; 
	}
}
int validarIdClientes(int id, CLIENTES lista_c)
{
	if(id <= 0){
		printf("El id no puede ser 0. Favor de ingresar otro\n"); // Esto nos ayuda a tener un mejor control.
		return 1;
	}
	if(lista_c == NULL){
		return 0; // Si la lista no tienen elementos NO hace una busqueda.
	}
	else{
		while(lista_c != NULL){
			if(lista_c->ID == id){
				printf("El id %d ya exista en la base de datos. Favor de ingresar otro\n", id);
				return 1;
			}
			lista_c = lista_c->next;	
		}
		return 0; // Terminó la busqueda y ningún ID concide con el introducido en la base de datos.
	}
}
void actualizarClientes(CLIENTES lista_c)
{
	FILE*archivo_nuevo;
	
	archivo_nuevo= fopen("./FILES/CLIENTES_TEMP.txt","w");
	
	if(archivo_nuevo==NULL)
	{
		printf("\nERROR AL ACTUALIZAR ARCHIVO\n");
	}
	
	else
	{
		NOTAS LISTA_DE_NOTAS;
		while(lista_c != NULL){
			
			fprintf(archivo_nuevo,"%d %d %d %d %d ",
			strlen(lista_c->nombre),
			strlen(lista_c->correo),
			strlen(lista_c->municipio),
			strlen(lista_c->calle),
			lista_c->cantidad_de_notas);
			
			fprintf(archivo_nuevo,"|%d|%s|%s|%llu|%s|%s|%d|",
			lista_c->ID,
			lista_c->nombre,
			lista_c->correo,
			lista_c->telefono,
			lista_c->municipio,
			lista_c->calle,
			lista_c->numero);
			LISTA_DE_NOTAS = NULL;
			LISTA_DE_NOTAS = lista_c->LISTA_DE_NOTAS;
			while(LISTA_DE_NOTAS != NULL){
				fprintf(archivo_nuevo, "%s|", LISTA_DE_NOTAS->texto);
				LISTA_DE_NOTAS = LISTA_DE_NOTAS->next;	
			}
			fprintf(archivo_nuevo, "\n");
			lista_c = lista_c->next;
			
		}
	fclose(archivo_nuevo);
	remove("./FILES/CLIENTES.txt");
	rename("./FILES/CLIENTES_TEMP.txt","./FILES/CLIENTES.txt");
	}	
}
void actualizarLibros(LIBROS lista_l)
{
	FILE*archivo_nuevo;

	archivo_nuevo= fopen("./FILES/LIBROS_TEMP.txt","w");

	if(archivo_nuevo==NULL)
	{
		printf("\nERROR AL ACTUALIZAR ARCHIVO\n");
	}

	else
	{
		while(lista_l != NULL){
			fprintf(archivo_nuevo,"%d %d %d %d ",
			strlen(lista_l->titulo),
			strlen(lista_l->autor),
			strlen(lista_l->editorial),
			strlen(lista_l->notas));

			fprintf(archivo_nuevo,"|%d|%d|%d|%llu|%f|%s|%s|%s|%s|\n",
			lista_l->ID,
			lista_l->tipo,
			lista_l->anio_p,
			lista_l->ISBN,
			lista_l->precio,
			lista_l->titulo,
			lista_l->autor,
			lista_l->editorial,
			lista_l->notas);

			lista_l = lista_l->next;
		}

	fclose(archivo_nuevo);
	remove("./FILES/LIBROS.txt");
	rename("./FILES/LIBROS_TEMP.txt","./FILES/LIBROS.txt");
	}
}
int agregarLibros(LIBROS* lista_l, int ID)
{
	
	LIBRO_N* nodo_l = (LIBRO_N*) malloc(sizeof(LIBRO_N));
	nodo_l->ID = ++ID;
	nodo_l->estado=1;
	nodo_l->next = NULL; fflush(stdin);
	do{
		printf("Tipo de libro:\n1 - Renta\n2 - Venta\n3 - Solo lectura\nOPCION: ");
		fflush(stdin);
		scanf("%d", &nodo_l->tipo);
	}while(nodo_l->tipo <0 && nodo_l->tipo >4);
	
	fflush(stdin);
	
	printf("Ingresa el titulo del libro: "); fflush(stdin); 
	nodo_l->titulo = stringProcess();
	printf("Ingresa el autor: "); fflush(stdin);
	nodo_l->autor = stringProcess();
	printf("Ingresa la editorial: "); fflush(stdin);
	nodo_l->editorial = stringProcess();
	printf("Ingresa el a%co de publicacion: ", 164);
	scanf("%d", &(nodo_l->anio_p));
	printf("Ingresa el ISBN: ");
	scanf("%llu", &(nodo_l->ISBN));
	printf("Ingresa el precio: ");
	scanf("%f", &(nodo_l->precio));	
	if(*lista_l == NULL){
		*lista_l = nodo_l;
	}else{
		nodo_l->next = *lista_l;
		*lista_l = nodo_l;
	}
	return ID;
}
int validarIdLibros(int id, LIBROS lista_l){
		if(id <= 0){
		printf("El id no puede ser 0. Favor de ingresar otro\n"); // Esto nos ayuda a tener un mejor control.
		return 1;
	}
	if(lista_l == NULL){
		return 0; // Si la lista no tienen elementos NO hace una busqueda.
	}
	else{
		while(lista_l != NULL){
			if(lista_l->ID == id){
				printf("El id %d ya exista en la base de datos. Favor de ingresar otro\n", id);
				return 1;
			}
			lista_l = lista_l->next;	
		}
		return 0; // Terminó la busqueda y ningún ID concide con el introducido en la base de datos.
	}
}
void imprimirLibros(LIBROS lista_l){
	while(lista_l != NULL){
		printf("ID: %d\nTipo: %d ", lista_l->ID, lista_l->tipo);
			switch(lista_l->tipo){case 1: printf("(Renta)"); break; case 2: printf("(Venta)"); break; case 3: printf("(Solo lecutra)"); break; }
		printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista_l->titulo, lista_l->autor, lista_l->editorial);
		printf("A%co de publicacion: %d\nISBN: %llu\nPrecio: %.2f", 164, lista_l->anio_p, lista_l->ISBN, lista_l->precio);
		printf("\n\n");		
		lista_l = lista_l->next;	
	}
}
void editarCliente(CLIENTES lista_c){
	CLIENTES lista_c_auxiliar = lista_c; // Es necesario crear un auxiliar para recorrer dos veces la lista.
	
	printf("\n\t--- CLIENTES ---\n");
	printf(" %-20s %-50s\n", "ID", "NOMBRE");
	while(lista_c != NULL){
			printf(" %-20d %-50s\n", lista_c->ID, lista_c->nombre); 
		lista_c = lista_c->next;
	} // Imprime la lista de clientes.
	printf("\n[0] Regresar");
	int opcion;
	int flag = 0;
	do{
		printf("\n\n\t\t\t\tSELECCIONE UN CLIENTE: "); fflush(stdin);
		scanf("%d", &opcion);
		if(opcion == 0){
			break;
		}
		while(lista_c_auxiliar != NULL){
			if(lista_c_auxiliar->ID == opcion){
				flag = 1;
				break;
			}
			lista_c_auxiliar = lista_c_auxiliar->next;
		}
		if(flag != 1){
			printf("\nID del cliente no encontrado. Favor de comprobar.");
			system("pause");
			break;
		}
		else{
			printf("[1] - Nombre: %s\n[2] - Correo: %s\n[3] - Telefono: %llu\n", lista_c_auxiliar->nombre, lista_c_auxiliar->correo, lista_c_auxiliar->telefono);
			printf("[4] - Calle: %s\n[5] - Municipio: %s\n[6] - Numero de casa: %d\n", lista_c_auxiliar->calle, lista_c_auxiliar->municipio, lista_c_auxiliar->numero);
			printf("\tSELECCIONE UNA OPCION: ");
			do{
				scanf("%d", &opcion);
				if(opcion < 1 && opcion > 6){
					printf("Ingrese una opcion valida: "); fflush(stdin);
				}
				}while(opcion < 1 && opcion > 6);
				switch(opcion){
					case 1: 
						printf("Nuevo nombre: "); fflush(stdin);
						free(lista_c_auxiliar->nombre);
						lista_c_auxiliar->nombre = stringProcess();
						break;
					case 2:
						printf("Nuevo correo: "); fflush(stdin);
						free(lista_c_auxiliar->correo);
						lista_c_auxiliar->correo = stringProcess();
						break;	
					case 3:
						printf("Nuevo telefono: "); fflush(stdin);
						scanf("%llu", &(lista_c_auxiliar->telefono));
						break;
					case 4:
						printf("Nueva calle: "); fflush(stdin);
						free(lista_c_auxiliar->calle);
						lista_c_auxiliar->calle = stringProcess();
						break;
					case 5: 
						printf("Nuevo municipio: "); fflush(stdin);
						free(lista_c_auxiliar->municipio);
						lista_c_auxiliar->municipio = stringProcess();
						break;
					case 6: 
						printf("Nuevo numero de casa: "); fflush(stdin);
						scanf("%d", &(lista_c_auxiliar->numero));
				}
				break;
			}
	}while(opcion != 0);
}
void editarLibro(LIBROS lista_l){
	int opcion, flag = 1;
	LIBROS aux_l = lista_l;
	printf("\t--- LIBROS ---\n");
	while(lista_l != NULL){
		printf("ID: %d\t-\t%s\n", lista_l->ID, lista_l->titulo);
		lista_l = lista_l->next;
	}
	printf("0 \t-\tSalir\tSELECCIONE (ID): "); fflush(stdin);
	do{
		lista_l = aux_l;
		scanf("%d", &opcion);
		while(lista_l != NULL){
			if(lista_l->ID == opcion || opcion == 0){
				flag=0;
				break;
			}
			lista_l = lista_l->next;
		}
		if(flag){
			printf("ID no dado de alta. Ingrese un ID valido:");
		}
	}while(flag);
	if(opcion == 0){
		return;
	}
	flag=0;
	printf("[1] - Titulo: %s\n[2] - Autor: %s\n[3] - Editorial: %s\n", lista_l->titulo, lista_l->autor, lista_l->editorial);
	printf("[4] - ISBN: %llu\n[5] - Precio: %d\n[6] - Tipo de libro: %d\n", lista_l->ISBN, lista_l->precio, lista_l->tipo);
	printf("[7] - A%co de publicacion: %d\n\tSeleccione: ", 164, lista_l->anio_p);
	do
	{
		scanf("%d", &opcion);
		if(opcion < 1 && opcion >6){
			printf("Ingrese una opcion valida: "); fflush(stdin);
			flag=1;
		}
	}while(flag);
	switch(opcion){
		case 1: 
			printf("Nuevo titulo: "); fflush(stdin);
			free(lista_l->titulo);
			lista_l->titulo = stringProcess();
			break;
		case 2:
			printf("Nuevo autor: ");fflush(stdin);
			free(lista_l->autor);
			lista_l->autor = stringProcess();
			break;
		case 3:
			printf("Nueva editorial: "); fflush(stdin);
			free(lista_l->editorial);
			lista_l->editorial = stringProcess();
			break;
		case 4:
			printf("Nuevo ISBN: ");
			scanf("%llu", &(lista_l->ISBN));
			break;
		case 5:
			printf("Nuevo precio: ");
			scanf("%f", &(lista_l->precio));
			break;
		case 6:
			do{
				printf("Nuevo tipo de libro:\n1 - Renta\n2 - Venta\n3 - Solo lectura\nOPCION: ");fflush(stdin);
				scanf("%d", &(lista_l->tipo));
			}while(lista_l->tipo < 0 && lista_l->tipo > 4);
			break;
		case 7: 
			printf("Nuevo a%co de publicacion: ", 164);
			scanf("%d", &(lista_l->anio_p));
	}
}
void imprimirClientes(CLIENTES lista_c){
	while(lista_c != NULL){
		printf("ID: %d\nNombre: %s\nCorreo: %s\nTelefono: %llu\n", lista_c->ID, lista_c->nombre, lista_c->correo, lista_c->telefono);
		printf("--- DIRECCION ---\nMunicipio: %s\nCalle: %s\nNumero de casa: %d", lista_c->municipio, lista_c->calle, lista_c->numero);
		printf("%\n--- NOTAS ---");
		NOTAS LISTA_DE_NOTAS = lista_c->LISTA_DE_NOTAS; // Se tiene que hacer un auxiliar.
		while( LISTA_DE_NOTAS != NULL){	
			printf("\n%s", LISTA_DE_NOTAS->texto);
			LISTA_DE_NOTAS = LISTA_DE_NOTAS->next;
		}
		printf("\n\n");
		lista_c = lista_c->next;
	}
}
void bajaCliente(CLIENTES* lista_c){
	CLIENTES aux_c = *lista_c;
	int ID, flag=1;
	printf("\t--- CLIENTES ---\n");
	while(*lista_c != NULL){
		printf("ID: %d\t-\t%s\n", (*lista_c)->ID, (*lista_c)->nombre);
		*lista_c = (*lista_c)->next;
	}
		printf("0 \t-\t Salir\t\nSELECCIONE(ID): "); fflush(stdin);
	do{
		scanf("%d", &ID);
		*lista_c = aux_c;
		while(*lista_c != NULL){
			if((*lista_c)->ID == ID || ID == 0){
				flag=0;
				break;
			}
			*lista_c = (*lista_c)->next;
		}
		if(flag){
			printf("\nID no dado de alta. Ingrese un ID valido: "); fflush(stdin);
		}
	}while(flag);
	if(ID == 0)
	{
		return;
	}
	*lista_c = aux_c;
	aux_c = NULL;
	if((*lista_c)->ID == ID)
	{
		if((*lista_c)->next == NULL)
		{
			aux_c = *lista_c;
			*lista_c = NULL;
			free(aux_c);
			actualizarClientes(*lista_c);
		}else
		{
			aux_c = *lista_c;
			*lista_c = aux_c->next;	
			free(aux_c);
			actualizarClientes(*lista_c);
		}	
	}else
	{
		aux_c = *lista_c;
		while(aux_c->next != NULL)
		{
			aux_c = aux_c->next;	
		}
		if(aux_c->ID == ID)
		{
			CLIENTES previo_c = NULL;
			aux_c = *lista_c;
			while(aux_c->next != NULL)
			{
				previo_c = aux_c;
				aux_c = aux_c->next;	
			}
			free(aux_c);
			previo_c->next = NULL;	
			actualizarClientes(*lista_c);
		}else
		{
			aux_c = *lista_c;
			CLIENTES previo_c = NULL;
			while(aux_c->ID != ID && aux_c->next != NULL)
			{
				previo_c = aux_c;
				aux_c = aux_c->next;
			}
			if(aux_c->ID == ID)
			{
				previo_c->next = aux_c->next;
				free(aux_c);
				actualizarClientes(*lista_c);
			}else
				printf("\nEl cliente con ID : %d no esta dado de alta", ID);
				getch();
		}		
	}
}
void bajaLibro(LIBROS* lista_l, int ID){
	int flag=1;
	if(ID == 0)
	{
		return; //se sale por la funcion idLibro;
	}
	LIBROS aux_l = NULL;	
	if((*lista_l)->ID == ID)
	{
		if((*lista_l)->next == NULL)
		{
			aux_l = *lista_l;
			*lista_l = NULL;
			free(aux_l);
			actualizarLibros(*lista_l);
		}else
		{
			aux_l = *lista_l;
			*lista_l = aux_l->next;
			free(aux_l);
			actualizarLibros(*lista_l);
		}
	}else
	{
		aux_l = *lista_l;
		while(aux_l->next != NULL)
		{
			aux_l = aux_l->next;
		}
		if(aux_l->ID == ID)
		{
			LIBROS previo_l = NULL;
			aux_l = *lista_l;
			while(aux_l->next != NULL)
			{
				previo_l = aux_l;
				aux_l = aux_l->next;
			}
			free(aux_l);
			previo_l->next = NULL;
			actualizarLibros(*lista_l);
		}else
		{
			aux_l = *lista_l;
			LIBROS previo_l = NULL;
			while(aux_l->ID != ID && aux_l->next != NULL)
			{
				previo_l = aux_l;
				aux_l = aux_l->next;
			}
			if(aux_l->ID == ID)
			{
				previo_l->next = aux_l->next;
				free(aux_l);
				actualizarLibros(*lista_l);
			}else
				printf("\nEl libro con ID: %d, no esta dado de alta", ID);
				getch();
		}
	}	
}
void buscarLibro(LIBROS lista){
	int op, b=0;
	char auxs[20];
	int auxi;
	int contadorRenta,contadorVenta,contadorSoloLectura;
	do{
		b=0;
		LIBROS lista_l=lista; //auxiliar, no le cambié el nombre para no borrar lo que ya tenía.
		system("cls");
		printf("Buscar por: \n");
		printf("1.- Titulo. \n");
		printf("2.- Autor. \n");
		printf("3.- ISBN \n");
		printf("4.- Regresar. \n");
		printf("Opcion: ");
		scanf("%d",&op);
		contadorRenta=0;
		contadorVenta=0;
		contadorSoloLectura=0;
		system("cls");
		switch(op){
			case 1:
				fflush(stdin);
				printf("Ingrese titulo del libro: ");
				gets(auxs);
				system("cls");
				while(lista_l != NULL){
					if(stricmp(auxs,lista_l->titulo)==0){
						printf("ID: %d\nTipo: %d", lista_l->ID,lista_l->tipo);
						printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista_l->titulo, lista_l->autor, lista_l->editorial);
						printf("A%co de publicacion: %d\nISBN: %d\nPrecio: %.2f", 164, lista_l->anio_p, lista_l->ISBN, lista_l->precio);
						printf("\n\n");
						b=1;
						if(lista_l->tipo==1){
							contadorRenta++;
						}
						if(lista_l->tipo==2){
							contadorVenta++;
						}
						if(lista_l->tipo==3){
							contadorSoloLectura++;
						}
					}
					lista_l = lista_l->next;
				}
				if(b==0)
					printf("No se encontro informacion del titulo %s.\n", auxs);
				else
					printf("Libros de Venta: %d, Libros de Renta: %d, Libros de Solo Lectura: %d\n", contadorVenta, contadorRenta, contadorSoloLectura);
				printf("\n");
				system("pause");
				break;
			case 2:
				fflush(stdin);
				printf("Ingrese autor del libro: ");
				gets(auxs);
				system("cls");
				while(lista_l != NULL){
					if(stricmp(auxs,lista_l->autor)==0){
						printf("ID: %d\nTipo: %d", lista_l->ID,lista_l->tipo);
						printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista_l->titulo, lista_l->autor, lista_l->editorial);
						printf("A%co de publicacion: %d\nISBN: %d\nPrecio: %.2f", 164, lista_l->anio_p, lista_l->ISBN, lista_l->precio);
						printf("\n\n");
						b=1;
						if(lista_l->tipo==1){
							contadorRenta++;
						}
						if(lista_l->tipo==2){
							contadorVenta++;
						}
						if(lista_l->tipo==3){
							contadorSoloLectura++;
						}
					}
					lista_l = lista_l->next;
				}
				if(b==0)
					printf("No se encontro informacion del autor %s.\n", auxs);
				else
					printf("Libros de Venta: %d, Libros de Renta: %d, Libros de Solo Lectura: %d\n", contadorVenta, contadorRenta, contadorSoloLectura);
				printf("\n");
				system("pause");
				break;
			case 3:
				fflush(stdin);
				printf("Ingrese ISBN del libro: ");
				scanf("%d",&auxi);
				system("cls");
				while(lista_l != NULL){
					if(auxi==lista_l->ISBN){
						printf("ID: %d\nTipo: %d", lista_l->ID,lista_l->tipo);
						printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista_l->titulo, lista_l->autor, lista_l->editorial);
						printf("A%co de publicacion: %d\nISBN: %d\nPrecio: %.2f", 164, lista_l->anio_p, lista_l->ISBN, lista_l->precio);
						printf("\n\n");
						b=1;
						if(lista_l->tipo==1){
							contadorRenta++;
						}
						if(lista_l->tipo==2){
							contadorVenta++;
						}
						if(lista_l->tipo==3){
							contadorSoloLectura++;
						}
					}
					lista_l = lista_l->next;
				}
				if(b==0)
					printf("No se encontro informacion del ISBN %d.\n", auxi);
				else
					printf("Libros de Venta: %d, Libros de Renta: %d, Libros de Solo Lectura: %d\n", contadorVenta, contadorRenta, contadorSoloLectura);
				printf("\n");
				system("pause");
				break;
		}
	}while(op!=4);
}
void PrestamoSoloLectura(LIBROS lista, CLIENTES listaC){

	int op;
	char aux[50];//Para guardar el titulo
	unsigned long long int AUXISBN;
	int idL,idC,b;//Para validar id de libros de lectura.


	LIBROS listaaux=lista;//Creamos una lista auxiliar para guardar todos los libros. (Guarda la lista que traemos como parametro).

	CLIENTES listaauxC=listaC;

	do{
		system("cls");
		listaC=listaauxC;
		printf("Ingrese ID de cliente o [0] para regresar: ");
		scanf("%d",&idC);
		b=0;
		while(listaC!=NULL&&b==0&&idC!=0){
			if(listaC->ID==idC){
				b=1;
			}
			listaC=listaC->next;
		}
	}while(b==0&&idC!=0);
	if(idC!=0)
	{
		do{
			b=0;
			lista=listaaux;//Igualamos la lista de libros para guardarla en la auxiliar que declaramos arriba.
			system("cls");
			printf("Prestamo Solo Lectura\n");
			printf("1. Buscar por Titulo\n");
			printf("2. Buscar por ISBN\n");
			printf("3. Regresar\n");
			printf("OPCION: ");
			scanf("%d", &op);
			fflush( stdin );
			system("cls");
			switch(op){
				case 1:
					printf("Ingrese el Titulo: ");
					gets(aux);
					printf("\n");
					while(lista!=NULL){
						if(lista->estado==1&&strcmp(aux,lista->titulo)==0&&lista->tipo==3){
							printf("ID: %d\nTipo: %d", lista->ID,lista->tipo);
							printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista->titulo, lista->autor, lista->editorial);
							printf("A%co de publicacion: %d\nISBN: %d", 164, lista->anio_p, lista->ISBN);
							printf("\n\n");
							b=1;
						}
						lista=lista->next;
					}
					if(b==1)//Si b es igual a 1 significa que hay libros con ese titulo disponibles
						do{
							lista=listaaux;
							printf("Introduzca ID de libro para lectura o [0] para regresar: ");
							scanf("%d",&idL);
							b=0;
							if(idL!=0){
								while(lista!=NULL&&b==0){
									if(lista->estado==1&&strcmp(aux,lista->titulo)==0&&lista->tipo==3&&lista->ID==idL){
										b=1;
										lista->estado=0;
									}
									lista=lista->next;
								}
								if(b==0)
									printf("El ID no es valido.\n");
								else
								{
									printf("Prestamo de solo lectura exitoso.\n");
									system("pause");
								}
							}
						}while(b==0&&idL!=0);
					else{
						printf("No hay libros disponibles\n");
						system("pause");
					}
				break;
				case 2:
					printf("Ingrese el ISBN: ");
					scanf("%llu", &AUXISBN);
					printf("\n");
					while(lista!=NULL){
						if(lista->estado==1&&AUXISBN==lista->ISBN&&lista->tipo==3){
							printf("ID: %d\nTipo: %d", lista->ID,lista->tipo);
							printf("\nTitulo: %s\nAutor: %s\nEditorial: %s\n", lista->titulo, lista->autor, lista->editorial);
							printf("A%co de publicacion: %d\nISBN: %d", 164, lista->anio_p, lista->ISBN);
							printf("\n\n");
							b=1;
						}
						lista=lista->next;
					}
					if(b==1)//Si b es igual a 1 significa que hay libros con ese titulo disponibles
						do{
							lista=listaaux;
							printf("Introduzca ID de libro para lectura o [0] para regresar: ");
							scanf("%d",&idL);
							b=0;
							if(idL!=0){
								while(lista!=NULL&&b==0){
									if(lista->estado==1&&AUXISBN==lista->ISBN&&lista->tipo==3&&lista->ID==idL){
										b=1;
										lista->estado=0;
									}
									lista=lista->next;
								}
								if(b==0)
									printf("El ID no es valido.\n");
								else
								{
									printf("Prestamo de solo lectura exitoso.\n");
									system("pause");
								}
							}
						}while(b==0&&idL!=0);
					else{
						printf("No hay libros disponibles\n");
						system("pause");
					}
				break;	
			}
		}while(op!=3);
	}
}

void comprarLibros(LIBROS* lista_l){
	SHOP_CAR lista_s = NULL, aux_s = NULL, previo_s = NULL;
	LIBROS aux_l = NULL;
	int opcion, flag, dato_centi;
	char *titulo = NULL;
	float subTotal = 0, IVA = 0, total = 0, pago = 0, cambio = 0;
	unsigned long long int ISBN_aux;

	printf("---\tCOMPRAR LIBROS\t---\n");
	do{
		printf("1. Buscar por titulo\n2. Buscar por ISBN\n\t\tOPCION: ");
		do{
			fflush(stdin);
			scanf("%d", &opcion);
			if(opcion != 1 && opcion != 2)
				printf("Ingresa un dato valido: ");
		}while(opcion != 1 && opcion != 2);
		switch(opcion){
			case 1:
				dato_centi = 0;
				aux_l = *lista_l;
				flag = 0;
				printf("Ingrese el titulo del libro: ");fflush(stdin);
				titulo = stringProcess();
				while(aux_l != NULL){
					if(strcmp(titulo, aux_l->titulo) == 0 && aux_l->tipo == 2){
						flag = 1;
						break;
					}
					aux_l = aux_l->next;
				}
				if(flag == 0){
					printf("No se ha encontrado ningun titulo coincidente\n");
					break;
				}
				printf("Libro coincidente: \n");
				printf("Titulo: %s  -  ISBN: %llu   -   Precio: %.2f\n", aux_l->titulo, aux_l->ISBN, aux_l->precio);
				printf("Desea a%cadir el libro al carrito: 1. SI\t2. NO\n\tOPCION: ", 164);
				do{
					fflush(stdin);
					scanf("%d", &dato_centi);
					if(dato_centi != 1 && dato_centi != 2)
						printf("Ingrese un dato valido: ");
				}while(dato_centi != 1 && dato_centi != 2);
				if(dato_centi == 1)
					toShopCar(*(aux_l), &lista_s);
				break;
			case 2:
				dato_centi = 0;
				flag = 0;
				aux_l = *lista_l;
				printf("Ingrese el ISBN del libro: "); fflush(stdin);
				scanf("%llu", &ISBN_aux);
				while(aux_l != NULL){
					if(aux_l->ISBN == ISBN_aux && aux_l->tipo == 2){
						flag = 1;
						break;
					}
					aux_l = aux_l->next;
				}
				if(flag == 0){
					printf("No se ha encontrado ningun ISBN coincidente\n");
					break;
				}
				printf("Libro coincidente: \n");
				printf("Titulo: %s  -  ISBN: %llu   -   Precio: %.2f\n", aux_l->titulo, aux_l->ISBN, aux_l->precio);
				printf("Desea a%cadir el libro al carrito: 1. SI\t2. NO\n\t", 164);
				do{
					fflush(stdin);
					scanf("%d", &dato_centi);
					if(dato_centi != 1 && dato_centi != 2)
						printf("Ingrese un dato valido: ");
				}while(dato_centi != 1 && dato_centi != 2);
				if(dato_centi == 1)
					toShopCar(*(aux_l), &lista_s);
				break;
		}
		dato_centi = 0;
		printf("Desea comprar otro libro: 1. SI\t2. NO\n\tOPCION: ");
		do{
			fflush(stdin);
			scanf("%d", &dato_centi);
			if(dato_centi != 1 && dato_centi != 2)
				printf("Ingrese un dato valido: ");
		}while(dato_centi != 1 && dato_centi != 2);
	}while(dato_centi == 1);
	if(lista_s != NULL){
		dato_centi = 0;
		aux_s = lista_s;
		system("cls");
		printf("Libros en el carrito: \n\n");
		while(aux_s != NULL){
			printf("Titulo: %s  -  ISBN: %llu   -   Precio: %.2f\n", aux_s->libro->titulo, aux_s->libro->ISBN, aux_s->libro->precio);
			subTotal += aux_s->libro->precio;
			aux_s = aux_s->next;	
		}
		IVA = subTotal * 0.16;
		total = subTotal + IVA;
		printf("\n\t\tSubTotal: %.2f\n\t\tIVA: %.2f\n\t\tTotal: %.2f\n", subTotal, IVA, total);
		printf("Desea comprar los libros: 1.SI\t2.NO\n\tOPCION: ");
		do{
			fflush(stdin);
			scanf("%d", &dato_centi);
			if(dato_centi != 1 && dato_centi != 2)
				printf("Ingrese un dato valido: ");
		}while(dato_centi != 1 && dato_centi != 2);
		if(dato_centi == 2)
			return;
		printf("Cantidad con la que pago: ");
		do{
			flag = 0;
			fflush(stdin);
			scanf("%f", &pago);
			if(pago < 0){
				flag = 1;
				printf("Ingrese una cantidad valida: ");
			}else{
				cambio = pago - total;
				if(cambio < 0){
					flag = 1;
					printf("Ingrese una cantidad valida: ");
				}
			}	
		}while(flag);
		printf("\n\n\n");
		printf("---------------- TICKET DE COMPRA ----------------\n\n");
		printf("       BIENVENIDOS A LA BIBLIOTECA D CHUCHI       \n");
		printf("            ESTE ES SU TICKET D COMPRA            \n");
		printf("   LIBRO                      ISBN          PRECIO\n\n");
		aux_s = lista_s;
		while(aux_s != NULL){
			if((strlen(aux_s->libro->titulo) -1) >= 25)
				printf(" %25s ", aux_s->libro->titulo);
			else{
				printf(" %s ", aux_s->libro->titulo); 
				int i =strlen(aux_s->libro->titulo) -1;
				for(; i < 25; i++) 
					printf(" ");
			}
			printf("  %13llu  %.2f\n\n", aux_s->libro->ISBN, aux_s->libro->precio);
			aux_s = aux_s->next;
		}
		printf("                                  SubTotal: %4.2f      \n", subTotal);
		printf("                                       IVA: %4.2f      \n", IVA);
		printf("                                    Total: %5.2f      \n\n", total);
		printf("                                  Efectivo: %4.2f      \n", pago);
		printf("                                    Cambio: %4.2f      \n\n", cambio);
		printf("               BIBLIOTECA DE CHUCHI               \n");
		printf("               CIUDAD UNIVERSITARIA               \n");
		printf("             SAN NICOLAS DE LOS GARZA             \n\n");
		printf("--------------------------------------------------\n");
		aux_s = lista_s;
		while(aux_s != NULL){
			bajaLibro(lista_l, aux_s->libro->ID);
			aux_s->libro = NULL;
			aux_s = aux_s->next;
		}
		aux_s = lista_s;
		flag = 1;
		do{
			if(aux_s->next == NULL)
			{
				flag = 0;
			}
			else{				
				previo_s = NULL;
				while(aux_s->next != NULL){
					previo_s = aux_s;
					aux_s = aux_s->next;
				}
				free(aux_s);
				previo_s->next = NULL;
				aux_s = lista_s;
			}
		}while(flag);
		free(aux_s);
	} 
}

int idLibro(LIBROS lista_l){
	LIBROS aux_l = lista_l;
	int ID, flag =1;
	printf("\t--- LIBROS ---\n");
	while(aux_l != NULL){
		printf("ID: %d\t-\t%s\n", aux_l->ID, aux_l->titulo);
		aux_l = aux_l->next;
	}
	printf("0\t-\tSalir\t\nSELECCIONE(ID): ");
	do{
		fflush(stdin);
		scanf("%d", &ID);
		aux_l = lista_l;
		while(aux_l != NULL){
			if(aux_l->ID == ID || ID == 0){
				flag = 0;
				break;
			}
			aux_l = aux_l->next;
		}
		if(flag){
		printf("ID no dado de alta. Ingrese un ID valido: ");
		}
	}while(flag);
	return ID;
}

void toShopCar(LIBRO_N libro_u, SHOP_CAR* lista_s){
	SHOP_CAR_N* nodo_s = (SHOP_CAR_N*) malloc(sizeof(SHOP_CAR_N));
	nodo_s->libro = &libro_u;
	nodo_s->next = NULL;
	if(*lista_s == NULL)
		*lista_s = nodo_s;
	else{
		SHOP_CAR aux_s = *lista_s;
		while(aux_s->next = NULL){
			aux_s = aux_s->next;
		}
		aux_s->next = nodo_s;
	}
}
void buscarCliente(CLIENTES lista){
	int aux;
	int b=0;
	CLIENTES lista_c=lista;
	printf("Introduzca ID del cliente: ");
	scanf("%d", &aux);
	system("cls");
	while(lista_c!=NULL&&b==0){
		if(aux==lista_c->ID){
			printf("ID: %d \nNombre: %s\n\n",lista_c->ID,lista_c->nombre);
			b=1;
		}
		lista_c=lista_c->next;
	}
	if(b==0)
		printf("No se encontro informacion de cliente %d.\n", aux);
	printf("\n");
	system("pause");
}
char* stringProcess(){
	int lng, i;
	llenarBuffer();
	fgets(BUFFER, MAX, stdin);
	lng = strlen(BUFFER);
	char* string = (char*)malloc(lng-1 * sizeof(char));fflush(stdin);
	for(i=0; i<lng-1; i++)
	{
		*(string+i) = toupper(BUFFER[i]);	
	}
	*(string+(lng-1)) = '\0';
	return string;
}
void llenarBuffer(){
	int i;
	for(i=0; i<MAX; i++)
	{
		BUFFER[i] = '\0';
	}
}
