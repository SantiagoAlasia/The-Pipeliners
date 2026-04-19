# Instructivo para ejecutar el programa

## Ejecucion manual
```
    cd c

    gcc -c -fPIC gini.c -o gini.o

    gcc -shared -w -o libgini.so gini.o

    cd ../src

    python3 main.py
```  

## Ejecución con Docker
```
    sudo docker build -t mi_app .

    sudo docker run -it mi_app
```    