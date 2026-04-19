# Trabajo Práctico 2 - Stack Frame

## Integrantes

- Santiago Alasia
- Lucia Feiguin
- Elena Monutti

## Introducción
El presente trabajo práctico tiene como objetivo explorar la interacción entre distintos niveles de abstracción en sistemas computacionales, integrando lensuajes de alto nivel con programación de bajo nivel.
Se implementa una solución que obtiene datos reales desde una API REST (índice de GINI del Banco Mundial), los procesa en distintas capas del sistema y delega la parte de cálculo a rutinas escritas en lenguaje ensamblador. Este enfoque permite evidenciar cómo los lenguajes de alto nivel dependen de mecanismos de bajo nivel para ejecutar operaciones sobre el hardware. 

## Objetivos 
- Comprender la arquitectura en capaz de un sistema
- Implementar consumo de datos desde una API REST
- Integrar Python con C mediante librerías compartidas
- Aplicar convenciones de llamadas entre C y ensamblador
- Utilizar el stack para el pasaje de parámetros y retorno de valores
- Implementar y ejecutar rutinas en ensamblador dentro de un flujo real de aplicación

### 1. Primera instancia del proyecto
En la primera versión del trabajo se implementó una solución completamente en Python, enfocada en la obtención y procesamiento de datos.
Se desarrolló un cliente que consume la API del Banco Mundial utilizando la biblioteca requests, construyendo dinámicamente la URL en función del año ingresado por el usuario. La respuesta en formato JSON es procesada para extraer el valor del índice de GINI correspondiente.
Esta versión permitió validar: 
- La correcta comunicación con la API.
- El procesamiento de datos externos.
- La lógica general del flujo del sistema.
Sin embargo, no incluía aún interacción con lenguajes de bajo nivel.

### 2. Segunda instancia del proyecto

---

## Conclusión general
