void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (!Serial.available()) {
    return;
  }
  char cmd = Serial.read();

  if (cmd == '0' || cmd == '1') {
    led(cmd);
  } else if (cmd == 'a') {
    getdata();
  }
}

void led(char cmd) {
  int output = cmd == '1' ? HIGH : LOW;
  digitalWrite(LED_BUILTIN, output);
  Serial.print("OK;");
}

void getdata() {
  String data = String(analogRead(0), DEC);
  Serial.print(data + ";");
}
