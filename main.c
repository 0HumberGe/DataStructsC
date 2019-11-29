#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"./metodos.c"

int main(){
	
	CLIENTES lista_c = NULL;
	LIBROS lista_l = NULL;
	
	int ID_l = 0;	
		
	int op1,op2,op3;
	int x;
	ID_l = cargarLibros(&lista_l,ID_l);
		
	do
	{
		system("cls");

// COMPROBACION DE MOVIMIENTOS //
	if(lista_c == NULL){
		cargarClientes(&lista_c); // Solo si está vacía la lista se cargaran los datos.
	}
	
	imprimirClientes(lista_c);
	printf("\n\nLIBROS\n\n");
	imprimirLibros(lista_l);

		printf("\n\t\tMENU PRINCIPAL\n");
		printf("\n[1] CLIENTES");
		printf("\n[2] LIBROS");
		printf("\n[3] BIBLIOTECA");
		printf("\n[4] INVENTARIO");
		printf("\n[5] SALIR");
		printf("\n\n\t\t\t\tSELECCIONE OPCION: ");
		scanf("%d",&op1);
		system("cls");
		switch(op1)
		{
			case 1: 
				printf("\t\tCLIENTES\n");
				printf("\n[1] NUEVO CLIENTE");
				printf("\n[2] EDITAR CLIENTE");	
				printf("\n[3] ELIMINAR CLIENTE");					
				printf("\n\n\t\t\t\tSELECCIONE OPCION: ");	
				scanf("%d",&op2);
				
				switch(op2)
				{
					case 1:
						agregarClientes(&lista_c);
						actualizarClientes(lista_c);							
						break;
		
					case 2:
						if(lista_c != NULL){
							editarCliente(lista_c);
							actualizarClientes(lista_c);
						}
						else{
							printf("La lista esta vacia, porfavor ingrese datos");
							getch();
							}
					break;

					case 3:
						if(lista_c != NULL){
							bajaCliente(&lista_c);
							actualizarClientes(lista_c);
							}
						else
						{
							printf("La lista esta vacia, porfavor ingrese datos");
							getch();
						}
					break;

					default:
						printf("\nOPCION NO VALIDA, PRECIONE CUALQUIER TECLA PARA CONTINUAR");
						getch();
					break;
				}
				
			break;
	
			case 2: 
				printf("\t\tLIBROS\n");
				printf("\n[1] NUEVO LIBRO");
				printf("\n[2] EDITAR LIBRO");	
				printf("\n[3] ELIMINAR LIBRO");					
				printf("\n\n\t\t\t\tSELECCIONE OPCION: ");	
				scanf("%d",&op2);
				
				switch(op2)
				{
					case 1:
						ID_l = agregarLibros(&lista_l, ID_l);							
					break;
		
					case 2:
						if(lista_l != NULL)
							editarLibro(lista_l);
						else
							printf("\nLa lista esta vacia, porfavor ingrese datos");
					break;

					case 3:
						if(lista_l != NULL)
							bajaLibro(&lista_l, idLibro(lista_l));
						else
							printf("\nLa lista esta vacia, porfavor ingrese datos.");		
					break;

					default:
						printf("\nOPCION NO VALIDA,PRECIONE CUALQUIER TECLA PARA CONTINUAR");
						getch();
					break;
				}
					
			break;
	
			case 3: 
				printf("\t\tBIBLIOTECA\n");
				printf("\n[1] COMPRAR LIBRO");
				printf("\n[2] RENTAR LIBRO");	
				printf("\n[3] LEER EN SALA");
				printf("\n[4] REGRESAR LIBRO");						
				printf("\n\n\t\t\t\tSELECCIONE OPCION: ");	
				scanf("%d",&op2);
				
				switch(op2)
				{
					case 1:
							if(lista_l != NULL)
								comprarLibros(&lista_l);
							else
								printf("Porfavor agrega libros al inventario");
					break;
		
					case 2:
		
					break;

					case 3:
		
					break;

					case 4:
		
					break;

					default:
						printf("\nOPCION NO VALIDA, PRECIONE CUALQUIER TECLA PARA CONTINUAR");
						getch();
					break;
				}
				
						
			break;		
			
			case 4:
				printf("\t\tINVENTARIO\n");
				printf("\n[1] BUSCAR POR CLIENTE");
				printf("\n[2] BUSCAR POR LIBRO");				
				printf("\n\n\t\t\t\tSELECCIONE OPCION: ");	
				scanf("%d",&op2);
				
				switch(op2)
				{
					case 1:
							if(lista_c != NULL)
								buscarCliente(lista_c);
							else
								printf("\nLa lista esta vacia, porfavor ingrese datos");	
					break;
		
					case 2:
							if(lista_l != NULL)
								buscarLibro(lista_l);
							else
								printf("\nLa lista esta vacia, porfavor ingrese datos");
					break;

					default:
						printf("\nOPCION NO VALIDA");
					break;
				}				
				
			break;

			case 5:
				printf("\nPROGRAMA TERMINADO, PRESIONE CUALQUIER TECLA PARA CERRAR");
				getch();
			break;
						
			default:
				printf("\nOPCION NO VALIDA, PRESIONE CUALQUIER TECLA PARA CONTINUAR");
				getch();
			break;		
		}
	
	}while(op1!=5);
	
}
