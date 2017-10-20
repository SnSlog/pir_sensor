// Check the Values is between 0-255
boolean checkRange (String Value) {
	if (Value.toInt () < 0 || Value.toInt () > 255) { return false; }
	else { return true; }
}

// Check the Values is between 0-65535
boolean checkRange_2byte (String Value) {
  if (Value.toInt () < 0 || Value.toInt () > 65535) { return false; }
  else { return true; }
}

//Check the Values is between -12...+12
boolean checkRange_timezone (String Value) {
  if (Value.toInt () < -72 || Value.toInt () > 72) { return false; }
  else { return true; }
}

// Check the Values is between 1...24
boolean checkRange_upd_time (String Value) {
  if (Value.toInt () < 0 || Value.toInt () > 24) { return false; }
  else { return true; }
}

// convert a single hex digit character to its integer value (from https://code.google.com/p/avr-netino/)
unsigned char h2int (char c) {
  if (c >= '0' && c <= '9') { return ((unsigned char) c - '0'); }
  if (c >= 'a' && c <= 'f') { return ((unsigned char) c - 'a' + 10); }
  if (c >= 'A' && c <= 'F') { return ((unsigned char) c - 'A' + 10); }
  return(0);
}

//(based on https://code.google.com/p/avr-netino/)
String urldecode (String input) {
  char c;
  String ret = "";
  for (byte t = 0; t < input.length (); t++) {
    c = input [t];
    if (c == '+') c = ' ';
    if (c == '%') {
      t++;
      c = input [t];
      t++;
      c = (h2int (c) << 4) | h2int (input [t]);
    }
    ret.concat(c);
  }
  return ret;
}

// SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
void wifi_conf_html (AsyncWebServerRequest *request) {
	if (request->args () > 0 ) { //Save Settings
    if (request->argName (0) == "back_wifi") {
       request->send_P (200, "text/html", PAGE_WiFi_Conf);
    } else {
      config_dev.dhcp = false;
  		for ( uint8_t i = 0; i < request->args (); i++ ) {
  			if (request->argName (i) == "ssid") config_dev.ssid = urldecode (request->arg (i));
  			if (request->argName (i) == "password") config_dev.password = urldecode (request->arg (i));
  			if (request->argName (i) == "ip_0") if (checkRange (request->arg (i))) config_dev.IP[0] = request->arg (i).toInt ();
  			if (request->argName (i) == "ip_1") if (checkRange (request->arg (i))) config_dev.IP[1] = request->arg (i).toInt ();
  			if (request->argName (i) == "ip_2") if (checkRange (request->arg (i))) config_dev.IP[2] = request->arg (i).toInt ();
  			if (request->argName (i) == "ip_3") if (checkRange (request->arg (i))) config_dev.IP[3] = request->arg (i).toInt ();
  			if (request->argName (i) == "nm_0") if (checkRange (request->arg (i))) config_dev.Netmask[0] = request->arg (i).toInt ();
  			if (request->argName (i) == "nm_1") if (checkRange (request->arg (i))) config_dev.Netmask[1] = request->arg (i).toInt ();
  			if (request->argName (i) == "nm_2") if (checkRange (request->arg (i))) config_dev.Netmask[2] = request->arg (i).toInt ();
  			if (request->argName (i) == "nm_3") if (checkRange (request->arg (i))) config_dev.Netmask[3] = request->arg (i).toInt ();
  			if (request->argName (i) == "gw_0") if (checkRange (request->arg (i))) config_dev.Gateway[0] = request->arg (i).toInt ();
  			if (request->argName (i) == "gw_1") if (checkRange (request->arg (i))) config_dev.Gateway[1] = request->arg (i).toInt ();
  			if (request->argName (i) == "gw_2") if (checkRange (request->arg (i))) config_dev.Gateway[2] = request->arg (i).toInt ();
  			if (request->argName (i) == "gw_3") if (checkRange (request->arg (i))) config_dev.Gateway[3] = request->arg (i).toInt ();
        if (request->argName (i) == "dns_0") if (checkRange (request->arg (i))) config_dev.DNS[0] = request->arg (i).toInt ();
        if (request->argName (i) == "dns_1") if (checkRange (request->arg (i))) config_dev.DNS[1] = request->arg (i).toInt ();
        if (request->argName (i) == "dns_2") if (checkRange (request->arg (i))) config_dev.DNS[2] = request->arg (i).toInt ();
        if (request->argName (i) == "dns_3") if (checkRange (request->arg (i))) config_dev.DNS[3] = request->arg (i).toInt ();
   			if (request->argName (i) == "dhcp") config_dev.dhcp = true;
      }
      request->send_P (200, "text/html", PAGE_WaitAndReload_wifi);
      save_cfg = true;
      wifi_cfg = true;
	  } 
	} else {
    request->send_P (200, "text/html", PAGE_WiFi_Conf);
	}
	Serial.println (__FUNCTION__); 
}

// SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
void mqtt_conf_html (AsyncWebServerRequest *request) {
  if (request->args () > 0 ) { //Save Settings
    if (request->argName (0) == "next_mqtt") {
      request->send_P (200, "text/html", PAGE_MQTT_Conf);
    } else if (request->argName (0) == "back_mqtt") {
      request->send_P (200, "text/html", PAGE_MQTT_Conf);
    } else {
      config_dev.SSL = false;
      for ( uint8_t i = 0; i < request->args (); i++ ) {
        if (request->argName (i) == "MQTT_name") config_dev.MQTT_server = urldecode (request->arg (i));
        if (request->argName (i) == "MQTT_login") config_dev.MQTT_login = urldecode (request->arg (i));
        if (request->argName (i) == "MQTT_pass") config_dev.MQTT_password = urldecode (request->arg (i));
        if (request->argName (i) == "MQTT_port") if (checkRange_2byte (request->arg (i))) config_dev.MQTT_port = request->arg (i).toInt ();
        if (request->argName (i) == "MQTT_interval")  if (checkRange_2byte (request->arg (i))) config_dev.MQTT_interval = request->arg (i).toInt ();
        if (request->argName (i) == "ssl") config_dev.SSL = true;
      }
      request->send_P (200, "text/html", PAGE_WaitAndReload_mqtt);
      save_cfg = true;
      connect_mqtt = true;
    }
  } else {
    request->send_P (200, "text/html", PAGE_MQTT_Conf);
  }
  Serial.println (__FUNCTION__); 
}

// SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
void sensor_conf_html (AsyncWebServerRequest *request) {
  if (request->args () > 0 ) { //Save Settings
    if (request->argName (0) == "next_sns") {
      request->send_P (200, "text/html", PAGE_Sensor_Conf);
    } else {
      config_dev.timestamp = false;
      config_dev.ADC_EN = false;
      config_dev.D0_EN = false;
      config_dev.D1_EN = false;
      config_dev.D4_EN = false;
      config_dev.D6_EN = false;
      config_dev.D8_EN = false;
      for ( uint8_t i = 0; i < request->args (); i++ ) {
        if (request->argName (i) == "time_topic") config_dev.time_topic = urldecode (request->arg (i));
        if (request->argName (i) == "pwr_topic") config_dev.ADC_topic = urldecode (request->arg (i));
        if (request->argName (i) == "pir_topic") config_dev.D1_topic = urldecode (request->arg (i));
        if (request->argName (i) == "sw_topic") config_dev.D6_topic = urldecode (request->arg (i));
        if (request->argName (i) == "ext_topic") config_dev.D8_topic = urldecode (request->arg (i));
        if (request->argName (i) == "led_topic") config_dev.D4_topic = urldecode (request->arg (i));
        if (request->argName (i) == "bpr_topic") config_dev.D0_topic = urldecode (request->arg (i));
        if (request->argName (i) == "ts") config_dev.timestamp = true;
        if (request->argName (i) == "pwr") config_dev.ADC_EN = true;
        if (request->argName (i) == "pir") config_dev.D1_EN = true;
        if (request->argName (i) == "sw") config_dev.D6_EN = true;
        if (request->argName (i) == "ext") config_dev.D8_EN = true;
        if (request->argName (i) == "led") config_dev.D4_EN = true;
        if (request->argName (i) == "bpr") config_dev.D0_EN = true;
       }
      request->send_P (200, "text/html", PAGE_WaitAndReload_sensor);
      save_cfg = true;
      pin_cfg = true;
      
    }
  } else {
    request->send_P (200, "text/html", PAGE_Sensor_Conf);
  }
  Serial.println (__FUNCTION__);
}

