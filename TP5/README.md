# Trabajo Práctico 5 - Device drivers
## Integrantes

- Santiago Alasia
- Lucia Feiguin
- Elena Monutti

## Link del Repositorio

```
https://github.com/SantiagoAlasia/The-Pipeliners/tree/main/TP5
```

## Introducción

Los Controladores de Dispositivos de Caracteres (Character Device Drivers, CDD) constituyen uno de los mecanismos fundamentales mediante los cuales el sistema operativo Linux permite la comunicación entre el espacio de usuario y los dispositivos de hardware. A través de estos controladores, las aplicaciones pueden acceder a periféricos utilizando una interfaz estándar basada en operaciones de lectura y escritura.

En el presente trabajo práctico se desarrolla un CDD para Linux ejecutándose sobre una **Raspberry Pi Modelo 3B**, capaz de adquirir periódicamente dos señales externas digitales cuyo periodo es de 1 segundo. El controlador realiza el muestreo de las señales con una frecuencia de 20Hz (**cumpliendo con el teorema Nyquist-Shannon) y proporciona una interfaz de acceso mediante un dispositivo de caracteres. Además, permite seleccionar dinámicamente cuál de las dos señales será leída por las aplicaciones de usuario.

Como complemento al controlador, se implementa una aplicación de usuario encargada de obtener los datos desde el dispositivo de caracteres, procesarlos y representarlos gráficamente en función del tiempo. La aplicación también permite seleccionar la señal a visualizar y actualizar el gráfico en consecuencia. Para facilitar la interacción con el sistema y minimizar los requerimientos de hardware, la visualización se realiza mediante una interfaz web accesible desde cualquier navegador.

Todo el desarrollo se lleva a cabo utilizando compilación cruzada (cross-compilation), donde el código fuente es escrito y compilado en una computadora anfitriona, generando binarios compatibles con la arquitectura **ARM** de la **Raspberry Pi**. Posteriormente, estos binarios son transferidos al dispositivo para su ejecución y validación.

## Objetivos 

Diseñar e implementar un Controlador de Dispositivo de Caracteres (CDD) para Linux que permita adquirir dos señales externas mediante una Raspberry Pi y proveer una interfaz de comunicación con aplicaciones de usuario para su visualización y monitoreo en tiempo real.

### Objetivos Específicos

* Comprender el funcionamiento de los controladores de dispositivos de caracteres dentro del kernel de Linux.
* Implementar un módulo del kernel capaz de registrar y administrar un dispositivo de caracteres.
* Configurar y utilizar GPIOs de la Raspberry Pi para la adquisición de señales digitales externas.
* Aplicar técnicas de compilación cruzada para generar binarios compatibles con la arquitectura ARM de la Raspberry Pi.
* Validar el correcto funcionamiento del sistema completo mediante pruebas sobre hardware real.

## Desarrollo

### Creación del primer módulo del kernel
---

Como primera aproximación al desarrollo de drivers Linux, se implementó un módulo básico del kernel escrito en lenguaje C.

El módulo implementa dos funciones principales:

- Una función de inicialización ejecutada al cargar el módulo mediante `insmod`.
- Una función de salida ejecutada al remover el módulo mediante `rmmod`.

Estas funciones se registran utilizando las macros module_init() y module_exit(), las cuales forman parte de la infraestructura estándar para módulos Linux.

Además, se utilizó la función printk() para registrar mensajes en el log del kernel, permitiendo verificar el correcto funcionamiento del módulo mediante el comando dmesg.

**Compilación del módulo**

La compilación del módulo se realizó utilizando el sistema de build provisto por el kernel Linux mediante un archivo `Makefile`.

```
make
```
Como resultado, el sistema generó el archivo `tp_driver.ko`, correspondiente al módulo compilado listo para ser cargado dinámicamente en el kernel Linux.

<div align="center">
  <img src="img/Cap1.png"><br>
  <em>Figura 1: Compilación exitosa del módulo del kernel y generación del archivo tp_driver.ko.</em>
