/*
 * Cliente.h
 *
 *  Created on: 12 oct. 2021
 *      Author: Usuario
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "UTN_Input.h"
#include "Localidad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct
{
 int idClientes;
  char nombreEmpresa[20];
  char cuit[20];
  char direccion[20];
  int idLocalidad;
  int idPedido;
  int isEmptyClientes;
}typedef eClientes;


#define OCUPADO 2
#define LIBRE 1
#define BAJA -1
#define PEDIDO_PENDIENTE -1
#define TAM_BUFFER 30



void InicializarClientes(eClientes listaClientes[], int tamClientes);
void HarcodearClientes(eClientes listaClientes[], int tamClientes);

int BuscarLibreClientes(eClientes listaClientes[], int tamClientes);
int eClientes_BuscarPorID(eClientes listaCliente[], int tamClientes, int ID);
int BuscarOcupadoClientes(eClientes listaClientes[], int tamClientes);
int BuscarBajaClientes(eClientes listaClientes[], int tamClientes);


eClientes PedirDatosClientes(int *retorno, eLocalidades listaLocalidades[], int tamLocalidades);
int AltaClientes(eClientes listaTrabajos[], int tamClientes, int* id, eLocalidades listaLocalidades[], int tamLocalidades);
int EliminarClientes(eClientes listaClientes[], int tamClientes);
int ModificarClientes(eClientes listaClientes[], int tamClientes, eLocalidades listaLocalidades[], int tamLocalidades);

void MostrarAuxiliarCliente(eClientes auxiliarCliente);
void MostrarUnCliente(eClientes unCliente);
int MostrarTodosLosClientes(eClientes listaClientes[], int tamClientes);


#endif /* CLIENTE_H_ */
