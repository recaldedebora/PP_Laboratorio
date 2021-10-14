/*
 * Cliente.c
 *
 *  Created on: 12 oct. 2021
 *      Author: Usuario
 */


#include "Cliente.h"


void InicializarClientes(eClientes listaClientes[], int tamClientes)
{
	int i;

    if (listaClientes != NULL && tamClientes > 0) {
    	for(i=0; i<tamClientes; i++)
    	{
    		listaClientes[i].isEmptyClientes = LIBRE;
    	}
    }
}


void HarcodearClientes(eClientes listaClientes[], int tamClientes)//ADAPTAR A CLIENTES
{

    int idClientes[]={1, 2, 3};
    char nombreEmpresa[][30]={"Homero", "March", "Bart"};
    char cuit[][30]={"20-123456789-9", "21-14725869-6", "22-321654987-3"};
    char direccion[][30]={"Av. Mitre 3", "Calle falsa 123", "Alsina 150"};
    char localidad[][30]={"Avellaneda", "Quilmes", "Lanus"};
    int idPedido[]={0,1,2};


    int i;
    for(i=0; i<tamClientes; i++)
    {

    		listaClientes[i].idClientes = idClientes[i];
			strcpy(listaClientes[i].nombreEmpresa , nombreEmpresa[i]);
			strcpy(listaClientes[i].cuit , cuit[i]);
			strcpy(listaClientes[i].direccion , direccion[i]);
			strcpy(listaClientes[i].localidad , localidad[i]);
			listaClientes[i].idPedido=idPedido[i];
			listaClientes[i].isEmptyClientes = OCUPADO;



    }
}





///////////////////   BUSCAR /////////////////////

