/*
 * Informes.c
 *
 *  Created on: 13 oct. 2021
 *      Author: Usuario
 *
 *
4) Crear pedido de recolección: Se imprimirán los clientes por pantalla y
se pedirá que se ingrese el ID de un cliente existente y la cantidad de
kilos totales que se recolectarán del cliente. Se generará un ID para el
pedido y el mismo quedará en estado “Pendiente” hasta que se obtengan los
residuos del cliente y se trasladen a la empresa.

5) Procesar residuos: Se elegirá esta opción cuando los residuos que
volvieron a la empresa se hayan procesado y separado en los diferentes
tipos de plástico que la empresa puede reciclar. Se imprimirán los pedidos
por pantalla y se pedirá seleccionar el ID de uno de ellos. Luego deberán
ingresarse la cantidad de kilos de plástico de cada uno de los 3 tipos que
la empresa puede procesar que se obtuvieron de los kilos totales que se
recolectaron. Por último, se marcará al pedido como “Completado”.

6) Imprimir Clientes: Se imprimirá una lista de clientes con todos sus datos
junto con la cantidad de “pedidos de recolección” que posee en estado “Pendiente”.

7) Imprimir Pedidos pendientes: Se imprimirá una lista de los pedidos que
se encuentren en estado “Pendiente” con la información: Cuit del cliente,
dirección del cliente, cantidad de kilos a recolectar.

8) Imprimir Pedidos procesados: Se imprimirá una lista de los pedidos que
se encuentren en estado “Completado” con la información: Cuit del cliente,
dirección del cliente, cantidad de kilos reciclados de cada tipo de plástico.

9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para
dicha localidad.

10) Cantidad de kilos de polipropileno reciclado promedio
por cliente. (kilos totales / cantidad de clientes)
 */
#include "Informes.h"

ePedidos PedirDatosPedidos_ConIDCliente(int *retorno, eClientes listaCliente[], int tamClientes)
{

	ePedidos auxiliar;
	*retorno=-1;


	if(utn_getNumero(&auxiliar.idCliente, "ingrese ID cliente", "Error", 0, 500, 2)==0 )
	{
		if(eClientes_BuscarPorID(listaCliente, tamClientes, auxiliar.idCliente)!= -1)
		{
			printf("Segundo if pedir datos");
			if(utn_getNumeroFlotante(&auxiliar.kilosTotales,"\nIngrese Kilos totales: ", "Error", 0, 8000000, 2)==0 )
			{

				*retorno=0;
			}
		}
	}

    return auxiliar;
}

int AltaPedidos_ConIDClienteValidado(ePedidos listaPedidos[], int tamPedidos, int* idPedido,eClientes listaCliente[], int tamClientes){
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

	    	 auxiliar = PedirDatosPedidos_ConIDCliente(&datosOk, listaCliente,tamClientes);
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
					//MostrarUnPedido(auxiliar);
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
	    //printf("retorno : %d \n", retorno);
	    return retorno;
	}

}

int CrearPedidoDeRecoleccion(ePedidos listaPedidos[], int tamPedidos, int* idPedido,eClientes listaClientes[], int tamClientes)
{
	int retorno;
	retorno = -1;
	int idRecibido;
	idRecibido=*idPedido;

	if(MostrarTodosLosClientes(listaClientes, tamClientes)==1)
	{

		if(AltaPedidos_ConIDClienteValidado(listaPedidos, tamPedidos, &idRecibido,listaClientes,tamClientes)==1)
		{
			retorno = 1;
		}
	}
	else
	{
		retorno = 0;
	}

	return retorno;
}

/*6. Imprimir Clientes con pedidos “Pendiente”
7. Imprimir Pedidos pendientes con datos del cliente
8. Imprimir Pedidos procesados con datos del cliente
6) Imprimir Clientes: Se imprimirá una lista de clientes con todos sus datos
junto con la cantidad de “pedidos de recolección” que posee en estado “Pendiente”.

7) Imprimir Pedidos pendientes: Se imprimirá una lista de los pedidos que
se encuentren en estado “Pendiente” con la información: Cuit del cliente,
dirección del cliente, cantidad de kilos a recolectar.

8) Imprimir Pedidos procesados: Se imprimirá una lista de los pedidos que
se encuentren en estado “Completado” con la información: Cuit del cliente,
dirección del cliente, cantidad de kilos reciclados de cada tipo de plástico.

9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para
dicha localidad.

*/
void MostrarAuxiliarCliente_ConKilosTotales(eClientes auxiliarCliente, ePedidos auxiliarPedido)
{
    printf("\nCUIT: %8s DIRECCION: %5s TOTAL KILOS: %5.2f\n",auxiliarCliente.cuit,
                                 	 	 	 	 	 	 	 auxiliarCliente.direccion,
															 auxiliarPedido.kilosTotales);
}

