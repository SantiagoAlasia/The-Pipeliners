#!/bin/bash

# Configuración de rutas relativas desde /TP5-SdC/
DRIVER_DIR="CDD"
MODULE_NAME="gpio_driver"
OVERLAY_NAME="my_overlay"

echo "=?================================================="
echo "Iniciando despliegue global del TP (The-Pipeliners)"
echo "==================================================="

# 1. Limpieza preventiva del módulo anterior
if lsmod | grep -q "$MODULE_NAME"; then
    echo "Removiendo versión anterior del driver..."
    sudo rmmod $MODULE_NAME
    sleep 0.2
fi

# Remover el overlay dinámico si ya estaba cargado
if sudo dtoverlay -l | grep -q "$OVERLAY_NAME"; then
    echo "Removiendo el Device Tree Overlay anterior..."
    sudo dtoverlay -R $OVERLAY_NAME
    sleep 0.2
fi

# 2. Cargar el Device Tree Overlay en caliente
echo "Aplicando el Device Tree Overlay ($OVERLAY_NAME.dtbo)..."
if [ -f "$DRIVER_DIR/$OVERLAY_NAME.dtbo" ]; then
    sudo dtoverlay $DRIVER_DIR/$OVERLAY_NAME.dtbo
    if [ $? -ne 0 ]; then
        echo "[❌] Error al aplicar el dtoverlay."
        exit 1
    fi
else
    echo "No se encontró $DRIVER_DIR/$OVERLAY_NAME.dtbo"
    exit 1
fi

sleep 0.5

# 3. Insertar el Kernel Driver compilado
echo "Insertando el Kernel Driver ($MODULE_NAME.ko)..."
if [ -f "$DRIVER_DIR/$MODULE_NAME.ko" ]; then
    sudo insmod $DRIVER_DIR/$MODULE_NAME.ko
    if [ $? -ne 0 ]; then
        echo "Error al ejecutar insmod."
        exit 1
    fi
else
    echo "No se encontró $DRIVER_DIR/$MODULE_NAME.ko. ¿Corriste el make?"
    exit 1
fi

sleep 0.5

# 4. Modificar los permisos para Flask
echo "Aplicando chmod 666 a /dev/$MODULE_NAME..."
if [ -e "/dev/$MODULE_NAME" ]; then
    sudo chmod 666 /dev/$MODULE_NAME
else
    echo "El archivo /dev/$MODULE_NAME no se creó."
    exit 1
fi

echo "--------------------------------"
echo "¡HARDWARE CONFIGURADO CON ÉXITO!"
echo "--------------------------------"

# 5. Lanzar la aplicación de Python (Flask)
echo "Activando entorno virtual y lanzando app.py..."

source app/.venv/bin/activate

if [ -f "app/app.py" ]; then
    echo "Servidor Flask corriendo. Abrí tu navegador en http://localhost:5000"
    echo "Presioná Ctrl+C para detener la aplicación y el servidor."
    echo "=========================================================="
    
    # Ejecutamos python. Al usar sudo para los pasos previos, nos aseguramos de que
    # corra con tu usuario normal si no le ponés sudo a Python.
    python3 app/app.py
else
    echo "No se encontró app.py en la raíz de /TP5-SdC/"
fi
