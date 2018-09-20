void Eeprom_read()
{ 
  EE_ind = 0;
  EEPROM.get(EE_ind, modalita);
  
  EE_ind += sizeof(modalita);
  EEPROM.get(EE_ind, d_focus);
  
  EE_ind += sizeof(d_focus);
  EEPROM.get(EE_ind, d_shoot);
  
  EE_ind += sizeof(d_shoot);
  EEPROM.get(EE_ind, d_laser);
  
  EE_ind += sizeof(d_laser);
  EEPROM.get(EE_ind, d_audio);

  Serial.println("Eeprom read");
}

void Eeprom_save()
{
  EE_ind = 0;
  EEPROM.put(EE_ind, modalita);//scrive valore su eeprom solo se viene modificato
 
  EE_ind += sizeof(modalita);
  EEPROM.put(EE_ind, d_focus);
  
  EE_ind += sizeof(d_focus);
  EEPROM.put(EE_ind, d_shoot);
  
  EE_ind += sizeof(d_shoot);
  EEPROM.put(EE_ind, d_laser);
  
  EE_ind += sizeof(d_laser);
  EEPROM.put(EE_ind, d_audio);

  EEPROM.commit();

  //Serial.println("Eeprom save");

}