int MostrarClientes_PedidoPendiente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes){
	int retorno;
	retorno = -1;

	int i;
	int j;
	for(i=0; i<tamClientes; i++)
	{
		printf("Clientes con pedidos pendientes:");
		for(j=0; j<tamPedidos; j++)
		{
			if(listaClientes[i].idClientes == listaPedidos[j].idPedidos && listaPedidos[j].isEmptyPedidos == PENDIENTE)
			{
				MostrarUnCliente(listaClientes[i]);
				retorno = 0;
			}
		}


	}


	return retorno;
}

int MostrarPedidoPendiente_ConCliente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes){

	int retorno;
	retorno = -1;

	int i;
	int j;
	for(i=0; i<tamPedidos; i++)
	{
		if(listaPedidos[i].isEmptyPedidos == PENDIENTE)
		{
			for(j=0; j<tamClientes; j++)
			{
				if(listaPedidos[i].idCliente == listaClientes[j].idClientes)
				{
					printf("***PEDIDOS PENDIENTES DE PROCESAR***");
					MostrarAuxiliarCliente_ConKilosTotales(listaClientes[j], listaPedidos[i]);
					retorno = 0;
					break;
				}
			}
		}

	}
	return retorno;
}



int MostrarPedidoCompletado_ConCliente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes){

	int retorno;
	retorno = -1;

	int i;
	int j;
	for(i=0; i<tamPedidos; i++)
	{
		if(listaPedidos[i].isEmptyPedidos == COMPLETADO)
		{
			printf("***PEDIDOS COMPLETOS***");
			for(j=0; j<tamClientes; j++)
			{
				if(listaPedidos[i].idCliente == listaClientes[j].idClientes)
				{
					MostrarAuxiliarCliente_ConKilosTotales(listaClientes[j], listaPedidos[i]);
					retorno = 0;
				}
			}
		}

	}
	return retorno;
}

float PromedioKilosPP_PorCliente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes)
{
	//eAuxiliar aux[tamClientes];
	int i;
	float promedio;
	float retorno;
	int contador;
	float acumuladorKilos;
	retorno = -1;
	contador = 0;
	acumuladorKilos = 0;


	/*for(i=0; i<tamClientes; i++)
	{

		aux[i].contadorClientes= 0;
		aux[i].acumuladorKilosPP= 0;

	}
	printf("\ncontador clientes %d antes", aux[i].contadorClientes);
	printf("\nacumulador kilor PP %f antes", aux[i].acumuladorKilosPP);*/

	if (listaClientes != NULL && tamClientes > 0)
	{
		for(i=0; i<tamClientes; i++)
		{
			if(listaClientes[i].isEmptyClientes == OCUPADO)
			{
				contador++;
			}
		}
	}

	//printf("\nRetorno contador clientes %d", aux[i].contadorClientes);


	for(i=0; i<tamPedidos; i++)
	{
		acumuladorKilos = acumuladorKilos + listaPedidos[i].kilosPP;
	}
	//printf("\nRetorno acumulador kilor PP %f", aux[i].acumuladorKilosPP);


	if(contador > 0){

		promedio = acumuladorKilos/contador;
		retorno = promedio;
	}

	printf("\nRetorno contador %d", contador);
	printf("\nRetorno acumulador kilos %.2f", acumuladorKilos);
	printf("\nRetorno promedio %.2f", retorno);

	return retorno;
}

/*
9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para
dicha localidad.

*/

int MostrarPedidosPendientes_PorLocalidad(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes, eLocalidades listaLocalidades[], int tamLocalidades)
{

	int i;
	int idLocalidadRecibida;
	int resultado;
	int retorno;
	int flag;
	flag = 0;
	retorno = -1;

	MostrarTodasLasLocalidades(listaLocalidades, tamLocalidades);

	resultado = utn_getNumero(&idLocalidadRecibida, "Ingrese ID de localidad a buscar", "Error", 0, 20, 2);

	if(resultado == 0)
	{
		retorno = 0;
		printf("Pedidos pendientes para %d", idLocalidadRecibida);
		for(i=0; i<tamPedidos; i++)
		{
			if(listaPedidos[i].isEmptyPedidos == PENDIENTE)
			{

				if(idLocalidadRecibida == listaClientes[i].idLocalidad)
				{
					MostrarUnCliente(listaClientes[i]);
					retorno = 1;
					flag++;
				}
			}


		}
	}

	if(flag !=0){
		retorno=1;
	}


	return retorno;

}


