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


