/*
 * Pedido.c
 *
 *  Created on: 13 oct. 2021
 *      Author: Usuario
 */
#include "Pedido.h"

void InicializarPedidos(ePedidos listaPedidos[], int tamPedidos)
{
	int i;

    if (listaPedidos != NULL && tamPedidos > 0) {
    	for(i=0; i<tamPedidos; i++)
    	{
    		listaPedidos[i].isEmptyPedidos = LIBRE;
    	}
    }
}


void HarcodearPedidos(ePedidos listaPedidos[])
{


    int idPedidos[]={1, 2, 3};
    int idCliente[]={1, 2, 3};
    float kilosTotales[]={10000,20000,30000};
	float kilosHDPE[]={150,8500,0};
	float kilosLDPE[]={4500,9000,0};
	float kilosPP[]={1405,10000,0};


    int i;
    for(i=0; i<3; i++)
    {
    	listaPedidos[i].idPedidos = idPedidos[i];
    	listaPedidos[i].idCliente = idCliente[i];
        listaPedidos[i].kilosTotales = kilosTotales[i];
        listaPedidos[i].kilosHDPE = kilosHDPE[i];
        listaPedidos[i].kilosLDPE = kilosLDPE[i];
        listaPedidos[i].kilosPP = kilosPP[i];
        listaPedidos[i].kilosResiduos = listaPedidos[i].kilosTotales - listaPedidos[i].kilosHDPE - listaPedidos[i].kilosLDPE -listaPedidos[i].kilosPP;

        if(i<2)
        {
        	listaPedidos[i].isEmptyPedidos = COMPLETADO;
        }
        else
        {
        	listaPedidos[i].isEmptyPedidos = PENDIENTE;
        }

    }
}





///////////////////   BUSCAR /////////////////////

