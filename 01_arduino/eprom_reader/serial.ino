//---------------------------------------------------------------------------------------------------------------

void serial_command()
{
  //create a buffer, it will save the serial char in an array before json deserialization
  static char buffer[82];
  static unsigned char index = 0;
  char inch;

  //while loop read the json message string
  while (Serial.available() > 0) {
    inch = Serial.read();
    if (inch == '}') {
      buffer[index++] = inch;
      buffer[index] = 0;
      for (int i = 0; i < 82; i++)
      {
        //transfert buffer to json array
        json[i] = buffer[i];
      }
      
      //clear buffer
      buffer[0] = 0;
      index = 0;

      //deserialization validation
      serial_validation = true;

    } else {
      if (index < 81) {
        buffer[index++] = inch;
        buffer[index] = 0;
      }
    }
  }

  if (serial_validation)
  {
    serial_validation = false;
    
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(json_message, json);

    // Test if parsing succeeds. If an error exist, the reader will be in status n°3 and will be reinit
    if (error)
    {
      //      Serial.print(F("deserializeJson() failed: "));
      //      Serial.print(error.f_str());
      json_message["status"] = 3; // status n°3 = deserialisation error
      serializeJson(json_message, Serial);
      delay(2000);
      reader_reinit();
    }
    else
    {
      // Fetch values.
      json_command = json_message["command"];
      json_adress_min = json_message["adress_min"];
      json_adress_max = json_message["adress_max"];
      serializeJson(json_message, Serial);

      //execute command
      switch (json_command)
      {
        case 0:
          // re-init
          reader_reinit();
          break;
        case 1:
          // total reading
          reading_cycle(0, eprom_adress_max);
          break;
        case 2:
          // partial reading with adress min and max
          reading_cycle(json_adress_min, json_adress_max);
          break;
        default:
          break;
      }
    }
    // send the status after the executed command
    serializeJson(json_message, Serial);
  }
}

//---------------------------------------------------------------------------------------------------------------
