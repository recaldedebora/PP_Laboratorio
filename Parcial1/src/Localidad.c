/*
 * Localidad.c
 *
 *  Created on: 14 oct. 2021
 *      Author: Usuario
 */

#include "Localidad.h"


void InicializarLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)
{
	int i;

    if (listaLocalidades != NULL && tamLocalidades > 0) {
    	for(i=0; i<tamLocalidades; i++)
    	{
    		listaLocalidades[i].isEmptyLocalidades = LIBRE;
    	}
    }
}


void HarcodearLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)//ADAPTAR A CLIENTES
{

    int idLocalidades[]={1, 2, 3};
    char localidad[][30]={"Avellaneda", "Quilmes", "Lanús"};


    int i;
    for(i=0; i<tamLocalidades; i++)
    {

        strcpy(listaLocalidades[i].nombreLocalidad , localidad[i]);
        listaLocalidades[i].idLocalidades=idLocalidades[i];
        listaLocalidades[i].isEmptyLocalidades = OCUPADO;

    }
}





///////////////////   BUSCAR /////////////////////

int BuscarLibreLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)
{
	int i;
	int indice;
	indice = -1;

	if (listaLocalidades != NULL && tamLocalidades > 0) {
    	for(i=0; i<tamLocalidades; i++)
    	{
    		if(listaLocalidades[i].isEmptyLocalidades==LIBRE)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}


int BuscarOcupadoLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)//pendiente
{
	int i;
	int indice;
	indice = -1;


	if (listaLocalidades != NULL && tamLocalidades > 0) {
    	for(i=0; i<tamLocalidades; i++)
    	{
    		if(listaLocalidades[i].isEmptyLocalidades==OCUPADO)
    		{
    			indice = i;
    			break;
    		}
    	}
	}

	return indice;
}

int BuscarBajaLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)//completado
{
	int i;
	int indice;
	indice = -1;
	for(i=0; i<tamLocalidades; i++)
	{
		if(listaLocalidades[i].isEmptyLocalidades==BAJA)
		{
			indice = i;
			break;
		}
	}

	return indice;
}


int eLocalidades_BuscarPorID(eLocalidades listaLocalidades[], int tamLocalidades, int ID)//ver//CAMBIAR A "RETORNO"//ver si me sirve filtrar por ocupado
{
	int retorno = -1;
	int i;


	if (listaLocalidades != NULL && tamLocalidades > 0)
	{
		for (i = 0; i < tamLocalidades; i++)
		{
			if (listaLocalidades[i].idLocalidades == ID && listaLocalidades[i].isEmptyLocalidades == OCUPADO)
			{
	            retorno = i;
				break;
			}
		}
	}

	return retorno;
}

///////////////////  FIN BUSCAR /////////////////////
eLocalidades PedirDatosLocalidades(int *retorno)
{

	eLocalidades auxiliar;
	*retorno=-1;

	if(utn_getDescripcion(auxiliar.nombreLocalidad, TAM_BUFFER,"\nIngrese nombre de la Localidad: ", "Error", 2)== 0)
	{
		*retorno=0;
	}

    return auxiliar;
}


int AltaLocalidades(eLocalidades listaLocalidades[], int tamLocalidades, int* id)
{

	eLocalidades auxiliar;
    int indice;
    indice=BuscarLibreLocalidades(listaLocalidades, tamLocalidades);
    int rtn;
    int confirmar;
    int datosOk;



    if(indice==-1)
    {
    	rtn=  -1;
    }
    else
    {

    	 auxiliar = PedirDatosLocalidades(&datosOk);
    	 if(datosOk == 0)
    	 {
			 MostrarAuxiliarLocalidad(auxiliar);
			 confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");

			 if(confirmar==1)
			 {
				//SETEO ID UNICO - VARIABLE AUTOINCREMENTAL
				auxiliar.isEmptyLocalidades = OCUPADO;
				auxiliar.idLocalidades = *id;
				*id = *id + 1;
				//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
				listaLocalidades[indice] = auxiliar;
				MostrarUnaLocalidad(auxiliar);
				//RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
				printf("ID cliente asignado : %d \n", listaLocalidades[indice].idLocalidades);
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


int EliminarLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)
{


	int idIngresado;
	int indice;
	int confirmar;
	int retorno = -1;

	MostrarTodosLosLocalidades(listaLocalidades, tamLocalidades);
	utn_getNumero(&idIngresado, "Ingrese el idLocalidades a eliminar: ", "Error", 0, 200, 2);//verificar que no pida rango
	indice = eLocalidades_BuscarPorID(listaLocalidades, tamLocalidades, idIngresado);

	confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");

	if(confirmar)
	{
		listaLocalidades[indice].isEmptyLocalidades = BAJA;
		retorno = 0;
	}

    return retorno;
}


///////////////FIN BAJA///////////////////////////

/*2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitirá
cambiar la dirección y la localidad. */


 int ModificarLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)//adaptar a cliente
 {
     int idIngresado;
     eLocalidades auxiliar;
     int i;
     int retorno = -1;
     int opcion;
     int confirmar;

     MostrarTodosLosLocalidades(listaLocalidades, tamLocalidades);

     utn_getNumero(&idIngresado, "Ingrese el id a modificar: ", "Error.", 0, 5000, 2);//cambiar

     for(i=0; i<tamLocalidades; i++)
     {
         if(idIngresado == listaLocalidades[i].idLocalidades)//lo encontre
         {
             MostrarUnaLocalidad(listaLocalidades[i]);

             auxiliar=listaLocalidades[i];

             do{
            	 printf("\n\nMENU MODIFICACIÓN\n");
            	 printf("1. Modificar Nombre localidad\n");
            	 printf("2. Confirmar/Cancelar modificaciones\n");
            	 utn_getNumero(&opcion, "Ingrese opcion: ", "Error.", 1, 3, 2);
                 switch(opcion)
                 {
                 	 	/////MEJORAR OPCIONES///BANDERA
                     case 1:
                    	 utn_getDescripcion(auxiliar.nombreLocalidad, tamLocalidades,"Ingrese nueva dirección: ", "Error", 2);
                     break;

                     case 2:
                        confirmar = ConfirmarGestion("DESEA CONTINUAR SI[S] - NO[N]: ","ERROR. REINGRESE.");
                             if(confirmar)
                             {
                                 listaLocalidades[i] = auxiliar;
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
void MostrarAuxiliarLocalidad(eLocalidades auxiliarLocalidad)
{
    printf("\n♦%8d %5s\n", auxiliarLocalidad.idLocalidades,
                                 auxiliarLocalidad.nombreLocalidad);
}


void MostrarUnaLocalidad(eLocalidades unLocalidad)
{
    printf("\n♦ID Localidad: %5d NOMBRE LOCALIDAD: %8s", unLocalidad.idLocalidades,
                                                         unLocalidad.nombreLocalidad);
}



int MostrarTodosLosLocalidades(eLocalidades listaLocalidades[], int tamLocalidades)
{
    int i;
	printf("\n\t> LISTADO Localidades");
	printf("%5s\n\n", "ID");
	int retorno;
	retorno = -1;

	if (listaLocalidades != NULL && tamLocalidades > 0)
	{
		for (i = 0; i < tamLocalidades; i++)
		{
			if (listaLocalidades[i].isEmptyLocalidades == OCUPADO)
			{
				MostrarUnaLocalidad(listaLocalidades[i]);
				retorno = 1;
			}
		}
	}
	return retorno;
}