</div>

**Inserción y Verificacion del módulo**

Una vez compilado el módulo, se procedió a cargarlo dinámicamente en el kernel utilizando el comando:

```
sudo insmod tp_driver.ko
```

La correcta inserción del módulo se verificó mediante:

```
lsmod | grep tp_driver
```

Posteriormente, el módulo fue removido utilizando:

```
sudo rmmod tp_driver
```

Este procedimiento permitió validar el correcto funcionamiento de las funciones de inicialización y salida implementadas en el módulo.

<div align="center">
  <img src="img/Cap2.png"><br>
  <em>Figura 2: Verificación de la correcta carga del módulo `tp_driver` en el kernel Linux.</em>
</div>

**Verificación mediante dmesg**

Los mensajes generados por el módulo fueron verificados mediante el comando:

```
sudo dmesg | tail
```

A través de este mecanismo fue posible observar los mensajes emitidos por `printk()` durante la carga y descarga del módulo.

Esto permitió confirmar la correcta ejecución de las funciones del módulo dentro del espacio de kernel.

<div align="center">
  <img src="img/Cap3.png"><br>
  <em>Figura 3: Mensajes del kernel generados durante la carga y descarga del módulo.</em>
</div>

### Implementación del CDD
---

Tras validar el correcto funcionamiento de un módulo básico de pruebas en el espacio de kernel, se procedió al diseño y desarrollo del driver definitivo. Sin embargo, como instancia previa a la programación del hardware, resultó nesesario preparar el entorno de **desarrollo cruzado** para garantizar un flujo de trabajo eficiente.

**Proceso de Compilación Cruzada (Cross-Compilación)**

Para la construcción del módulo de kernel se implementó un flujo de compilación cruzada (cross-compilación). Este proceso consiste en utilizar una máquina anfitriona (Host con arquitectura x86_64) con alta capacidad de procesamiento para generar un binario ejecutable final destinado a una arquitectura de hardware completamente diferente (Target con arquitectura ARM64 de 64 bits).

Para que la **cross-compilación** fuera exitosa, se procedió a configurar un entorno de desarrollo integrado que coordinó tres variables esenciales a través del sistema de construcción de Linux (Kbuild). En primer lugar, se instaló y declaró el toolchain específico mediante la bandera `CROSS_COMPILE=aarch64-linux-gnu-`, forzando al sistema a invocar las herramientas de traducción de instrucciones para `ARM64`. En segundo lugar, se configuró la variable `ARCH=arm64` para empaquetar el módulo bajo las reglas de dicha arquitectura. Finalmente, el Makefile se enlazó de forma directa con las cabeceras y el código fuente clonado de la versión exacta del núcleo de la placa destino (rama `Linux Raspberry Pi 6.1.8`), garantizando que las estructuras de datos y macros del kernel coincidan al momento de la inserción dinámica con `insmod`.

**Implementación de Arquitectura GPIO Moderna (gpiod)**

La vinculación del hardware no se realiza de forma estática en el código de C, sino que se delega al Device Tree Overlay (gpio_overlay.dts). Este archivo define un nodo compatible con la firma "the-pipeliners,gpio-driver", reservando los pines físicos GPIO 20 y GPIO 21 bajo los alias lógicos "sensor1" y "sensor2". Cuando el kernel detecta la carga de este overlay, dispara la función de inicialización `probe` del driver de plataforma. Dentro de esta rutina, el módulo utiliza la API segura `devm_gpiod_get()` para solicitar los descriptores de las líneas configuradas como entradas (GPIOD_IN). Este enfoque no solo blinda el acceso al hardware aislando los pines de otros procesos, sino que permite conmutar de forma segura entre canales en tiempo de ejecución escribiendo un carácter ('1' o '2') en `/dev/gpio_driver`.

**Muestreo Periódico Mediante Temporizadores de Kernel (Timers)**

