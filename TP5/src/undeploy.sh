#!/bin/bash

# Configuración de rutas relativas desde /TP5-SdC/
DRIVER_DIR="CDD"
MODULE_NAME="gpio_driver"
OVERLAY_NAME="my_overlay"

echo "================================================"
echo "Iniciando protocolo de limpieza y desarme del TP"
echo "================================================"

# 1. Remover el Kernel Driver de caracteres
if lsmod | grep -q "$MODULE_NAME"; then
    echo "Removiendo el módulo del Kernel ($MODULE_NAME)..."
    sudo rmmod $MODULE_NAME
    if [ $? -eq 0 ]; then
        echo "Módulo de C removido con éxito."
    else
        echo "Error al remover el módulo. Asegurate de cerrar la app web primero."
    fi
    sleep 0.2
else
    echo "El módulo $MODULE_NAME ya estaba descargado."
fi

# 2. Remover el Device Tree Overlay dinámico
if sudo dtoverlay -l | grep -q "$OVERLAY_NAME"; then
    echo "Retirando el Device Tree Overlay ($OVERLAY_NAME)..."
    sudo dtoverlay -R $OVERLAY_NAME
    if [ $? -eq 0 ]; then
        echo "Overlay dinámico removido. Pines 20 y 21 liberados."
    else
        echo "No se pudo retirar el overlay de la memoria."
    fi
    sleep 0.2
else
    echo "El overlay $OVERLAY_NAME no estaba cargado dinámicamente."
fi
