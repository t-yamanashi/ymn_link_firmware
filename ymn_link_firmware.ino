String gcmd;

/*
 * Initialize the serial port and digital port
 */
void setup() {
  for (int port = 2; port <= 13; port++) {
    pinMode(port, OUTPUT);
  }
  Serial.begin(115200);
  gcmd = "";
}

/*
 * Use a semicolon as a delimiter
 * And execute the command
 */
void loop() {
  if (!Serial.available()) {
    return;
  }
  
  char data = Serial.read();
  if(data != ';') {
    gcmd += data;
    return;
  }
  
  exec(gcmd);
  gcmd = "";
}

/*
 * Parse and execute commands
 */
void exec(String cmd) {
  String sec = cmd.substring(0, 1);
  String portstr = cmd.substring(1);
  int port = portstr.toInt();

  if (sec == "1") {
    setdata(port, 1);
  } else if (sec == "0") {
    setdata(port, 0);
  } else if (sec == "a") {
    getdata(port);
  }
}

/*
 * Digital output
 */
void setdata(int port, int val) {
  if (port < 2) {
    Serial.print("NG");
    return;
  } 
  digitalWrite(port, val);
  Serial.print("OK");
}

/*
 * Get analog data
 */
void getdata(int port) {
  if (port > 5) {
    Serial.print("NG");
    return;
  } 
  String data = String(analogRead(port), DEC);
  Serial.print(data);
}
