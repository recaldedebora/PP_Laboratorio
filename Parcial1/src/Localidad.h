/*
 * Localidad.h
 *
 *  Created on: 14 oct. 2021
 *      Author: Usuario
 */

#ifndef LOCALIDAD_H_
#define LOCALIDAD_H_


#include "UTN_Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct
{
 int idLocalidades;
  char nombreLocalidad[20];
  int isEmptyLocalidades;
}typedef eLocalidades;


#define OCUPADO 2
#define LIBRE 1
#define BAJA -1
#define PEDIDO_PENDIENTE -1
#define TAM_BUFFER 30



void InicializarLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);
void HarcodearLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);

int BuscarLibreLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);
int eLocalidades_BuscarPorID(eLocalidades listaCliente[], int tamLocalidades, int ID);
int BuscarOcupadoLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);
int BuscarBajaLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);


eLocalidades PedirDatosLocalidades(int* retorno);
int AltaLocalidades(eLocalidades listaTrabajos[], int tamLocalidades, int* id);
int EliminarLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);
int ModificarLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);

void MostrarAuxiliarLocalidad(eLocalidades auxiliarCliente);
void MostrarUnaLocalidad(eLocalidades unCliente);
int MostrarTodosLosLocalidades(eLocalidades listaLocalidades[], int tamLocalidades);

#endif /* LOCALIDAD_H_ */
