/**
 * Programa de prueba para verificar conocimientos teoricos 
**/

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Hasta que no le pasemos el comando "start" el programa no realiza nada
  if (Serial.available()) {
    String texto = Serial.readString(); 
    texto.trim();

    if (texto == "start") {
      Serial.println("OK");
      testLoop(); 
    }
  }
}

// Funcion de calculo 
void testLoop() {
  volatile unsigned long i;
  volatile unsigned int sumaEntera = 0;
  volatile float sumaFloat = 0.0;
  
  unsigned long start = micros();

  // Operaciones con enteros
  for(i = 0; i <= 500000; i++){
    sumaEntera++;
    yield();
  }

  // Operaciones con flotantes  
  for(i = 0; i <= 1000000; i++){
    sumaFloat = sumaFloat + 1.2;
    yield();
  }

  unsigned long end = micros();

  // Calculo y Visualizacion del tiempo de ejecucion + Frec CPU
  Serial.print("Frecuencia: ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("Tiempo (microsegundos): ");
  Serial.println(end - start);
}
