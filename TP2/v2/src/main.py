import requests
from gini import procesar_gini

# Constantes
PAIS = "ARG"
INDICADOR = "SI.POV.GINI"
ANIO_ACTUAL = 2026

def pedir_anio():
    print(">>> Indice GINI del Banco Mundial")

    while True:
        try:
            anio = int(input("\n>>> Ingrese el año (1978 - presente): "))

            if 1978 <= anio <= 2026:
                break
            else:
                print(">>> Año fuera de rango, vuelva a intentarlo")

        except ValueError:
            print(">>> Hay que ingresar número")

    return anio

def construir_url(anio):
    # Creamos la url en base a las constantes y el año requerido
    return f"https://api.worldbank.org/v2/country/{PAIS}/indicator/{INDICADOR}?date={anio}&format=json"
    
def obtener_datos(url):
    res = requests.get(url)

    if not res: 
        print("\n>>> Respuesta de la API: Fallida")
        print(res.status_code)
        return None
    
    print("\n>>> Respuesta de la API: OK")
    return res.json()
  
def extraer_gini(data):
    for entry in data[1]:
        if entry["value"] is not None:
            return float(entry["value"])
    
    return None

def main():
    anio = pedir_anio()
    url = construir_url(anio)
    data = obtener_datos(url)

    if data:
        gini = extraer_gini(data)
        print(">>> Gini Original: ", gini)
    else:
        print(">>> No se pudieron obtener datos")

    # Llamado a la funcion en C
    res = procesar_gini(gini)
    print("\n>>> Gini + 1: ", res)

if __name__ == '__main__':
    main()