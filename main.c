#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"./metodos.c"

int main(){
	
	CLIENTES lista_c = NULL;
	LIBROS lista_l = NULL;
	
	int ID_c = 0;	
	int ID_l = 0;	
		
	int op1,op2,op3;
	int x;
	
	ID_c = cargarClientes(&lista_c,ID_c);
	ID_l = cargarLibros(&lista_l,ID_l);
		
	do
	{
		system("cls");

// COMPROBACION DE MOVIMIENTOS //
		
	imprimirClientes(lista_c);
	printf("\n\nLIBROS\n\n");
	imprimirLibros(lista_l);
	
	//	actualizarClientes(lista_c);
///////

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
						ID_c = agregarClientes(&lista_c, ID_c);							
						break;
		
					case 2:
						if(lista_c != NULL)
							editarCliente(lista_c);	
						else
							printf("La lista está vacia, ingrese datos porfavor");
							getch();
					break;

					case 3:
<<<<<<< HEAD
						if(lista_c != NULL)
							bajaCliente(&lista_c);	
						else
							printf("La lista está vacia, ingrese datos porfavor");
							getch();	
=======
						printf("\nINGRESE EL CLIENTE A ELIMINAR: ");
						scanf("%d",&x);
						bajaCliente(&lista_c, x);
>>>>>>> master
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
		
					break;

					case 3:
						printf("\nINGRESE EL LIBRO A ELIMINAR: ");
						scanf("%d",&x);
						bajaLibro(&lista_l, x);		
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
				printf("\n[4] REGRESAR LIRBO");						
				printf("\n\n\t\t\t\tSELECCIONE OPCION: ");	
				scanf("%d",&op2);
				
				switch(op2)
				{
					case 1:
							
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
							
					break;
		
					case 2:
						system("cls");		
						printf("\t\tBUSCAR POR LIBRO\n");
						printf("\n[1] BUSQUEDA POR TITULO");
						printf("\n[2] BUSQUEDA POR AUTOR");	
						printf("\n[3] BUSQUEDA POR ISBN");					
						printf("\n\n\t\t\t\tSELECCIONE OPCION: ");	
						scanf("%d",&op3);
						
						switch(op3)
						{
							case 1:
									
							break;
				
							case 2:
				
							break;
		
							case 3:
				
							break;
		
							default:
								printf("\nOPCION NO VALIDA, PRECIONE CUALQUIER TECLA PARA CONTINUAR");
								getch();
							break;
						}		
		
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
