# Trabajo Práctico 3.a - UEFI
## Integrantes

- Santiago Alasia
- Lucia Feiguin
- Elena Monutti

## Introducción


## Objetivos 
Comprender la arquitectura de la Interfaz de Firmware Extensible Unificada (UEFI) como un entorno pre-sistema operativo, desarrollar binarios nativos, entender su formato y ejecutar rutinas tanto en entornos emulados como en hardware físico (bare metal).

### 1. Exploración del entorno UEFI y la SHELL

#### 1.1 Arranque en el entorno virtual

Se ejecutó el emulador QEMU utilizando el firmware UEFI provisto por OVMF, lo que permite simular un entorno pre-sistema operativo moderno en lugar del BIOS tradicional.

![alt text](img/Cap1.png)

Al iniciar, el sistema carga la UEFI Shell, la cual provee una interfaz interactiva para explorar dispositivos, memoria y ejecutar aplicaciones EFI.

![alt text](img/Cap2.png)

#### 1.2 Exploración de dispositivos (Handles y Protocolos)

Se utilizó el comando map para identificar los dispositivos disponibles en el sistema, observándose la asignación de identificadores como FS0.
Posteriormente, se accedió al sistema de archivos mediante fs0: y se listaron sus contenidos con ls, verificando la presencia de archivos en el entorno UEFI.

![alt text](img/Cap3.png)

Mediante el comando dh, se visualizaron los distintos handles y protocolos cargados por el firmware, evidenciando el modelo de abstracción de hardware utilizado por UEFI.

![alt text](img/Cap4.png)

#### 1.3 Análisis de Variables Globales (NVRAM)

Se utilizó el comando dmpstore para inspeccionar las variables persistentes almacenadas en la NVRAM. En particular, se observaron variables como BootOrder y Boot####, las cuales determinan la secuencia de arranque del sistema.

![alt text](img/Cap5.png)

Se creó una variable personalizada (TestSeguridad) utilizando el comando set, verificando posteriormente su almacenamiento mediante la visualización de variables activas.

Esto demuestra la capacidad de persistencia de datos en el entorno UEFI.

![alt text](img/Cap6.png)

#### 1.4 Footprinting de Memoria y Hardware

Se ejecutó el comando `memmap` para visualizar la distribución de memoria del sistema. 
Este comando permite identificar las distintas regiones utilizadas por el firmware UEFI, incluyendo áreas reservadas para Boot Services, Runtime Services y memoria disponible, proporcionando una visión detallada del uso de memoria en el entorno pre-OS.

![alt text](img/Cap7.png)

![alt text](img/Cap8.png)

Se utilizó el comando `pci` para listar los dispositivos conectados al bus PCI del sistema. 
Este comando permite inspeccionar el hardware detectado por el firmware, mostrando información relevante sobre dispositivos como controladores de red, almacenamiento y otros periféricos.

![alt text](img/Cap9.png)

Se ejecutó el comando `drivers` para visualizar los controladores cargados en el entorno UEFI. 
Este listado muestra los drivers responsables de gestionar los distintos dispositivos del sistema, evidenciando el modelo modular de UEFI basado en la carga dinámica de controladores.

![alt text](img/Cap10.png)

### 2. Desarrollo, compilación y análisis de seguridad
  


### 3. Ejecución en Hardware Físico (Bare Metal)

---

## Conclusión general
