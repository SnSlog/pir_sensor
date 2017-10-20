Ticker D3_delay;
Ticker send_delay;
Ticker second_tick;

void update_time (void) {
  UnixTimestamp++;
}

void Send_Data (void) {
  send_mqtt_data = true;
  if (config_dev.ADC_EN) {
    ADC_data = analogRead (A0);
    Serial.println ("ADC data: " + (String)ADC_data);
  }
}

void D3_pressed (void) {
  D3_delay.detach ();
  if (digitalRead (D3) == 0) {
    if (!config_dev.AdminEnabled) {
      config_dev.AdminEnabled = true;
      save_cfg = true;
      Serial.println("AdminEnabled=true");
    }
    wifi_conf = true;
    Serial.println ("Start WiFi Access Point");
  } else {
    Serial.println ("RST button relesed");
    pin_cfg = true;
  }
}

void rst_btn (void) {
  detachInterrupt (D3);
  D3_delay.once (3, D3_pressed); //3 seconds wait
  Serial.println ("RST button pressed");
}

void D1_intr (void) {                     
  static unsigned long D1_millis_prev;
  Serial.println ("D1");
  if(millis()-10 > D1_millis_prev) {
    D1_millis_prev = millis();
    if (digitalRead (D1) == HIGH) pir = true;
    else pir = false;
    Serial.println ("PIR-sensor: " + (String)pir);
    send_mqtt_data = true;
    }
  }
  
void D6_intr (void) {                     
  static unsigned long D6_millis_prev;
  Serial.println ("D6");
  if(millis()-205 > D6_millis_prev) {
    D6_millis_prev = millis();
    if (digitalRead (D6) == HIGH) sw = true;
    else sw = false;
    Serial.println ("Photoresistor: " + (String)sw);
    send_mqtt_data = true;
    }
  }

