#include <string.h>

#define MAX_TERMS 3
#define CMD_INDX 0
#define ADDR_INDX 1
#define WORD_SIZE 4

//PINS Mapping
const unsigned int clk = 23;
const unsigned int we = 25;

//Using little endian
const unsigned int address_out[WORD_SIZE] = { 22, 24, 26, 28 }; 
const unsigned int data_in[WORD_SIZE] = { 46, 48, 50, 52 };
const unsigned int data_out[WORD_SIZE] = { 47, 49, 51, 53 };

void sendAddress(unsigned int address);
void sendData(unsigned char data);

unsigned char readBits(unsigned int address);
void writeBits(unsigned int address, unsigned char data);

void setup() {
  Serial.begin(9600);
  
  pinMode(clk, OUTPUT);
  digitalWrite(clk, LOW);
  
  pinMode(we, OUTPUT);
  digitalWrite(we, LOW);
  
  for(int i = 0; i < WORD_SIZE; i++)
  {
    pinMode(address_out[i], OUTPUT);
    pinMode(data_in[i], OUTPUT);
    pinMode(data_out[i], INPUT);

    digitalWrite(address_out[i], LOW);
    digitalWrite(data_in[i], LOW);
    digitalWrite(data_out[i], LOW);
  }
}

void loop() {
  if(Serial.available())
  {
    String str = Serial.readString();
    char* token = strtok((char*)(str.c_str()), " ");
    unsigned int arg1 = 0, arg2 = 0;

    if(!strcmp(token, "r") || !strcmp(token, "w"))
    {
      if(!strcmp(token, "r"))
      {
        arg1 = atoi(strtok(NULL, " "));
        Serial.println("Reading from address " + String(arg1));
        unsigned char data = readBits(arg1);
        Serial.println("Read data: " + String(data));
      }
      else if(!strcmp(token, "w"))
      {
        arg1 = atoi(strtok(NULL, " "));
        arg2 = atoi(strtok(NULL, " "));
        Serial.println("Writing " + String(arg2) + " to address " + String(arg1));
        writeBits(arg1, arg2);
      }
    }
    else
    {
      Serial.println("Not a valid command.");
    }
  }
}

void sendAddress(unsigned int address){
  for(int i = 0; i < WORD_SIZE; i++)
  {
    if(address & (1 << i))
      digitalWrite(address_out[i], HIGH);
    else
      digitalWrite(address_out[i], LOW);
  }
}

void sendData(unsigned char data){
  for(int i = 0; i < WORD_SIZE; i++)
  {
    if(data & (1 << i))
      digitalWrite(data_in[i], HIGH);
    else
      digitalWrite(data_in[i], LOW);
  }
}

unsigned char readBits(unsigned int address){
  sendAddress(address);
  digitalWrite(clk, HIGH);
  delay(100);
  digitalWrite(clk, LOW);

  unsigned char data = 0;
  for(int i = 0; i < WORD_SIZE; i++)
  {
    data |= (digitalRead(data_out[i]) << i);
  }
  return data;
}

void writeBits(unsigned int address, unsigned char data){
  sendAddress(address);
  sendData(data);
  digitalWrite(we, HIGH);
  digitalWrite(clk, HIGH);
  delay(100);
  digitalWrite(clk, LOW);
  digitalWrite(we, LOW);
}
