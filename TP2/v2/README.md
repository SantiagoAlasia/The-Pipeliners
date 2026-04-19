# Instructivo para ejecutar el programa

## Ejecucion manual (v2: Python + C + ASM)
```
    cd c

    # Compilar ASM
    nasm -f elf64 gini_asm.s -o gini_asm.o

    # Compilar C
    gcc -c -fPIC gini.c -o gini.o

    # Crear librería compartida
    gcc -shared -o libgini.so gini.o gini_asm.o

    cd ../src

    python3 main.py
```  

## Ejecución con Docker
```
    sudo docker build -t mi_app .

    sudo docker run -it mi_app
```    