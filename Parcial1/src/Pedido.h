/*
 * Pedido.h
 *
 *  Created on: 13 oct. 2021
 *      Author: Usuario
 */

#ifndef PEDIDO_H_
#define PEDIDO_H_

#include "UTN_Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define COMPLETADO 2
#define LIBRE 1
#define PENDIENTE 0
#define CANCELADO -1
#define SIN_CLASIFICAR -1
#define TAM_BUFFER 30

struct
{
 int idPedidos;
 int idCliente;
 float kilosTotales;
 float kilosHDPE;
 float kilosLDPE;
 float kilosPP;
 float kilosResiduos;
  int isEmptyPedidos;
}typedef ePedidos;

/**
 * @fn void InicializarPedidos(ePedidos[], int)
 * @brief inicializa todo el array de pedidos en "LIBRE"
 *
 * @param listaPedidos array de pedidos
 * @param tamPedidos tamaño del array de pedidos
 */
void InicializarPedidos(ePedidos listaPedidos[], int tamPedidos);

/**
 * @fn void HarcodearPedidos(ePedidos[])
 * @brief Harcodea los campos de la estructura ePedidos
 *
 * @param listaPedidos array de pedidos
 */
void HarcodearPedidos(ePedidos listaPedidos[]);

/**
 * @fn int BuscarLibrePedidos(ePedidos[], int)
 * @brief Recorre el array y busca un pedido que tenga isEmpty LIBRE
 *
 * @param listaPedidos array de pedidos
 * @param tamPedidos
 * @return retorna el primer indice que tenga isEmpty LIBRE encontrado ó  -1 si no encontró ninguno
 */
int BuscarLibrePedidos(ePedidos listaPedidos[], int tamPedidos);

/**
 * @fn int BuscarPendientePedidos(ePedidos[], int)
 * @brief Recorre el array y busca un pedido que tenga isEmpty PENDIENTE
 *
 * @param listaPedidos array de pedidos
 * @param tamPedidos tamaño del array de pedidos
 * @return retorna el primer indice que tenga isEmpty PENDIENTE encontrado ó  -1 si no encontró ninguno
 */
int BuscarPendientePedidos(ePedidos listaPedidos[], int tamPedidos);


/**
 * @fn int BuscarCompletadoPedidos(ePedidos[], int)
 * @brief Recorre el array y busca un pedido que tenga isEmpty COMPLETADO
 *
 * @param listaPedidos array de pedidos
 * @param tamPedidos tamaño del array de pedidos
 * @return retorna el primer indice que tenga isEmpty COMPLETADO encontrado ó  -1 si no encontró ninguno
 */
int BuscarCompletadoPedidos(ePedidos listaPedidos[], int tamPedidos);

/**
 * @fn int BuscarCanceladoPedidos(ePedidos[], int)
 * @brief Recorre el array y busca un pedido que tenga isEmpty CANCELADO
 *
 * @param listaPedidos array de pedidos
 * @param tamPedidos tamaño del array de pedidos
 * @return retorna el primer indice que tenga isEmpty CANCELADO encontrado ó  -1 si no encontró ninguno
 */
int BuscarCanceladoPedidos(ePedidos listaPedidos[], int tamPedidos);

/**
 * @fn int ePedidos_BuscarPorID(ePedidos[], int, int)
 * @brief  Recorre el array y busca un pedido que coincida con el id recibido como parametro
 *
 * @param listaPedido listaPedidos array de pedidos
 * @param tamPedidos tamPedidos tamaño del array de pedidos
 * @param ID id de pedido solicitado
 * @return retorna el indice que coincide con el id ingresado ó  -1 si no encontró ninguno
 */
int ePedidos_BuscarPorID(ePedidos listaPedido[], int tamPedidos, int ID);


/**
 * @fn ePedidos PedirDatosPedidos(int*)
 * @brief pide los datos y los asigna a una ePedidos auxiliar
 *
 * @param retorno puntero a entero para devolver -1 si los datos ingresados son correctos ó 0 si son correctos
 * @return retorna el ePedidos auxiliar con los datos cargados
 */
ePedidos PedirDatosPedidos(int* retorno);

/**
 * @fn int AltaPedidos(ePedidos[], int, int*)
 * @brief Llama a BuscarLibrePedidos, luego pide los datos con PedirDatosPedidos y los carga a un ePedidos auxiliar.
 * Pide que se confirme el alta y asigna los datos pedidos al ePedido en el indice libre encontrado.
 *
 * @param listaPedidos listaPedidos array de pedidos
 * @param tamPedidos tamPedidos tamaño del array de pedidos
 * @param idPedido puntero a entero para asignar en el alta un id único
 * @return -1 si no se encontro espacio libre, -2 si los dartos ingresados son incorrectos, 0 si el alta fue cancelado y 1 si el alta se confirmo
 */
int AltaPedidos(ePedidos listaPedidos[], int tamPedidos, int* idPedido);

/**
 * @fn int CancelarPedidos(ePedidos[], int)
 * @brief Muestra los pedidos, pide un id y cambia el estado a isEmpty CANCELADO
 *
 * @param listaPedidos listaPedidos array de pedidos
 * @param tamPedidos  tamPedidos tamaño del array de pedidos
 * @return -1 si no se confirmó la gestión. 0 si se confirmo
 */
int CancelarPedidos(ePedidos listaPedidos[], int tamPedidos);

/**
 * @fn int ProcesarPedidos(ePedidos[], int)
 * @brief Permite ingresar los kilos de cada tipo de plastico a reciclar
 *
 * @param listaPedidos listaPedidos array de pedidos
 * @param tamPedidos tamPedidos tamaño del array de pedidos
 * @return-0 si se canceló la modificacion, 1 si se confirmó la cancelación, -1 error
 */
int ProcesarPedidos(ePedidos listaPedidos[], int tamPedidos);

void MostrarAuxiliarPedido(ePedidos auxiliarPedido);
void MostrarUnPedido(ePedidos unPedido);
int MostrarTodosLosPedidos(ePedidos listaPedidos[], int tamPedidos);
int MostrarPedidosPendientes(ePedidos listaPedidos[], int tamPedidos);



#endif /* PEDIDO_H_ */
