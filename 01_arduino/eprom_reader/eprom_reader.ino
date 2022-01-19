//Arduino's latched 87c257 eprom reader

#include <ArduinoJson.h>

const uint16_t eprom_adress_max = 32767;
uint16_t adress_max;
uint16_t adress_min ;
uint8_t eprom_data;
bool reading_failure = false;
bool eprom_read = false;
bool serial_validation = true;
uint8_t json_command = 0;
uint16_t json_adress_min ;
uint16_t json_adress_max;
char json[82];

StaticJsonDocument<96> json_message;

void setup() {
  Serial.begin(9600);
  DDRA = 255; //output adress port declaration lsb 1111111 A7>A0
  DDRC = 127; //output adress port declaration msb 0111111 A14>A8
  DDRK = 7; //output command port declaration 0000111 A10 A09 A08 > AS E G
  DDRL = 0; //input data port configuration Q7>Q0
  PORTK = 3; //command port configuration 111 !AS !E !G
  reader_reinit();
}

void loop() {
  serial_command();
}
