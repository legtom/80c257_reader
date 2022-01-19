//---------------------------------------------------------------------------------------------------------------

void reading_cycle(uint16_t eprom_adress_start, uint16_t eprom_adress_stop)
{
  //eprom reading status false before to start the reading
  eprom_read = false;
  volatile uint16_t eprom_adress = 0;

  //checking if the adresses are in the eprom adresses
  if (eprom_adress_start < eprom_adress_stop && eprom_adress_stop <= eprom_adress_max)
  {
    volatile uint16_t eprom_adress = eprom_adress_start;
    eprom_read = true;
    json_message["status"] = 1;
    while (eprom_adress <= eprom_adress_stop)
    {
      //new byte reading cycle init
      PORTK = 7; //command port configuration 111 AS !E !G
      delayMicroseconds(1);

      //setting eprom adress
      PORTA = lowByte(eprom_adress); //adress port configuration lsb 1111111 A7>A0
      PORTC = highByte(eprom_adress); //adress port configuration msb 0111111 A14>A8
      delayMicroseconds(1);

      //adress strobe
      PORTK = 3; //command port configuration 011 AS !E !G
      delayMicroseconds(1);

      //chip enable
      PORTK = 1; //command port configuration 001 AS E !G
      delayMicroseconds(1);

      //output enable
      PORTK = 0; //command port configuration 000 AS E G
      delayMicroseconds(1);

      //reading byte at eprom_adress
      eprom_data = PINL; //data port reading Q7>Q0
      delayMicroseconds(1);

      //output and chip disable
      PORTK = 3; //command port configuration 011 AS !E !G
      delayMicroseconds(1);

      //serialize and send json_message
      json_message["adress"] = eprom_adress;
      json_message["data"]   = eprom_data;
      serializeJson(json_message, Serial);

      //eprom_adress incrimente for next cycle
      eprom_adress++;
    }

    //end of the reading
    json_message["status"] = 2;
  }
  else
  {
    //stop reading and set the failure byte
    json_message["status"] = 4;
  }
}

//---------------------------------------------------------------------------------------------------------------

void reader_reinit()
{
  json_command = json_message["command"] = 0;
  json_adress_min = json_message["adress_min"] = 0;
  json_adress_max = json_message["adress_max"] = 0;
  json_message["status"] = 0;
  json_message["adress"] = 0;
  json_message["data"]   = 0;
  eprom_read = false;
  reading_failure = false;
  serial_validation = false;
}

//---------------------------------------------------------------------------------------------------------------