// FILL THE PAGE WITH VALUES
void send_wifi_conf_values_html (AsyncWebServerRequest *request) {
	String values = "";
	values += "ssid|" + config_dev.ssid + "|input\n";
	values += "password|" + config_dev.password + "|input\n";
  if (config_dev.dhcp) {values += "dhcp|checked|chk\n";}
  else {values += "dhcp||chk\n";}
  values += "ip_0|" + (String) config_dev.IP[0] + "|input\n";
	values += "ip_1|" + (String) config_dev.IP[1] + "|input\n";
	values += "ip_2|" + (String) config_dev.IP[2] + "|input\n";
	values += "ip_3|" + (String) config_dev.IP[3] + "|input\n";
	values += "nm_0|" + (String) config_dev.Netmask[0] + "|input\n";
	values += "nm_1|" + (String) config_dev.Netmask[1] + "|input\n";
	values += "nm_2|" + (String) config_dev.Netmask[2] + "|input\n";
	values += "nm_3|" + (String) config_dev.Netmask[3] + "|input\n";
	values += "gw_0|" + (String) config_dev.Gateway[0] + "|input\n";
	values += "gw_1|" + (String) config_dev.Gateway[1] + "|input\n";
	values += "gw_2|" + (String) config_dev.Gateway[2] + "|input\n";
	values += "gw_3|" + (String) config_dev.Gateway[3] + "|input\n";
  values += "dns_0|" + (String) config_dev.DNS[0] + "|input\n";
  values += "dns_1|" + (String) config_dev.DNS[1] + "|input\n";
  values += "dns_2|" + (String) config_dev.DNS[2] + "|input\n";
  values += "dns_3|" + (String) config_dev.DNS[3] + "|input\n";
  request->send (200, "text/plain", values);
	Serial.println(__FUNCTION__); 
}

// FILL THE PAGE WITH VALUES
void send_mqtt_state_html (AsyncWebServerRequest *request) {
  String values = "";
  values += "MQTT_name|" + config_dev.MQTT_server + "|input\n";
  values += "MQTT_login|" + config_dev.MQTT_login + "|input\n";
  values += "MQTT_pass|" + config_dev.MQTT_password + "|input\n";
  values += "MQTT_port|" + (String) config_dev.MQTT_port + "|input\n";
  values += "MQTT_interval|" + (String) config_dev.MQTT_interval + "|input\n";
  if (config_dev.SSL) {values += "ssl|checked|chk\n";}
  else {values += "ssl||chk\n";}
  request->send (200, "text/plain", values);
  Serial.println(__FUNCTION__); 
}

