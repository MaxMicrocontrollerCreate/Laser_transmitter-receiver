#define LASER A0
#define R A1
#define G A2
#define B A3

const char *symbolsBin[63] = {"000001", "000010", "000011", "000100", "000101", "000110", "000111",
                              "001000", "001001", "001010", "001011", "001100", "001101", "001110", "001111",
                              "010000", "010001", "010010", "010011", "010100", "010101", "010110", "010111",
                              "011000", "011001", "011010", "011011", "011100", "011101", "011110", "011111",
                              "100000", "100001", "100010", "100011", "100100", "100101", "100110", "100111",
                              "101000", "101001", "101010", "101011", "101100", "101101", "101110", "101111",
                              "110000", "110001", "110010", "110011", "110100", "110101", "110110", "110111",
                              "111000", "111001", "111010", "111011", "111100", "111101", "111110", "111111"
                            };
const char symbols[63] = "0123456789abcdefghijklmnopqrstuvwxyz.,?!+-*/=()[]{}@#%&\"<>~;: ";

String Coding(String data){
  String exitStr = "11";
  for(int i = 0; i < data.length(); i++){
    for(int j = 0; j<63; j++){
      if (symbols[j] == data[i]){
        exitStr+=symbolsBin[j];
        break;
      }
    }
  }
  exitStr += "11";
  Serial.println(exitStr);
  return exitStr;
}

void Send(String inputs){
  for(int i = 0; i < inputs.length(); i++){
    if (inputs[i] == '1'){
      analogWrite(LASER, 1023);
      analogWrite(B, 1023);
    }
    else{
      analogWrite(LASER, 0);
      analogWrite(B, 0);
    }
    delay(10);
  }
  analogWrite(LASER, 0);
  analogWrite(B, 0);
}

void setup() {
  Serial.begin(9600);
}

String str = "";
void loop() {
  
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if(incomingByte != 10) str+=(char)incomingByte;
    else{
      Serial.println(str);
    Send(Coding(str));
    str = "";
    }
  }
}