Para recolectar el nivel lógico de los sensores sin usar un **polling** continuo que degradaría críticamente el rendimiento del sistema operativo, se implementó un timer del kernel mediante la estructura struct `timer_list`.

Durante la fase de inicialización (`probe`), el driver configura y acopla este temporizador interno a una función de `callback` dedicada encargada de realizar la lectura física del hardware de forma automatizada. El temporizador se calibra utilizando la variable del sistema `jiffies` para dispararse con una periodicidad controlada. Cada vez que expira el ciclo de tiempo establecido, la función `callback` interroga al descriptor GPIO activo mediante la llamada no bloqueante `gpiod_get_value()`, guarda el estado digital en una variable global segura para su posterior lectura desde el espacio de usuario (`copy_to_user`), y vuelve a programar el temporizador de manera recursiva empleando la macro `mod_timer()`. Este diseño asincrónico asegura un muestreo predecible, determinista y de bajo impacto para el planificador de tareas de Linux.

### Desarrollo de la Interfaz Web
---

La capa de aplicación fue diseñada siguiendo una arquitectura que separa claramente la adquisición de datos de la lógica de visualización. El componente principal de esta capa es el archivo `app.py`, encargado de actuar como intermediario entre el driver de caracteres y la interfaz web. Su funcionamiento se divide en dos responsabilidades fundamentales:

- *Adquisición de datos*: La adquisición de muestras se realiza mediante un hilo de ejecución secundario (`acquisition_loop`) que opera de forma independiente del servidor web. Este hilo efectúa lecturas periódicas sobre el dispositivo de caracteres (`/dev/gpio_driver`) utilizando operaciones no bloqueantes, con una frecuencia aproximada de 20 Hz.

Las muestras obtenidas son almacenadas en memoria dentro de una estructura que funciona como un búfer circular de hasta 400 elementos. Esta estrategia permite conservar únicamente las mediciones más recientes, limitando el consumo de memoria y garantizando una actualización eficiente de los datos mostrados al usuario.

- *Comunicación entre cliente y servidor*: Para permitir la interacción con la interfaz web se implementó una API REST sencilla compuesta por dos rutas principales:

* **`/data`**: proporciona al navegador las últimas muestras adquiridas junto con la información de estado necesaria para la visualización. Los datos son serializados en formato JSON, facilitando su procesamiento mediante JavaScript en el lado del cliente.

* **`/signal`**: recibe solicitudes HTTP de tipo POST generadas por el usuario cuando desea cambiar la señal monitoreada. La aplicación traduce estas solicitudes en operaciones de escritura sobre el dispositivo de caracteres, permitiendo que el controlador seleccione dinámicamente cuál de las entradas GPIO será utilizada para la adquisición de datos.

**Visualización de las señales**

El gráfico utiliza un eje temporal fijo que muestra una ventana con referencias temporales relativas que van desde **−3 s** hasta el instante actual, identificado como **"Ahora"**.

La aplicación actualiza periódicamente el gráfico utilizando las muestras más recientes almacenadas en el búfer. De esta manera, la señal se desplaza de forma continua a lo largo de la pantalla, permitiendo observar su evolución en tiempo real sin necesidad de realizar desplazamientos manuales. Además, cuando el usuario selecciona una señal diferente, la visualización se reinicia automáticamente para evitar mezclar datos pertenecientes a distintas fuentes y garantizar una representación coherente de la nueva medición.

En las siguientes figuras podemos ver como quedo la interfaz web para cada una de las señales.

#### Señal 1

<div align="center">
  <img src=""><br>
  <em>*Figura X. Ventana correspondiente a la señal 1*</em>
</div>

#### Señal 2

<div align="center">
  <img src=""><br>
  <em>*Figura Y.Ventana correspondiente a la Señal 2.*</em>
</div>


### Creación de un generador de señales para testing
---

