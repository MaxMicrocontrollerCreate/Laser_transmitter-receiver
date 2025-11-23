#define SENSOR A0
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


String Receive(){
  String inputStr = "";
  bool firstSymbol = true;
  int zeroCount = 0;
  int delaySig = 30;
  while (zeroCount < 15){
    if (analogRead(SENSOR) < 100){
      analogWrite(B, 1023);
      inputStr += '1';
      zeroCount = 0;
    }
    else{
      analogWrite(B, 0);
      inputStr += '0';
      zeroCount++;
   }
   if (firstSymbol or delaySig == 0){
    delay(5);
    firstSymbol = false;
    delaySig = 30;
   }
   else{
    delay(10);
    delaySig--;
   }
  }

  return inputStr;
}

String ClearSignal(String rawSignal){
  String clearSig = rawSignal;
  clearSig.remove(0,3);
  clearSig.remove(clearSig.length()-17, 17);
  return clearSig;
}

String Decoding(String clearBin){
  String operPart = "";
  String result = "";
  for(int i = 0; i < clearBin.length()/6; i++){
    operPart += clearBin[(i*6)];
    operPart += clearBin[(i*6)+1];
    operPart += clearBin[(i*6)+2];
    operPart += clearBin[(i*6)+3];
    operPart += clearBin[(i*6)+4];
    operPart += clearBin[(i*6)+5];
    for(int j = 0; j< 63; j++){
      if(operPart == symbolsBin[j]){
        result+=symbols[j];
        operPart = "";
        break;
      }
    }
  }
  return result;
}
void setup(){
  Serial.begin(9600);
}

void loop(){
  bool waiting = true;
  while(waiting){
    if (analogRead(SENSOR) < 75) waiting = false;
    delay(0);
  }
  String rawStr = Receive();
  Serial.println(ClearSignal(rawStr));
  Serial.println(Decoding(ClearSignal(rawStr)));
  waiting = true;
}
