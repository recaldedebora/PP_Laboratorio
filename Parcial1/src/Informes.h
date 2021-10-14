/*
 * Informes.h
 *
 *  Created on: 13 oct. 2021
 *      Author: Usuario
 */

#ifndef INFORMES_H_
#define INFORMES_H_
#include "Cliente.h"
#include "Pedido.h"
#include "Localidad.h"
#include "UTN_Input.h"

struct
{
	int contadorClientes;
	float acumuladorKilosPP;
}typedef eAuxiliar;

int AltaPedidos_ConIDClienteValidado(ePedidos listaPedidos[], int tamPedidos, int* idPedido,eClientes listaCliente[], int tamClientes);
ePedidos PedirDatosPedidos_ConIDCliente(int *retorno, eClientes listaCliente[], int tamClientes);
int CrearPedidoDeRecoleccion(ePedidos listaPedidos[], int tamPedidos, int* idPedido,eClientes listaCliente[], int tamClientes);
void MostrarAuxiliarCliente_ConKilosTotales(eClientes auxiliarCliente, ePedidos auxiliarPedido);
int MostrarClientes_PedidoPendiente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes);
int MostrarPedidoPendiente_ConCliente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes);
int MostrarPedidoCompletado_ConCliente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes);
float PromedioKilosPP_PorCliente(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes);
int MostrarPedidosPendientes_PorLocalidad(ePedidos listaPedidos[], int tamPedidos, eClientes listaClientes[], int tamClientes);
#endif /* INFORMES_H_ */