int BuscarLibrePedidos(ePedidos listaPedidos[], int tamPedidos)
{
	int i;
	int indice;
	indice = -1;

	if (listaPedidos != NULL && tamPedidos > 0) {
    	for(i=0; i<tamPedidos; i++)
    	{
    		if(listaPedidos[i].isEmptyPedidos==LIBRE)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}


int BuscarPendientePedidos(ePedidos listaPedidos[], int tamPedidos)
{
	int i;
	int indice;
	indice = -1;

	if (listaPedidos != NULL && tamPedidos > 0) {
    	for(i=0; i<tamPedidos; i++)
    	{
    		if(listaPedidos[i].isEmptyPedidos==PENDIENTE)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}


int BuscarCompletadoPedidos(ePedidos listaPedidos[], int tamPedidos)
{
	int i;
	int indice;
	indice = -1;


	if (listaPedidos != NULL && tamPedidos > 0) {
    	for(i=0; i<tamPedidos; i++)
    	{
    		if(listaPedidos[i].isEmptyPedidos== COMPLETADO)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}

int BuscarCanceladoPedidos(ePedidos listaPedidos[], int tamPedidos)
{
	int i;
	int indice;
	indice = -1;
	for(i=0; i<tamPedidos; i++)
	{
		if(listaPedidos[i].isEmptyPedidos==CANCELADO)
		{
			indice = i;
			break;
		}
	}

	return indice;
}


int ePedidos_BuscarPorID(ePedidos listaPedidos[], int tamPedidos, int ID)//ver si me sirve filtrar por ocupado
{
	int retorno = -1;
	int i;


	if (listaPedidos != NULL && tamPedidos > 0)
	{
		for (i = 0; i < tamPedidos; i++)
		{
			if (listaPedidos[i].idPedidos == ID && listaPedidos[i].isEmptyPedidos == COMPLETADO)
			{
	            retorno = i;
				break;
			}
		}
	}

	return retorno;
}

///////////////////  FIN BUSCAR /////////////////////
///
/*struct
{
 int idPedidos;
 float kilosTotales;
 float kilosHDPE;
 float kilosLDPE;
 float kilosPP;
 float kilosResiduos;
  int isEmptyPedidos;
}typedef ePedidos;

• HDPE: Polietileno de alta densidad (Envases para lácteos, perfumes,
detergentes líquidos, etc.)
• LDPE: Polietileno de baja densidad (Bolsas
de congelación de alimentos, tapas flexibles o bolsas de basura.)
• PP: Polipropileno (Plásticos utilizados en la industria automovilística
y en la construcción.) El resto de la basura recolectada es desechada*/
ePedidos PedirDatosPedidos(int *retorno)
{

	ePedidos auxiliar;
	*retorno=-1;


	if(utn_getNumero(&auxiliar.idCliente, "\ningrese ID cliente", "Error", 0, 500, 2)==0 &&
		utn_getNumeroFlotante(&auxiliar.kilosTotales,"\nIngrese Kilos totales: ", "Error", 0, 800000, 2)==0)
	{
		*retorno=0;
	}

    return auxiliar;
}


int AltaPedidos(ePedidos listaPedidos[], int tamPedidos, int* idPedido)
{

	ePedidos auxiliar;
    int indice;
    int retorno;
    int confirmar;
    int datosOk;

    indice=BuscarLibrePedidos(listaPedidos, tamPedidos);


    if(indice==-1)
    {
    	retorno=  -1;
    }
    else
    {

    	 auxiliar = PedirDatosPedidos(&datosOk);
    	 if(datosOk == 0)
    	 {
			 MostrarAuxiliarPedido(auxiliar);
			 confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");

			 if(confirmar==1)
			 {

				auxiliar.idPedidos = *idPedido;
				*idPedido = *idPedido + 1;
				//SETEO ID UNICO - VARIABLE AUTOINCREMENTAL
				auxiliar.isEmptyPedidos = PENDIENTE;
				auxiliar.kilosHDPE = SIN_CLASIFICAR;
				auxiliar.kilosLDPE = SIN_CLASIFICAR;
				auxiliar.kilosPP = SIN_CLASIFICAR;
				auxiliar.kilosResiduos = SIN_CLASIFICAR;

				//SETEO EL ARRAY CON AUXILIAR EN INDEX PENDIENTE OBTENIDO PREVIAMENTE
				listaPedidos[indice] = auxiliar;
				MostrarUnPedido(auxiliar);
				//RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
				printf("ID Pedido asignado : %d \n", listaPedidos[indice].idPedidos);
				retorno= 1;
			}
			 else
			 {
				 retorno = 0;
			 }

    	 }
    	 else
    	 {
    		 retorno= -2;
    	 }

    }
    printf("retorno : %d \n", retorno);
    return retorno;
}

/////////////// FIN ALTA   /////////////////////////

/*3) Baja de Pedido: Se ingresa el ID
del Pedido. Luego se preguntará si se quiere confirmar la eliminación.*/

int CancelarPedidos(ePedidos listaPedidos[], int tamPedidos)
{


	int idIngresado;
	int indice;
	int confirmar;
	int retorno = -1;

	MostrarTodosLosPedidos(listaPedidos, tamPedidos);
	utn_getNumero(&idIngresado, "Ingrese el idPedidos a cancelar: ", "Error", 0, 200, 2);//verificar que no pida rango
	indice = ePedidos_BuscarPorID(listaPedidos, tamPedidos, idIngresado);

	confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");

	if(confirmar)
	{
		listaPedidos[indice].isEmptyPedidos = CANCELADO;
		retorno = 0;
	}

    return retorno;
}


///////////////FIN CANCELADO///////////////////////////

/*2) Modificar datos de Pedido: Se ingresa el ID de Pedido y se permitirá
cambiar la dirección y la localidad. */


 int ProcesarPedidos(ePedidos listaPedidos[], int tamPedidos)//adaptar a Pedido
 {
     int idIngresado;
     ePedidos auxiliar;
     int i;
     int retorno = -1;
     int opcion;
     int confirmar;

     if(MostrarPedidosPendientes(listaPedidos, tamPedidos)==1)
     {
    	 utn_getNumero(&idIngresado, "\nIngrese id del pedido a procesar: ", "Error.", 0, 5000, 2);//cambiar

		 for(i=0; i<tamPedidos; i++)
		 {
			 if(idIngresado == listaPedidos[i].idPedidos)//lo encontre
			 {
				 MostrarUnPedido(listaPedidos[i]);

				 auxiliar=listaPedidos[i];

				 do{
					 printf("\n\nMENU MODIFICACIÓN\n");
					 printf("1. Cargar Kilos de Polietileno de alta densidad: \n");
					 printf("2. Cargar Kilos de Polietileno de baja densidad: \n");
					 printf("3. Cargar Kilos de Polipropileno: \n");
					 printf("4. Confirmar/Cancelar modificaciones\n");
					 utn_getNumero(&opcion, "Ingrese opcion: ", "Error.", 1, 4, 2);
					 switch(opcion)
					 {
							/////MEJORAR OPCIONES///BANDERA
						 case 1:
							 utn_getNumeroFlotante(&auxiliar.kilosHDPE,"Ingrese Kilos de Polietileno de alta densidad: ", "Error", 0, 9999, 2);
						 break;
						 case 2:
							 utn_getNumeroFlotante(&auxiliar.kilosLDPE,"Ingrese Kilos de Polietileno de baja densidad: ", "Error", 0, 9999, 2);
						 break;
						 case 3:
							 utn_getNumeroFlotante(&auxiliar.kilosPP, "Ingrese Kilos de Polipropileno: ", "Error", 0, 9999, 2);
						 break;

						 case 4:
							confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");
								 if(confirmar)
								 {
									 auxiliar.kilosResiduos = auxiliar.kilosTotales - auxiliar.kilosHDPE - auxiliar.kilosLDPE - auxiliar.kilosPP;
									 auxiliar.isEmptyPedidos = COMPLETADO;
									 listaPedidos[i] = auxiliar;
									 retorno = 1;
								 }
								 else
								 {
									 retorno=0;
								 }

							 opcion =0;
						 break;
					 }

				 }while(opcion!=0);

				 break;
			 }
		 }
     }

     return retorno;
 }


///////////////////  FIN BUSCAR /////////////////////



////////////////MOSTRAR/////////////
void MostrarAuxiliarPedido(ePedidos auxiliarPedido)
{
    printf("\nID Cliente: %8d Kilos totales: %5.2f \n", auxiliarPedido.idCliente,
                           auxiliarPedido.kilosTotales);
}


void MostrarUnPedido(ePedidos unPedido)
{
    printf("\n Estado: %d ID Pedido: %5d ID Cliente: %5d Kilos totales: %5.2f Kilos HDPE(Polietileno de alta densidad): %5.2f Kilos LDPE(Polietileno de baja densidad): %5.2f Kilos PP(Polipropileno): %5.2f Kilos residuos: %5.2f", unPedido.isEmptyPedidos ,unPedido.idPedidos,
                                                                                            unPedido.idCliente,
                                                                                            unPedido.kilosTotales,
                                                                                            unPedido.kilosHDPE,
                                                                                            unPedido.kilosLDPE,
																							unPedido.kilosPP,
																							unPedido.kilosResiduos);
}



int MostrarTodosLosPedidos(ePedidos listaPedidos[], int tamPedidos)
{
    int i;
	printf("\n\t> LISTADO Pedidos");
	printf("%5s\n\n", "ID");
	int retorno;
	retorno = -1;

	if (listaPedidos != NULL && tamPedidos > 0)
	{
		for (i = 0; i < tamPedidos; i++)
		{
			if (listaPedidos[i].isEmptyPedidos == COMPLETADO)
			{
				MostrarUnPedido(listaPedidos[i]);
				retorno = 1;
			}
		}
	}
	return retorno;
}

int MostrarPedidosPendientes(ePedidos listaPedidos[], int tamPedidos)
{
    int i;
	printf("\n\t> LISTADO Pedidos");
	printf("%5s\n\n", "ID");
	int retorno;
	retorno = -1;

	if (listaPedidos != NULL && tamPedidos > 0)
	{
		for (i = 0; i < tamPedidos; i++)
		{
			if (listaPedidos[i].isEmptyPedidos == PENDIENTE)
			{
				MostrarAuxiliarPedido(listaPedidos[i]);
				retorno = 1;
			}
		}
	}
	return retorno;
}