int BuscarLibreClientes(eClientes listaClientes[], int tamClientes)
{
	int i;
	int indice;
	indice = -1;

	if (listaClientes != NULL && tamClientes > 0) {
    	for(i=0; i<tamClientes; i++)
    	{
    		if(listaClientes[i].isEmptyClientes==LIBRE)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}


int BuscarOcupadoClientes(eClientes listaClientes[], int tamClientes)//pendiente
{
	int i;
	int indice;
	indice = -1;


	if (listaClientes != NULL && tamClientes > 0) {
    	for(i=0; i<tamClientes; i++)
    	{
    		if(listaClientes[i].isEmptyClientes==OCUPADO)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}

int BuscarBajaClientes(eClientes listaClientes[], int tamClientes)//completado
{
	int i;
	int indice;
	indice = -1;
	for(i=0; i<tamClientes; i++)
	{
		if(listaClientes[i].isEmptyClientes==BAJA)
		{
			indice = i;
			break;
		}
	}

	return indice;
}


int eClientes_BuscarPorID(eClientes listaClientes[], int tamClientes, int ID)//ver//CAMBIAR A "RETORNO"//ver si me sirve filtrar por ocupado
{
	int retorno = -1;
	int i;


	if (listaClientes != NULL && tamClientes > 0)
	{
		for (i = 0; i < tamClientes; i++)
		{
			if (listaClientes[i].idClientes == ID && listaClientes[i].isEmptyClientes == OCUPADO)
			{
	            retorno = i;
				break;
			}
		}
	}

	return retorno;
}

///////////////////  FIN BUSCAR /////////////////////
eClientes PedirDatosClientes(int *retorno)
{

	eClientes auxiliar;
	*retorno=-1;

	if(utn_getDescripcion(auxiliar.nombreEmpresa, TAM_BUFFER,"\nIngrese nombre de la Empresa: ", "Error", 2)== 0 &&
	utn_getCuit(auxiliar.cuit , TAM_BUFFER,"Ingrese cuit de la Empresa: ", "Error", 2)== 0 &&
	utn_getDescripcion(auxiliar.direccion, TAM_BUFFER,"Ingrese direccion de la Empresa: ", "Error", 2)== 0 &&
	utn_getDescripcion(auxiliar.localidad, TAM_BUFFER,"Ingrese localidad de la Empresa: \n", "Error", 2)== 0){
		*retorno=0;
	}

    return auxiliar;
}


int AltaClientes(eClientes listaClientes[], int tamClientes, int* id)
{

	eClientes auxiliar;
    int indice;
    indice=BuscarLibreClientes(listaClientes, tamClientes);
    int rtn;
    int confirmar;
    int datosOk;



    if(indice==-1)
    {
    	rtn=  -1;
    }
    else
    {

    	 auxiliar = PedirDatosClientes(&datosOk);
    	 if(datosOk == 0)
    	 {
			 MostrarAuxiliarCliente(auxiliar);
			 confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");

			 if(confirmar==1)
			 {
				//SETEO ID UNICO - VARIABLE AUTOINCREMENTAL
				auxiliar.isEmptyClientes = OCUPADO;
				auxiliar.idPedido = PEDIDO_PENDIENTE;
				auxiliar.idClientes = *id;
				*id = *id + 1;
				//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
				listaClientes[indice] = auxiliar;
				MostrarUnCliente(auxiliar);
				//RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
				printf("ID cliente asignado : %d \n", listaClientes[indice].idClientes);
				rtn= 1;
			}
			 else
			 {
				 rtn = 0;
			 }

    	 }
    	 else
    	 {
    		 rtn= -2;
    	 }

    }
    printf("retorno : %d \n", rtn);
    return rtn;
}

/////////////// FIN ALTA   /////////////////////////

/*3) Baja de cliente: Se ingresa el ID
del cliente. Luego se preguntará si se quiere confirmar la eliminación.*/

int EliminarClientes(eClientes listaClientes[], int tamClientes)
{


	int idIngresado;
	int indice;
	int confirmar;
	int retorno = -1;

	MostrarTodosLosClientes(listaClientes, tamClientes);
	utn_getNumero(&idIngresado, "Ingrese el idClientes a eliminar: ", "Error", 0, 200, 2);//verificar que no pida rango
	indice = eClientes_BuscarPorID(listaClientes, tamClientes, idIngresado);

	confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");

	if(confirmar)
	{
		listaClientes[indice].isEmptyClientes = BAJA;
		retorno = 0;
	}

    return retorno;
}


///////////////FIN BAJA///////////////////////////

/*2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitirá
cambiar la dirección y la localidad. */


 int ModificarClientes(eClientes listaClientes[], int tamClientes)//adaptar a cliente
 {
     int idIngresado;
     eClientes auxiliar;
     int i;
     int retorno = -1;
     int opcion;
     int confirmar;

     MostrarTodosLosClientes(listaClientes, tamClientes);

     utn_getNumero(&idIngresado, "Ingrese el id a modificar: ", "Error.", 0, 5000, 2);//cambiar

     for(i=0; i<tamClientes; i++)
     {
         if(idIngresado == listaClientes[i].idClientes)//lo encontre
         {
             MostrarUnCliente(listaClientes[i]);

             auxiliar=listaClientes[i];

             do{
            	 printf("\n\nMENU MODIFICACIÓN\n");
            	 printf("1. Modificar direccion\n");
            	 printf("2. Modificar localidad\n");
            	 printf("3. Confirmar/Cancelar modificaciones\n");
            	 utn_getNumero(&opcion, "Ingrese opcion: ", "Error.", 1, 3, 2);
                 switch(opcion)
                 {
                 	 	/////MEJORAR OPCIONES///BANDERA
                     case 1:
                    	 utn_getDescripcion(auxiliar.direccion, tamClientes,"Ingrese nueva dirección: ", "Error", 2);
                     break;
                     case 2:
                    	 utn_getDescripcion(auxiliar.localidad, tamClientes,"Ingrese nueva localidad: ", "Error", 2);
                     break;

                     case 3:
                        confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");
                             if(confirmar)
                             {
                                 listaClientes[i] = auxiliar;
                                 retorno = 0;
                             }

                         opcion =0;
                     break;
                 }

             }while(opcion!=0);

             break;
         }
     }

     return retorno;
 }


///////////////////  FIN BUSCAR /////////////////////



////////////////MOSTRAR/////////////
void MostrarAuxiliarCliente(eClientes auxiliarCliente)
{
    printf("\n♦%8s %5s %5s %5s\n", auxiliarCliente.nombreEmpresa,
                                 auxiliarCliente.cuit,
                                 auxiliarCliente.direccion,
                                 auxiliarCliente.localidad);
}


void MostrarUnCliente(eClientes unCliente)
{
    printf("\n♦ID Cliente: %5d NOMBRE EMPRESA: %8s CUIT: %5s DIRECCION: %5s LOCALIDAD: %5s",  unCliente.idClientes,
                                                                                            unCliente.nombreEmpresa,
                                                                                            unCliente.cuit,
                                                                                            unCliente.direccion,
                                                                                            unCliente.localidad);
}



int MostrarTodosLosClientes(eClientes listaClientes[], int tamClientes)
{
    int i;
	printf("\n\t> LISTADO Clientes");
	printf("%5s\n\n", "ID");
	int retorno;
	retorno = -1;

	if (listaClientes != NULL && tamClientes > 0)
	{
		for (i = 0; i < tamClientes; i++)
		{
			if (listaClientes[i].isEmptyClientes == OCUPADO)
			{
				MostrarUnCliente(listaClientes[i]);
				retorno = 1;
			}
		}
	}
	return retorno;
}
