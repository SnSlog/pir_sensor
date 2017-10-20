void getIP (void) {
  IPAddress loc_IP, loc_SN, loc_GW;
  loc_IP = WiFi.localIP ();
  loc_SN = WiFi.subnetMask ();
  loc_GW = WiFi.gatewayIP ();
  for (int i = 0; i < 4; i++) {
    config_dev.IP[i] = loc_IP [i];
    config_dev.Netmask[i] = loc_SN[i];
    config_dev.Gateway[i] = loc_GW[i];
    config_dev.DNS[i] = loc_GW[i];
  }
}

void statusRequestWifi(void){
    if (WiFi.status() == WL_CONNECTED) {
       if (mqtt_status) {
          Serial.println ("s_Disconnected from MQTT server");
       }
       connect_mqtt = true;
    }else if (WiFi.status() != WL_CONNECTED) {
       Serial.println ("s_Disconnected from WiFi ");
       wifi_cfg = true;
    }
}

void ConfigureWifi (void) {
  int i = 0;
  //If connected to WiFi then try to disconnect
  if (WiFi.status () == WL_CONNECTED) {
    WiFi.disconnect ();
    Serial.print ("Disconnecting from Wifi");
    delay (1000);
    while ((WiFi.status() == WL_CONNECTED) and (i <= 20)) {
      Serial.print (".");
      delay (1000);
      i++;
    }
    Serial.println (".");
  }
  //Configure WiFi
  if (!config_dev.dhcp) {
    WiFi.config (IPAddress (config_dev.IP[0], config_dev.IP[1], config_dev.IP[2], config_dev.IP[3]), IPAddress (config_dev.DNS[0], config_dev.DNS[1], config_dev.DNS[2], config_dev.DNS[3]), IPAddress (config_dev.Gateway[0], config_dev.Gateway[1], config_dev.Gateway[2], config_dev.Gateway[3]), IPAddress (config_dev.Netmask[0], config_dev.Netmask[1], config_dev.Netmask[2], config_dev.Netmask[3]));
  }
  WiFi.begin (config_dev.ssid.c_str (), config_dev.password.c_str ());
  WiFi.setAutoConnect (false);
  WiFi.setAutoReconnect (true);
  Serial.print ("Connecting to Wifi");
  i = 0;
  //Start to connect to WiFi
  while ((WiFi.status() != WL_CONNECTED) and (i <= 20)) {
    Serial.print (".");
    delay (1000);
    i++;
  }
  Serial.println (".");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println ("Can not connect to WiFi");
    wifi_status = OFF_MODE;
  } else {
    Serial.println ("Successfully connected to WiFi");
    getIP ();
    connect_mqtt = true;
    check_tick.detach();
    b_check_tick = false;
  }
}

AsyncWebServer server(80); // Port of Webserver

void ConfigureServer (void) {
  server.on ("/", [](AsyncWebServerRequest *request) {wifi_conf_html (request);});
  server.on ("/wifi_config.html", [](AsyncWebServerRequest *request) {wifi_conf_html (request);});
  server.on ("/mqtt_config.html", [](AsyncWebServerRequest *request) {mqtt_conf_html (request);});
  server.on ("/sensor_config.html", [](AsyncWebServerRequest *request) {sensor_conf_html (request);});
  server.on ("/switch_off.html", [](AsyncWebServerRequest *request) {config_dev.AdminEnabled = false; pin_cfg = true; save_cfg = true; wifi_conf = true; request->send_P (200, "text/html", PAGE_Switch_OFF);});
  server.on ("/wifi_state", [](AsyncWebServerRequest *request) {send_wifi_conf_values_html (request);});
  server.on ("/mqtt_state", [](AsyncWebServerRequest *request) {send_mqtt_state_html (request);});
  server.on ("/sensor_state", [](AsyncWebServerRequest *request) {send_sensor_state_html (request);});
  server.on ("/new_networks", [](AsyncWebServerRequest *request) {send_new_networks_html (request);});
  server.on ("/mqtt_connection", [](AsyncWebServerRequest *request) {send_mqtt_connection_html (request);});
  server.on ("/style.css", [](AsyncWebServerRequest *request) {Serial.println ("style.css"); request->send_P (200, "text/css", PAGE_Style_css);});
  server.on ("/microajax.js", [](AsyncWebServerRequest *request) {Serial.println ("microajax.js"); request->send_P (200, "text/javascript", PAGE_microajax_js);});
  server.on ("/favicon.ico", [](AsyncWebServerRequest *request) {Serial.println("favicon.ico"); request->send (200, "text/plain", "");});
  server.onNotFound ([](AsyncWebServerRequest *request) {Serial.println ("Page Not Found"); request->redirect ("/");});
  server.begin ();
  server_status = true;
  Serial.println ("HTTP server started");
}

//get data from MQTT server
void MQTT_subscribe (char* topic, byte* payload, unsigned int length) {
  String payload_data;
  Serial.print ((String)topic + " => "); //output get topic
  for (int i = 0; i < length; i++) {
    payload_data += (char)payload[i];
  }
  Serial.println (payload_data); //output data
  if (String (topic) == config_dev.time_topic) { //check name of get topic
    if (config_dev.timestamp) {
      UnixTimestamp = payload_data.toInt ();
    }
  }
  else if (String (topic) == config_dev.D0_topic) {
    if (config_dev.D0_EN) {
      int bpr = payload_data.toInt (); //conver data string to integer
      digitalWrite (D0, bpr);  //control Beepear
    }
  }
  else if (String (topic) == config_dev.D4_topic) {
    if (config_dev.D4_EN) {
      int led = payload_data.toInt (); //conver data string to integer
      digitalWrite (D4, led);  //control LED
    }
  }
   else if (String (topic) == config_dev.D8_topic) {
    Serial.println ("ext"); //output data
    if (config_dev.D8_EN) {
      int ext = payload_data.toInt (); //conver data string to integer
      digitalWrite (D8, ext);  //control EXT
    }
  }
}