Con el objetivo de validar el correcto funcionamiento del controlador desarrollado y de la aplicación de visualización, se implementó un generador de señales utilizando una placa **Arduino UNO**. Este generador permite producir de forma controlada dos señales digitales periódicas independientes, las cuales son enviadas a los GPIO de la Raspberry Pi para su posterior adquisición por parte del driver.

La utilización de un generador dedicado resultó especialmente útil durante las etapas de desarrollo y depuración, ya que permitió disponer de señales conocidas y repetibles, facilitando la verificación del comportamiento del sistema ante distintos patrones de entrada.

El programa desarrollado para el Arduino genera dos señales digitales periódicas a través de dos pines de salida distintos. Ambas señales poseen un período de un segundo, cumpliendo con los requisitos establecidos en el enunciado del trabajo práctico. Sin embargo, cada una presenta una forma de onda diferente, lo que permite comprobar que el sistema es capaz de distinguir correctamente entre ambas señales y actualizar la visualización cuando el usuario selecciona una u otra.

La forma temporal de las señales generadas se muestra a continuación:

#### Señal 1

<div align="center">
  <img src=""><br>
  <em>*Figura X. Forma de onda correspondiente a la Señal 1.*</em>
</div>

#### Señal 2

<div align="center">
  <img src=""><br>
  <em>*Figura Y. Forma de onda correspondiente a la Señal 2.*</em>
</div>

Gracias a este banco de pruebas fue posible verificar el funcionamiento integral del sistema, desde la captura de datos en los GPIO, pasando por la comunicación entre el espacio de kernel y el espacio de usuario, hasta la correcta representación gráfica de las señales en la interfaz web.

### Automatización del proceso de carga y descarga del sistema completo
---

Durante la etapa de desarrollo y pruebas fue necesario cargar y descargar repetidamente todos los componentes del sistema, incluyendo el Device Tree Overlay, el módulo del kernel y la aplicación de usuario. Con el objetivo de simplificar este procedimiento, se desarrollaron dos scripts en Bash que automatizan completamente el despliegue y la desinstalación del sistema: `deploy.sh` y `undeploy.sh`.

El script `deploy.sh` se encarga de preparar el entorno de ejecución realizando de manera secuencial las siguientes tareas:

- Eliminar posibles configuraciones residuales provenientes de ejecuciones anteriores.
- Cargar el Device Tree Overlay (`my_overlay.dtbo`) para habilitar la configuración de hardware necesaria.
- Insertar el módulo del kernel (`gpio_driver.ko`) mediante `insmod`.
- Ajustar los permisos del archivo de dispositivo `/dev/gpio_driver`, permitiendo que la aplicación de usuario pueda acceder al controlador sin restricciones adicionales.
- Activar automáticamente el entorno virtual de Python utilizado por la aplicación.
- Iniciar la aplicación de usuario (`app.py`), responsable de la adquisición y visualización de datos.

Por otro lado, el script `undeploy.sh` realiza el proceso inverso, liberando todos los recursos utilizados por el sistema. Entre sus funciones se encuentran la descarga del módulo del kernel y la eliminación de las configuraciones aplicadas durante el despliegue.

La utilización de estos scripts permitió reducir significativamente el tiempo necesario para iniciar y finalizar las pruebas, además de garantizar que todos los integrantes del grupo ejecutaran exactamente la misma secuencia de pasos. Esto mejoró la reproducibilidad de los ensayos, facilitó las tareas de depuración y minimizó errores humanos asociados a la configuración manual del sistema.

## Resultados Obtenidos



## Conclusión general

## Bibliografia Consultada

- Implementation of Linux GPIO Device Driver on Raspberry Pi Platform - Vu Nguyen.
- Linux Driver Development with Raspberry Pi.
- Material de la catedra.
- Raspberry Pi Foundation, Linux Kernel Source Tree for Raspberry Pi. GitHub. Disponible en: https://github.com/raspberrypi/linux. 
- Tutoriales de Johannes4Linux. Disponible en: https://github.com/Johannes4Linux/Linux_Driver_Tutorial
- Kernel Device Tree.