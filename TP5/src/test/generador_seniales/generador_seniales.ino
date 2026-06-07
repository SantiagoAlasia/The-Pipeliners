#define LEN 8

bool signal1 [LEN] = {0, 0, 0, 1, 0, 1, 0, 1};
bool signal2 [LEN] = {0, 1, 1, 1, 0, 0, 1, 1};
int i = 0;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  digitalWrite(8, signal1[i]);
  digitalWrite(9, signal2[i]);

  i++;

  if(i >= LEN){
    i = 0;
  }

  delay(120);
}
