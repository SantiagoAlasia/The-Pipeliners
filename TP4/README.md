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

Un programa de usuario utiliza funciones provistas por bibliotecas del sistema (como libc) y accede a los recursos del sistema operativo mediante **system calls (syscalls)**. Algunas de las más comunes son:

```
open(),
read(),
write(),
etc.
```

Estas llamadas permiten interactuar con archivos, dispositivos y otros recursos del sistema de **manera controlada** y **segura**, ya que el sistema operativo restringe el acceso directo al hardware y a la memoria del kernel.

En cambio, un módulo del kernel se ejecuta en espacio de kernel, por lo que no utiliza bibliotecas de usuario como libc. Las funciones y símbolos que puede utilizar son proporcionados por el kernel.

Estas funciones pueden observarce en el archivo ´/proc/kallsyms´, el cual contiene la tabla de símbolos del kernel cargados actualmente en memoria, incluyendo funciones y variables globales disponibles para otros módulos.

Por ejemplo:

```
printk()
```

2. Espacio de usuario o espacio del kernel.

Cada proceso de usuario posee su propio espacio de memoria aislado, lo que evita que un programa pueda acceder directamente a la memoria de otro proceso o del kernel. Esta separación aporta estabilidad y seguridad al sistema. Cuando un programa de usuario falla, normalmente solo finaliza dicho proceso sin afectar al resto del sistema operativo.

Por otro lado, el kernel y los módulos cargados se ejecutan dentro del espacio del kernel, compartiendo el mismo **espacio de memoria privilegiado**. Debido a esto, un error dentro de un módulo del kernel puede comprometer la estabilidad de todo el sistema, provocando fallas graves.

En la *Figura 1* puede observarse una distribución lógica entre el espacio de usuario y el espacio del kernel.

<div align="center">
  <img src="img/Cap-User-Kernel-Space.png"><br>
  <em>Figura 1: Espacio de Usuario vs Espacio del Kernel</em>
</div>

3. Espacio de datos.

El espacio de datos es la región de memoria de un programa donde se almacenan las **variables** y **datos utilizados** durante su ejecución. Este es fundamental porque contiene el estado y la información que utiliza el programa mientras se ejecuta.

Dentro de la memoria de un proceso existen distintas secciones, cada una con un propósito específico. Las secciones `.data` y `.bss` forman parte del espacio de datos del programa. Además, durante la ejecución el programa puede reservar memoria dinámica en el **heap** utilizando funciones como `malloc()`.

En el caso de los módulos del kernel sucede algo similar, aunque la memoria es administrada directamente por el kernel mediante funciones como `kmalloc()`.

4. Drivers. Investigar contenido de /dev.

Los **Drivers** o controladores de dispositivos son un módulos especiales que proporcionan funcionalidad para un hardware especifico, como discos, teclados, placas de red, GPU o dispositivos USB. Como en los sistemas **Unix** los dispositivos se mapean como archivos, los vamos a encontrar asociados con alguna entrada en `/dev`. Esto permite interactuar con el hardware utilizando operaciones similares a las realizadas sobre archivos comunes, como `read()` o `write()`.

Para inspeccionar el contenido de `/dev` pueden utilizarse los siguientes comandos:

```
cd /dev
```

```
ls -l
```

La salida mostrará distintos archivos asociados a dispositivos del sistema. Por ejemplo:

```
brw-rw----  1 root disk      8,     0 jul 11  2025 sda

crw-rw-rw-  1 root tty       5,     0 may 20 12:15 tty
```

> **Obs:** En esta salida puede observarse que al comienzo aparece una letra que indica el tipo de dispositivo:
>- **c**	dispositivo de caracteres (character device)
>- **b**	dispositivo de bloques (block device)
>
>Los dispositivos de caracteres transfieren información byte a byte, como terminales o teclados. En cambio, los dispositivos de bloques
>trabajan con bloques de datos, como discos rígidos o pendrives.
>
>Además, aparecen dos números llamados **mayor** y **menor**:
>- El número **mayor** identifica al driver o controlador asociado al dispositivo.
>- El número **menor** identifica una instancia específica controlada por ese driver.
>
> Por ejemplo, distintos discos pueden compartir el mismo número major (mismo driver) pero tener distintos minor para diferenciar cada 
>dispositivo físico o partición.

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

<div align="center">
  <img src="img/Cap1.png"><br>
  <em>Figura 1: Log de eventos luego de cargar el módulo de kernel.</em>
</div>

```
lsmod | grep mod
```

<div align="center">
  <img src="img/Cap2.png"><br>
  <em>Figura 2: Lista de módulos cargados filtrados por "mod".</em>
</div>

```
sudo rmmod mimodulo
```

```
sudo dmesg
```

<div align="center">
  <img src="img/Cap3.png"><br>
  <em>Figura 3: Log de eventos luego de quitar el módulo de kernel.</em>
</div>

```
lsmod | grep mod
```

<div align="center">
  <img src="img/Cap4.png"><br>
  <em>Figura 4: Lista de módulos cargados filtrados por "mod".</em>
</div>

```
/proc/modules es un archivo del virtual filesystem que muestra los módulos del kernel que están actualmente cargados en memoria. Para poder ver el contenido podemos ejecutar el siguiente comando.

cat /proc/modules  | grep mod
```

<div align="center">
  <img src="img/Cap5.png"><br>
  <em>Figura 5: Lista de módulos cargados filtrados por "mod".</em>
</div>

```
modinfo mimodulo.ko 
```

<div align="center">
  <img src="img/Cap6.png"><br>
  <em>Figura 6: Descripción del modulo.</em>
</div>

```
modinfo /lib/modules/$(uname -r)/kernel/crypto/des_generic.ko
```

<div align="center">
  <img src="img/Cap7.png"><br>
  <em>Figura 7: Descripción del modulo crypto.</em>
</div>

### Preguntas

1. ¿Qué diferencias se pueden observar entre los dos modinfo ? 
2. ¿Qué divers/modulos estan cargados en sus propias pc? comparar las salidas con las computadoras de cada integrante del grupo. Expliquen las diferencias. **Carguen un txt con la salida de cada integrante en el repo y pongan un diff en el informe.**
3. ¿cuales no están cargados pero están disponibles? que pasa cuando el driver de un dispositivo no está disponible. 
4. Correr hwinfo en una pc real con hw real y agregar la url de la información de hw en el reporte. 
5. ¿Qué diferencia existe entre un módulo y un programa  ? 
6. ¿Cómo puede ver una lista de las llamadas al sistema que realiza un simple helloworld en c?
7. ¿Qué es un segmentation fault? ¿Cómo lo maneja el kernel y como lo hace un programa?
8. ¿Se animan a intentar firmar un módulo de kernel ? y documentar el proceso ?  https://askubuntu.com/questions/770205/how-to-sign-kernel-modules-with-sign-file
9. Agregar evidencia de la compilación, carga y descarga de su propio módulo imprimiendo el nombre del equipo en los registros del kernel. 
10. ¿Que pasa si mi compañero con secure boot habilitado intenta cargar un módulo firmado por mi? 
11. Dada la siguiente nota https://arstechnica.com/security/2024/08/a-patch-microsoft-spent-2-years-preparing-is-making-a-mess-for-some-linux-users/ 
12. ¿Cuál fue la consecuencia principal del parche de Microsoft sobre GRUB en sistemas con arranque dual (Linux y Windows)?
13. ¿Qué implicancia tiene desactivar Secure Boot como solución al problema descrito en el artículo?
14. ¿Cuál es el propósito principal del Secure Boot en el proceso de arranque de un sistema?

## Conclusión general
