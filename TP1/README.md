# Trabajo Práctico 1 - Rendimiento de las Computadoras

## Integrantes
- Elena Monutti
- Santiago Alasia
- Lucia Feiguin

## Objetivo

El objetivo de este trabajo práctico es poner en práctica los conceptos vistos sobre **performance** y **rendimiento de las computadoras**.

El trabajo se divide en dos partes. En la primera, se analizan **benchmarks de terceros** para evaluar qué pruebas resultan más útiles según las tareas que realiza cada usuario y para comparar el rendimiento de distintos procesadores en la compilación del kernel de Linux. En la segunda parte, se utilizan herramientas de **time profiling** para medir la performance de un programa y observar cuánto tiempo consume cada función.

## 1. Benchmarks útiles según las tareas diarias

### 1.1 ¿Qué es un benchmark?

Un **benchmark** es una prueba diseñada para medir el rendimiento de un sistema frente a una tarea específica. En computación, se utilizan benchmarks para evaluar cómo se comporta un procesador, memoria o sistema completo al ejecutar ciertos programas.
No existe un único benchmark que represente todos los casos de uso. El rendimiento de un sistema depende del tipo de tarea que se esté ejecutando, por lo que el benchmark más útil será aquel que mejor represente las actividades reales del usuario.

### 1.2 ¿Qué benchmarks son más útiles según el uso?

Los benchmarks más útiles dependen directamente del tipo de tareas que realiza cada usuario en su día a día. Esto se debe a que el rendimiento no es una propiedad absoluta, sino relativa a la carga de trabajo.
En el caso de estudiantes o desarrolladores, las tareas más comunes incluyen:
- Compilar programas
- Ejecutar código
- Manejar repositorios
- Trabajar con archivos
Por lo tanto, los benchmarks que mejor representan este tipo de uso son aquellos relacionados con compilación, procesamiento de datos y operaciones sobre archivos.

### 1.3 Lista de benchmarks útiles

- **Build Linux Kernel**  
  Representa tareas de compilación intensiva. 
- **Build GCC / Build LLVM**  
  Simulan la compilación de proyectos grandes y complejos.
- **Git Benchmark**  
  Evalúa el rendimiento al trabajar con repositorios y control de versiones.
- **Compression (gzip, zstd, xz, 7zip)**  
  Representa tareas de compresión y descompresión de archivos.
- **FFmpeg / x264 / x265**  
  Utilizados para procesamiento y codificación de video.
- **Blender**  
  Benchmark de renderizado 3D.
- **OpenSSL / GnuPG**  
  Evalúan operaciones criptográficas.
- **SQLite / pgbench**  
  Representan cargas de trabajo con bases de datos.
- **TensorFlow Lite / oneDNN**  
  Utilizados para tareas de inteligencia artificial en CPU.

### 1.4 Tabla: tareas diarias y benchmark asociado

| Tarea diaria | Benchmark representativo | Justificación |
|---|---|---|
| Compilar programas en C/C++ | Build Linux Kernel | Representa una tarea real de compilación intensiva |
| Compilar proyectos grandes | Build GCC / LLVM | Simula compilaciones complejas |
| Trabajar con repositorios | Git Benchmark | Representa operaciones reales sobre archivos |
| Comprimir archivos | gzip / zstd / xz | Refleja tareas comunes del sistema |
| Procesar videos | FFmpeg / x264 | Simula carga multimedia |
| Renderizar gráficos | Blender | Representa renderizado 3D |
| Trabajar con bases de datos | pgbench / SQLite | Simula consultas y manejo de datos |
| Ejecutar modelos de IA | TensorFlow Lite | Representa procesamiento intensivo en CPU |

### 1.5 Conclusión

Los benchmarks son herramientas fundamentales para evaluar el rendimiento de un sistema, pero su utilidad depende del contexto. No existe una única prueba que represente todos los usos posibles.
Para obtener resultados significativos, es importante elegir benchmarks que reflejen las tareas reales del usuario. En este caso, para un perfil orientado a la programación, los benchmarks de compilación resultan especialmente representativos.

## 2. Comparación de procesadores compilando el kernel de Linux

### 2.1 Objetivo de la comparación

En esta sección se compara el rendimiento de distintos procesadores utilizando un benchmark real: la compilación del kernel de Linux.
Este tipo de prueba es especialmente relevante porque representa una carga de trabajo intensiva en CPU, donde intervienen múltiples factores como:
- Cantidad de núcleos
- Frecuencia del procesador
- Capacidad de paralelismo
El benchmark utilizado mide el **tiempo necesario para compilar el kernel**, por lo tanto, **menor tiempo implica mejor rendimiento**.

### 2.2 Procesadores analizados

Los procesadores evaluados en este trabajo son:
- Intel Core i5-13600K
- AMD Ryzen 9 5900X (12 núcleos)
- AMD Ryzen 9 7950X (16 núcleos)

### 2.3 Resultados del benchmark

Se utilizaron datos del benchmark **Build Linux Kernel**, que mide el tiempo de compilación del kernel de Linux.
| Procesador | Tiempo de compilación (segundos) |
|---|---:|
| Intel Core i5-13600K | 72 s |
| AMD Ryzen 9 5900X | 76 s |
| AMD Ryzen 9 7950X | 50 s |

A partir de los resultados se puede observar que:
- El **AMD Ryzen 9 7950X** presenta el mejor rendimiento, con el menor tiempo de compilación.
- El **Intel Core i5-13600K** tiene un rendimiento ligeramente superior al Ryzen 9 5900X en esta prueba.
- El **Ryzen 9 5900X** queda en último lugar entre los tres, aunque la diferencia con el i5 no es muy grande.
Esto demuestra que el rendimiento no depende únicamente de la cantidad de núcleos, sino también de la arquitectura y optimización del procesador.

### 2.4 Cálculo de aceleración (Speedup)

La aceleración o *speedup* se calcula como:
Speedup = Tiempo base / Tiempo mejorado

#### Comparación con Intel Core i5-13600K

Speedup = 72 / 50 = 1.44
El Ryzen 9 7950X es aproximadamente **1.44 veces más rápido** que el i5-13600K.

#### Comparación con AMD Ryzen 9 5900X

Speedup = 76 / 50 = 1.52
El Ryzen 9 7950X es aproximadamente **1.52 veces más rápido** que el Ryzen 9 5900X.

Estos resultados indican una mejora significativa en el tiempo de ejecución al utilizar el Ryzen 9 7950X.
Sin embargo, la aceleración no es proporcional a la cantidad de núcleos, lo cual se debe a limitaciones como:
- Overhead de paralelismo
- Partes del código que no pueden paralelizarse
- Diferencias en arquitectura
Esto coincide con el concepto de que no todo el programa puede ejecutarse en paralelo de manera perfecta.
