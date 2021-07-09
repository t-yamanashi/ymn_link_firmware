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
  String arg = cmd.substring(1);
  int port = arg.toInt();

  if (sec == "1") {
    setdata(port, 1);
  } else if (sec == "0") {
    setdata(port, 0);
  } else if (sec == "a") {
    getdata(port);
  } else if (sec == "z") {
    getdata_all();
  } else if (sec == "s") {
    setdata_all(arg);
  } else if (sec == "x") {
    setgetdata_all(arg);
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
/*
 * Get analog data
 */
void getdata_all() {
  String data = "";
  for (int i = 0; i  <= 5; i++) {
    if( i > 0) {
      data += ",";
    }
    data += String(analogRead(i), DEC);   
  }
  Serial.print(data);
}

/*
 * Set Data All
 */
void setdata_all(String arg) {
  setdata_all_comm(arg);
  Serial.print("OK");
}

/*
 * Set Get Data All
 */
void setgetdata_all(String arg) {
  setdata_all_comm(arg);
  getdata_all();
}

/*
 * Set Data All Comm
 */
void setdata_all_comm(String arg) {
  if (arg.length() != 14) {
    Serial.print("NG");
    return;
  }
  int outval = 0;
  String inval;
  for (int i = 2; i  <= 14; i++) {
    inval = arg.substring(i, i + 1);
    outval = 0;
    if (inval == "1") {
     outval = 1; 
    }
    digitalWrite(i, outval);
  }
}
