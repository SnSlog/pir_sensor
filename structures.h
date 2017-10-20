#define ACCESS_POINT_NAME "SnSLog_pir"
#define ACCESS_POINT_PASSWORD "mqtt_device" //should be more than 8 characters

#define AP_MODE 2
#define STA_MODE 1
#define OFF_MODE 0

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D6 12
#define D8 15

#define DELAY2SEND 10 //delay seconds between sends data
long delay2send = DELAY2SEND;

IPAddress ServerIP (192, 168, 10, 1);
IPAddress ServerGW (192, 168, 10, 1);
IPAddress ServerSN (255, 255, 255, 0);

WiFiClientSecure secure_client;
WiFiClient WF_client;
PubSubClient mqtt_client;

uint8_t MAC [6];
byte wifi_status = OFF_MODE;
boolean wifi_conf = false;
boolean server_status = false;
boolean save_cfg = false;
boolean pin_cfg = false;
boolean wifi_cfg = false;
boolean connect_mqtt = false;
boolean mqtt_status = false;
boolean send_mqtt_data = false;
boolean b_check_tick = false;   //checking connection to the wifi


int ADC_data = 0; 
boolean pir = false;  //pir-sensor
boolean ext = false;  //external output
boolean sw = false; //reed swith
unsigned long UnixTimestamp = 0;

struct strConfig {
  boolean AdminEnabled; //1 byte
  boolean dhcp; //1 byte
  boolean SSL; //1 byte  
  boolean timestamp; //1 byte
  boolean ADC_EN; //1 byte
  boolean D0_EN; //1 byte
  boolean D1_EN; //1 byte
  boolean D4_EN; //1 byte
  boolean D6_EN; //1 byte
  boolean D8_EN; //1 byte
  long MQTT_port; //4 bytes
  long MQTT_interval; // 4 byte
  byte IP [4]; //4 bytes
  byte Netmask [4]; //4 bytes
  byte Gateway [4]; //4 bytes
  byte DNS [4]; //4 bytes
  String ssid; //24 bytes
  String password; //24 bytes  
  String DeviceName; //24 bytes
  String MQTT_server; //24 bytes
  String MQTT_login; //24 bytes
  String MQTT_password; //24 bytes
  String time_topic; //16 bytes
  String ADC_topic; //16 bytes
  String D0_topic; //16 bytes
  String D1_topic; //16 bytes
  String D4_topic; //16 bytes
  String D6_topic; //16 bytes
  String D8_topic; //16 bytes
};

strConfig config_dev;