/*
 * 3) Agregar los siguientes informes:
a) Cliente con más pedidos pendientes.
b) Cliente con más pedidos completados.
c) Cliente con más pedidos.
*/

int ClienteConMasPedidos(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes)
{

	eAuxiliar auxiliar;
	int i;
	int j;
	int maximo;
	int retorno;
	retorno = -1;

	for(i=0; i<tamClientes; i++)
		{
		auxiliar[i].contadorClientes = 0;
		auxiliar[i].contadorPedidos = 0;
	}




	for(i=0; i<tamClientes; i++)//recorro la lista de clientes y por cada uno recorro la lista de pedidos y cuento
	{
		for(j=0; j<tamPedidos; j++)
		{
			if(listaClientes[i].idClientes == listaPedidos[i].idCliente)
			{
				auxiliar[i].contadorPedidos++;
			}
		}
	}

	for(i=0; i<tamClientes; i++)
	{
		if(i==0 || auxiliar[i].contadorPedidos>maximo)
		{
			maximo = auxiliar[i].contadorPedidos;
		}
	}

	for(i=0; i<tamClientes; i++)//auxiliar
	{
		if(auxiliar[i].contadorPedidos==maximo)
		{
			for(j=0; j<tamClientes; j++)//clientes
			{
				if(listaClientes[i].idClientes == listaPedidos[i].idCliente)
				{
					printf("El tipo con mas pedidos es: %s\n" , listaClientes[i].nombreEmpresa);
					retorno = 0;
				}
			}
		}
	}

	return retorno;

}

int ClienteConMasPedidosPendientes(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes)
{

	eAuxiliar auxiliar;
	int i;
	int j;
	int maximo;
	int retorno;
	retorno = -1;
	for(i=0; i<tamClientes; i++)
	{
		auxiliar[i].contadorClientes = 0;
		auxiliar[i].contadorPedidos = 0;
	}




	for(i=0; i<tamClientes; i++)//recorro la lista de clientes y por cada uno recorro la lista de pedidos y cuento
	{
		for(j=0; j<tamPedidos; j++)
		{
			if(listaClientes[i].idClientes == listaPedidos[i].idCliente && listaPedidos[i].isEmptyPedidos == PENDIENTE)
			{
				auxiliar[i].contadorPedidos++;
			}
		}
	}

	for(i=0; i<tamClientes; i++)
	{
		if(i==0 || auxiliar[i].contadorPedidos>maximo)
		{
			maximo = auxiliar[i].contadorPedidos;
		}
	}

	for(i=0; i<tamClientes; i++)//auxiliar
	{
		if(auxiliar[i].contadorPedidos==maximo)
		{
			for(j=0; j<tamClientes; j++)//clientes
			{
				if(listaClientes[i].idClientes == listaPedidos[i].idCliente)
				{
					printf("El tipo con mas pedidos pendientes es: %s\n" , listaClientes[i].nombreEmpresa);
					retorno = 0;
				}
			}
		}
	}



}


int ClienteConMasPedidosCompletados(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes)
{

	eAuxiliar auxiliar;
	int i;
	int j;
	int maximo;
	int retorno;
	retorno = -1;

	for(i=0; i<tamClientes; i++)
		{
		auxiliar[i].contadorClientes = 0;
		auxiliar[i].contadorPedidos = 0;
	}




	for(i=0; i<tamClientes; i++)//recorro la lista de clientes y por cada uno recorro la lista de pedidos y cuento
	{
		for(j=0; j<tamPedidos; j++)
		{
			if(listaClientes[i].idClientes == listaPedidos[i].idCliente && listaPedidos[i].isEmptyPedidos == COMPLETADO)
			{
				auxiliar[i].contadorPedidos++;
			}
		}
	}

	for(i=0; i<tamClientes; i++)
	{
		if(i==0 || auxiliar[i].contadorPedidos>maximo)
		{
			maximo = auxiliar[i].contadorPedidos;
		}
	}

	for(i=0; i<tamClientes; i++)//auxiliar
	{
		if(auxiliar[i].contadorPedidos==maximo)
		{
			for(j=0; j<tamClientes; j++)//clientes
			{
				if(listaClientes[i].idClientes == listaPedidos[i].idCliente)
				{
					printf("El tipo con mas pedidos completados es: %s\n" , listaClientes[i].nombreEmpresa);
					retorno = 0;
				}
			}
		}
	}

	return retorno;

}
