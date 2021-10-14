/*
 ============================================================================
 Recalde, D�bora

Una empresa de recolecci�n y reciclado de pl�sticos requiere un sistema
que les permita administrar sus clientes y pedidos de recolecci�n.
El programa contar� con el siguiente men�:

1) Alta de cliente: Se da de alta un cliente con nombre de la empresa,
cuit direcci�n y localidad. Se generar� un ID �nico para este cliente que
se imprimir� por pantalla si el alta es correcta.

2) Modificar datos de cliente: Se ingresa el ID de cliente y se permitir�
cambiar la direcci�n y la localidad.

3) Baja de cliente: Se ingresa el ID
del cliente. Luego se preguntar� si se quiere confirmar la eliminaci�n.

4) Crear pedido de recolecci�n: Se imprimir�n los clientes por pantalla y
se pedir� que se ingrese el ID de un cliente existente y la cantidad de
kilos totales que se recolectar�n del cliente. Se generar� un ID para el
pedido y el mismo quedar� en estado �Pendiente� hasta que se obtengan los
residuos del cliente y se trasladen a la empresa.

5) Procesar residuos: Se elegir� esta opci�n cuando los residuos que
volvieron a la empresa se hayan procesado y separado en los diferentes
tipos de pl�stico que la empresa puede reciclar. Se imprimir�n los pedidos
por pantalla y se pedir� seleccionar el ID de uno de ellos. Luego deber�n
ingresarse la cantidad de kilos de pl�stico de cada uno de los 3 tipos que
la empresa puede procesar que se obtuvieron de los kilos totales que se
recolectaron. Por �ltimo, se marcar� al pedido como �Completado�.

6) Imprimir Clientes: Se imprimir� una lista de clientes con todos sus datos
junto con la cantidad de �pedidos de recolecci�n� que posee en estado �Pendiente�.

7) Imprimir Pedidos pendientes: Se imprimir� una lista de los pedidos que
se encuentren en estado �Pendiente� con la informaci�n: Cuit del cliente,
direcci�n del cliente, cantidad de kilos a recolectar.

8) Imprimir Pedidos procesados: Se imprimir� una lista de los pedidos que
se encuentren en estado �Completado� con la informaci�n: Cuit del cliente,
direcci�n del cliente, cantidad de kilos reciclados de cada tipo de pl�stico.

9) Ingresar una localidad e indicar la cantidad de pedidos pendientes para
dicha localidad.

10) Cantidad de kilos de polipropileno reciclado promedio
por cliente. (kilos totales / cantidad de clientes)

Los tipos de pl�stico que la empresa puede reciclar son:

� HDPE: Polietileno de alta densidad (Envases para l�cteos, perfumes,
detergentes l�quidos, etc.)
� LDPE: Polietileno de baja densidad (Bolsas
de congelaci�n de alimentos, tapas flexibles o bolsas de basura.)
� PP: Polipropileno (Pl�sticos utilizados en la industria automovil�stica
y en la construcci�n.) El resto de la basura recolectada es desechada
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Informes.h"
#define TAM_CLIENTES 5
#define TAM_PEDIDOS 10

int main()
{
	setbuf(stdout,NULL);
    eClientes miCliente[TAM_CLIENTES];
    ePedidos miPedido[TAM_PEDIDOS];
    int opcion;
    int idClientes =0;
    int estado;
    int estado2;
    int estado3;
    int estado4;

    InicializarClientes(miCliente, TAM_CLIENTES);
    HarcodearClientes(miCliente, 3);
    InicializarPedidos(miPedido,TAM_PEDIDOS);
    HarcodearPedidos(miPedido);

    do
    {
        printf("\n\n1. ALTA cliente\n");
        printf("2. MODIFICACION cliente\n");
        printf("3. BAJA cliente\n");
        printf("4. Crear pedido de recolecci�n\n");
        printf("5. Procesar residuos\n");
        printf("6. Imprimir Clientes con pedidos �Pendiente� \n");//mostrar si no tiene pedidos pendiente
        printf("7. Imprimir Pedidos pendientes con datos del cliente\n");
        printf("8. Imprimir Pedidos procesados con datos del cliente\n");
        printf("9. Ingresar una localidad e indicar la cantidad de pedidos pendientes para dicha localidad. \n");
        printf("10. Cantidad de kilos de polipropileno reciclado promedio por cliente.\n");
        printf("0. Salir\n");
        printf("Elija una opcion:");
        utn_getNumero(&opcion, "Ingrese opcion: ", "Error.", -1, 10, 2);
        switch(opcion)
        {
            case 1:
            	estado = AltaClientes(miCliente,TAM_CLIENTES, &idClientes);

            	if(estado == 1){
            		printf("Alta con exito\n");
            	}
            	else
            	{
            		if(estado == 0)
            		{
            			printf("Alta cancelada\n");
            		}
            		else
            		{
            			if(estado == -2)
						{
							printf("Datos ingresados de manera incorrecta\n");
						}
            			else
            			{
            				printf("No hay lugar\n");
            			}
            		}
            	}


            break;


            case 2:
                if(ModificarClientes(miCliente,TAM_CLIENTES)==0)
                {
                	printf("Modificacion confirmada\n");
                }
                else
                {
                	printf("Modificacion cancelada\n");
                }
            break;

            case 3:
            	if(EliminarClientes(miCliente,TAM_CLIENTES)==0)
				{
					 printf("Dato eliminado con exito\n");
				}
				else
				{
					printf("Eliminaci�n cancelada\n");
				}
			break;

            case 4:
            	estado2 = CrearPedidoDeRecoleccion(miPedido, TAM_PEDIDOS, &idClientes,miCliente,TAM_CLIENTES);

            	if(estado2 == 1){
            		printf("Pedido de recolecci�n generado con �xito\n");
            	}
            	else
            	{
            		if(estado2 == 0)
            		{
            			printf("Datos incorrectos, no se gener� pedido de recolecci�n\n");
            		}
            		else
            		{
            			printf("No hay clientes registrados\n");
            		}
            	}
            break;

            case 5:
            	estado3 = ProcesarPedidos(miPedido, TAM_PEDIDOS);

				if(estado3 == 1){
					printf("Pedido porcesado con exito\n");
				}
				else
				{
					if(estado3 == 0)
					{
						printf("Proceso de pedido cancelado\n");
					}
					else
					{

						printf("No hay pedidos pendientes de procesar\n");
					}
				}
            break;

            case 6:
            	//acomodar + completar
            	if(MostrarClientes_PedidoPendiente(miPedido, TAM_PEDIDOS,miCliente,TAM_CLIENTES)!=0){
            		printf("No hay clientes con pedidos pendientes de procesar\n");
            	}
            break;

            case 7:
            	if(MostrarPedidoPendiente_ConCliente(miPedido, TAM_PEDIDOS,miCliente,TAM_CLIENTES)== -1){
            		printf("No hay pedidos pendientes de procesar\n");
            	}
			break;

            case 8:
            	if(MostrarPedidoCompletado_ConCliente(miPedido, TAM_PEDIDOS,miCliente,TAM_CLIENTES)!=0){
					printf("No hay pedidos completados\n");
				}

			break;

            case 9:
            	estado4 = MostrarPedidosPendientes_PorLocalidad(miPedido,TAM_PEDIDOS,miCliente,TAM_CLIENTES);
            	if(estado4==0){
            		printf("No hay pedidos pendientes para la localidad ingresada\n");
            	}
            	else
            	{
            		if(estado4== -1){
						printf("Localidad ingresada incorrectamente.\n");
					}
            	}
			break;

            case 10:
            	if(PromedioKilosPP_PorCliente(miPedido, TAM_PEDIDOS,miCliente,TAM_CLIENTES)== -1){
            		printf("No se pudo calcular promedio\n");
            	}
			break;



        }
    }while(opcion != -1);

	return EXIT_SUCCESS;
}
