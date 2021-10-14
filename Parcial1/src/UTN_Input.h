/*
 * UTN_Input.h
 *
 *  Created on: 12 oct. 2021
 *      Author: Usuario
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef UTN_INPUT_H_
#define UTN_INPUT_H_


int getString(char* cadena, int longitud);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getCuit(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int esSoloNumerica(char* cadena);
int esSoloLetras(char* cadena);
int esAlfanumerica(char* cadena);
int esTelefono(char* cadena);
char Pedir_Char(char MSJ[], char ERROR_MSJ[]);
int ConfirmarGestion(char MSJ[], char ERROR_MSJ[]);
int Validar_OnlyAlphabet(char buffer[]);
int Validar_OnlyAlphabetWithSpaces(char buffer[]);

#endif /* UTN_INPUT_H_ */