// FILL THE PAGE WITH VALUES
void send_sensor_state_html (AsyncWebServerRequest *request) {
  String values = "";
  if (config_dev.timestamp) {values += "ts|checked|chk\n";}
  else {values += "ts||chk\n";}
  values += "time_topic|" + config_dev.time_topic + "|input\n";
  if (config_dev.ADC_EN) {values += "pwr|checked|chk\n";}
  else {values += "pwr||chk\n";}
  values += "pwr_topic|" + config_dev.ADC_topic + "|input\n";
  if (config_dev.D1_EN) {values += "pir|checked|chk\n";}
  else {values += "pir||chk\n";}
  values += "pir_topic|" + config_dev.D1_topic + "|input\n";
  if (config_dev.D6_EN) {values += "sw|checked|chk\n";}
  else {values += "sw||chk\n";}
  values += "sw_topic|" + config_dev.D6_topic + "|input\n";
  if (config_dev.D8_EN) {values += "ext|checked|chk\n";}
  else {values += "ext||chk\n";}
  values += "ext_topic|" + config_dev.D8_topic + "|input\n";
  if (config_dev.D4_EN) {values += "led|checked|chk\n";}
  else {values += "led||chk\n";}
  values += "led_topic|" + config_dev.D4_topic + "|input\n";
  if (config_dev.D0_EN) {values += "bpr|checked|chk\n";}
  else {values += "bpr||chk\n";}
  values += "bpr_topic|" + config_dev.D0_topic + "|input\n";
  request->send (200, "text/plain", values);
  Serial.println(__FUNCTION__); 
}

// FILL THE PAGE WITH NETWORKSTATE & NETWORKS
void send_new_networks_html (AsyncWebServerRequest *request) {
	String state = "N/A";
	String Networks = "";
  int stat = WiFi.status ();
	if (stat == 0) {state = "Idle"; wifi_cfg = true;}
  	else if (stat == 1) state = "NO SSID AVAILBLE";
  	else if (stat == 2) state = "SCAN COMPLETED";
  	else if (stat == 3) state = "CONNECTED";
  	else if (stat == 4) {state = "CONNECT FAILED"; wifi_cfg = true;}
  	else if (stat == 5) {state = "CONNECTION LOST"; wifi_cfg = true;}
  	else if (stat == 6) {state = "DISCONNECTED"; wifi_cfg = true;}
  int n = WiFi.scanComplete ();
  if ((n == -1) or (n == -2)) {
    WiFi.scanNetworks (true);
    Networks = "Scan not complete, please refresh later.";
  }	else if (n == 0) {
		Networks = "<font color='#FF0000'>No networks found!</font>";
    WiFi.scanNetworks (true);
	} else {
		Networks = "Found " + String(n) + " Networks<br>";
		Networks += "<table border='0' width='100%'>";
		Networks += "<tr bgcolor='#DDDDDD'><td><strong>Name</strong></td><td><strong>Quality</strong></td><td><strong>Enc</strong></td><tr>";
		for (int i = 0; i < n; ++i) {
			int quality = 0;
			if (WiFi.RSSI (i) <= -100) {quality = 0;}
			else if (WiFi.RSSI (i) >= -50) {quality = 100;}
			else {quality = 2 * (WiFi.RSSI (i) + 100);}
			Networks += "<tr><td class='nw'><a href='javascript:selssid (\"" + String (WiFi.SSID (i)) + "\")'>"  +  String (WiFi.SSID (i)) + "</a></td><td>" + String (quality) + "%</td><td>" + String ((WiFi.encryptionType (i) == ENC_TYPE_NONE)?" ":"*") + "</td></tr>";
		}
		Networks += "</table>";
    WiFi.scanDelete ();
    if (WiFi.scanComplete () == -2) {
      WiFi.scanNetworks (true);
    }
	}
	String values = "";
	values += "connectionstate|" + state + "|div\n";
	values += "networks|" + Networks + "|div\n";
  request->send (200, "text/plain", values);
	Serial.println (__FUNCTION__);
}

// FILL THE PAGE WITH NETWORKSTATE & NETWORKS
void send_mqtt_connection_html (AsyncWebServerRequest *request) {
  String state = "N/A";
  if (mqtt_status) state = "CONNECTED";
  else state = "DISCONNECTED";
  String values = "";
  values += "connectionstate|" + state + "|div\n";
  request->send (200, "text/plain", values);
  Serial.println (__FUNCTION__);
}
