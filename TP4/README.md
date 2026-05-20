# Trabajo Práctico 4 - Módulos de Kernel y llamadas a Sistema
## Integrantes

- Santiago Alasia
- Lucia Feiguin
- Elena Monutti

## Link del Repositorio

```
https://github.com/SantiagoAlasia/The-Pipeliners/tree/main/TP4
```

## Introducción

## Objetivos 

## Desafio 1

### ¿Qué es checkinstall y para qué sirve?
### ¿Se animan a usarlo para empaquetar un hello world? 
### Revisar la bibliografía para impulsar acciones que permitan mejorar la seguridad del kernel, concretamente: evitando cargar módulos que no estén firmados. rootkits ? 

## Desafio 2

### Debe tener respuestas precisas a las siguientes preguntas y sentencias:
1. ¿Qué funciones tiene disponible un programa y un módulo?
2. Espacio de usuario o espacio del kernel.
3. Espacio de datos.
4. Drivers. Investigar contenido de /dev.

## Desafio 3

### Pasos para la compilación y carga de un módulo de kernel.

```
cd kernel-modules/part1/module
```

```
make clean
make all
```

```
sudo insmod mimodulo.ko
```

```
sudo dmesg
```

![Salida del comando "sudo dmesg"](/TP4/img/Cap1.png)

*Figura 1: Log de eventos luego de cargar el módulo de kernel.*

```
lsmod | grep mod
```

![Salida del comando "lsmod | grep mod"](/TP4/img/Cap2.png)

*Figura 2: Lista de módulos cargados filtrados por "mod"*


```
sudo rmmod mimodulo
```

```
sudo dmesg
```

![Salida del comando "sudo dmesg"](/TP4/img/Cap3.png)

*Figura 3: Log de eventos luego de quitar el módulo de kernel.*

```
lsmod | grep mod
```

![Salida del comando "lsmod | grep mod"](/TP4/img/Cap4.png)

*Figura 4: Lista de módulos cargados filtrados por "mod"*

```
/proc/modules es un archivo del virtual filesystem que muestra los módulos del kernel que están actualmente cargados en memoria. Para poder ver el contenido podemos ejecutar el siguiente comando.

cat /proc/modules  | grep mod
```

![Salida del comando "cat /proc/modules  | grep mod"](/TP4/img/Cap5.png)

*Figura 5: Lista de módulos cargados filtrados por "mod"*

```
modinfo mimodulo.ko 
```

![Salida del comando "modinfo mimodulo.ko"](/TP4/img/Cap6.png)

*Figura 6: Informacion del modulo*

```
modinfo /lib/modules/$(uname -r)/kernel/crypto/des_generic.ko
```

![Salida del comando "modinfo /lib/modules/$(uname -r)/kernel/crypto/des_generic.ko"](/TP4/img/Cap7.png)

*Figura 7: Informacion del modulo crypto*

## Conclusión general
