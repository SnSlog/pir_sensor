const char PAGE_WiFi_Conf[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>WiFi configuration</title>
	<link href="style.css" rel="stylesheet" type="text/css">
	<script src="microajax.js" type="text/javascript"></script>
	<script type="text/javascript">
		function GetState(){setValues("/new_networks");}
    function LoadInfo(){setValues("/wifi_state");}
		function selssid(value){document.getElementById("ssid").value=value;}
		window.onload=function(){setTimeout(LoadInfo,2000);setTimeout(GetState,3000);}
	</script>
</head><body>
<div class="block1">
	<div class="div_prt"><form action="wifi_config.html" method="get">
		<table class="prt_box">
			<tr><td colspan="2" class="td_head"><strong>WiFi connection settings</strong></td></tr>
			<tr>
				<td class="td_css">SSID:</td> 
				<td class="inp_txt"><input class="inp_str" type="text" id="ssid" name="ssid" value=""></td>
			</tr>
			<tr>
				<td class="td_css">Password:</td>
				<td class="inp_txt"><input class="inp_str" type="text" id="password" name="password" value=""></td>
			</tr>
			<tr>
				<td class="td_css">DHCP:</td>
				<td class="ch_box"><input type="checkbox" id="dhcp" name="dhcp" value=""></td>
			</tr>
			<tr>
				<td class="td_css">IP:</td>
				<td class="ch_box"><input type="text" id="ip_0" name="ip_0" size="1">.<input type="text" id="ip_1" name="ip_1" size="1">.<input type="text" id="ip_2" name="ip_2" size="1">.<input type="text" id="ip_3" name="ip_3" value="" size="1"></td>
			</tr>
			<tr>
				<td class="td_css">Netmask:</td>
				<td class="ch_box"><input type="text" id="nm_0" name="nm_0" size="1">.<input type="text" id="nm_1" name="nm_1" size="1">.<input type="text" id="nm_2" name="nm_2" size="1">.<input type="text" id="nm_3" name="nm_3" size="1"></td>
			</tr>
			<tr>
				<td class="td_css">Gateway:</td>
				<td class="ch_box"><input type="text" id="gw_0" name="gw_0" size="1">.<input type="text" id="gw_1" name="gw_1" size="1">.<input type="text" id="gw_2" name="gw_2" size="1">.<input type="text" id="gw_3" name="gw_3" size="1"></td>
			</tr>
			<tr>
				<td class="td_css">DNS:</td>
				<td class="ch_box"><input type="text" id="dns_0" name="dns_0" size="1">.<input type="text" id="dns_1" name="dns_1" size="1">.<input type="text" id="dns_2" name="dns_2" size="1">.<input type="text" id="dns_3" name="dns_3" size="1"></td>
			</tr>
		</table>
		<div class="div_prt">
			<div class="btn_tb"><input type="submit" class="btn" name="Save" value="Save"></div>
		</div>
	</form></div>
	<div class="div_prt"><strong>Connection State to WiFi</strong><div id="connectionstate">N/A</div></div>
	<div class="div_prt"><table class="prt_box">
			<tr><td><strong>Avaliable networks</strong></td></tr>
			<tr><td><div id="networks">Scanning...</div></td></tr>
			<tr><td class="btn_tb"><div class="btn">
				<form action="javascript:GetState()">
					<input type="submit" class="btn" name="new_networks" value="Refresh">
				</form>
			</div></td></tr>
	</table></div>
	<div class="div_prt">
		<div class="btn_tb"><form action="mqtt_config.html" method="get">
			<input type="submit" class="btn" name="next_mqtt" value="Next ->>">
		</form></div>
	</div>
</div>
</body></html>
)=====";

const char PAGE_MQTT_Conf[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>MQTT server configuration</title>
	<link href="style.css" rel="stylesheet" type="text/css">
	<script src="microajax.js" type="text/javascript"></script>
	<script type="text/javascript">
    function GetState(){setValues("/mqtt_connection");}
    function LoadInfo(){setValues("/mqtt_state");}
		window.onload=function(){setTimeout(LoadInfo,2000);setTimeout(GetState,3000);}
	</script>
</head><body>
<div class="block1">
	<div><form action="mqtt_config.html" method="get">
		<table class="main_tbl">
			<tr><td><table class="prt_box">
				<tr><td colspan="2" class="td_head"><strong>MQTT server</strong></td></tr>
				<tr>
					<td class="td_css">Server:</td>    
					<td class="inp_txt"><input class="inp_str" type="text" id="MQTT_name" name="MQTT_name" value=""></td>
				</tr>
				<tr>
					<td class="td_css">Login:</td> 
					<td class="inp_txt"><input class="inp_str" type="text" id="MQTT_login" name="MQTT_login" value=""></td>
				</tr>
				<tr>
					<td class="td_css">Password:</td> 
					<td class="inp_txt"><input class="inp_str" type="text" id="MQTT_pass" name="MQTT_pass" value=""></td>
				</tr>
				<tr>
					<td class="td_css">Port:</td> 
					<td class="inp_txt"><input class="inp_str" type="text" id="MQTT_port" name="MQTT_port" value=""></td>
				</tr>
       <tr>
         <td class="td_css">Sending interval:</td>
          <td class="inp_txt"><input class="inp_str" type="text" id="MQTT_interval" name="MQTT_interval" value=""></td>
        </tr>
				<tr>
					<td class="td_css">SSL:</td>
					<td class="ch_box"><input type="checkbox" id="ssl" name="ssl"></td>
				</tr>
			</table></td></tr>
		</table>
		<div class="div_prt">
			<div class="btn_tb"><input type="submit" class="btn" name="Save" value="Save"></div>
		</div>
	</form></div>
	<div class="div_prt"><strong>Connection State to MQTT Server</strong><div id="connectionstate">N/A</div></div>
	<div class="div_prt">
		<div class="btn_tb"><form action="wifi_config.html" method="get">
			<input type="submit" class="btn" name="back_wifi" value="<<- Back">
		</form></div>
		<div class="btn_tb"><form action="sensor_config.html" method="get">
			<input type="submit" class="btn" name="next_sns" value="Next ->>">
		</form></div>
	</div>
</div>
</body></html>
)=====";

const char PAGE_Sensor_Conf[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Sensors configuration</title>
	<link href="style.css" rel="stylesheet" type="text/css">
	<script src="microajax.js" type="text/javascript"></script>
  <script type="text/javascript">
    function LoadInfo(){setValues("/sensor_state");}
    window.onload=function(){setTimeout(LoadInfo,2000);}
  </script>
</head><body>
<div class="block1">
	<div class="div_prt"><form action="sensor_config.html" method="get">
		<table class="prt_box">
			<tr><td colspan="3" class="td_head"><strong>Sensor settings</strong></td></tr>
			<tr>
				<td class="td_css">Time:</td> 
				<td class="ch_box"><input type="checkbox" id="ts" name="ts" value=""></td>
				<td class="inp_txt"><input class="inp_str" type="text" id="time_topic" name="time_topic" value=""></td>
			</tr>
			<tr>
				<td class="td_css">Power:</td>
				<td class="ch_box"><input type="checkbox" id="pwr" name="pwr" value=""></td>
				<td class="inp_txt"><input class="inp_str" type="text" id="pwr_topic" name="pwr_topic" value=""></td>
			</tr>
			<tr>
				<td class="td_css">Motion Sensor:</td>
				<td class="ch_box"><input type="checkbox" id="pir" name="pir" value=""></td>
				<td class="inp_txt"><input class="msns_str" type="text" id="pir_topic" name="pir_topic" value=""></td>
			</tr>
			<tr>
				<td class="td_css">Reed switch:</td>
				<td class="ch_box"><input type="checkbox" id="sw" name="sw" value=""></td>
				<td class="inp_txt"><input class="inp_str" type="text" id="sw_topic" name="sw_topic" value=""></td>
			</tr>
			<tr>
				<td class="td_css">External Output:</td>
				<td class="ch_box"><input type="checkbox" id="ext" name="ext" value=""></td>
				<td class="inp_txt"><input class="inp_str" type="text" id="ext_topic" name="ext_topic" value=""></td>
			</tr>
			<tr>
				<td class="td_css">LED:</td>
				<td class="ch_box"><input type="checkbox" id="led" name="led" value=""></td>
				<td class="inp_txt"><input class="inp_str" type="text" id="led_topic" name="led_topic" value=""></td>
			</tr>
			<tr>
				<td class="td_css">Beepear:</td>
				<td class="ch_box"><input type="checkbox" id="bpr" name="bpr" value=""></td>
				<td class="inp_txt"><input class="inp_str" type="text" id="bpr_topic" name="bpr_topic" value=""></td>
			</tr>
		</table>
		<div class="div_prt">
			<div class="btn_tb"><input type="submit" class="btn" name="Save" value="Save"></div>
		</div>
	</form></div>
	<div class="div_prt">
		<div class="btn_tb"><form action="mqtt_config.html" method="get">
			<input type="submit" class="btn" name="back_mqtt" value="<<- Back">
		</form></div>
		<div class="btn_tb"><form action="switch_off.html" method="get">
			<input type="submit" class="btn" name="sw_off" value="Switch off">
		</form></div>
	</div>
</div>
</body></html>
)=====";

const char PAGE_Switch_OFF[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Switch off</title>
	<link href="style.css" rel="stylesheet" type="text/css">
</head><body>
<div class="block1">
	<div class="div_prt">
		<p>Access point is switching off.</p>
		<p>You can switch it on again by pressed and hold RST button on 3 sec.</p>
		<p>Please, visit <a href="http://snslog.ru"><strong>SnSLog.ru</strong></a> for more information.</p>
	</div>
</div>
</body></html>
)=====";

const char PAGE_WaitAndReload_wifi[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv = "refresh" content = "3;URL=/wifi_config.html">
<title>Update</title>
</head>
<body>
<p>Please wait while saving configuration...</p>
</body>
</html>
)=====";

const char PAGE_WaitAndReload_mqtt[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv = "refresh" content = "3;URL=/mqtt_config.html">
<title>Update</title>
</head>
<body>
<p>Please wait while saving configuration...</p>
</body>
</html>
)=====";

const char PAGE_WaitAndReload_sensor[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv = "refresh" content = "3;URL=/sensor_config.html">
<title>Update</title>
</head>
<body>
<p>Please wait while saving configuration...</p>
</body>
</html>
)=====";

const char PAGE_Style_css[] PROGMEM = R"=====(
body{color: #000000; font-family: verdana,helvetica,arial,sans-serif; font-size: 12px; text-align: center;}
.block1{position: relative; float: none; margin: 0 auto; width: 400px; background: #dee0e2; border-radius: 20px;}
.main_tbl{width: 100%; border-spacing: 2px 7px;}
.prt_box{width: 100%; border: 1px solid grey; background: #ffffff; border-radius: 20px; padding: 2px; border-spacing: 4px;}
.td_head{text-align: center; border-bottom: 2px solid grey; padding-bottom: 5px;}
.td_css{width: 30%; text-align: right;}
.inp_txt{text-align: left;}
.inp_str{width: 95%;}
.ch_box{text-align: left;}
.btn_tb{text-align: center; display: inline-block; margin: 4px;}
.div_prt{padding: 4px;}
.nw{text-align: left;}
.btn, .btn:link, .btn:visited{width: 120px; height: 30px; border-radius: 20px; border: 1px solid #001F3F; background-color: #0074D9; font-weight: bold; text-decoration: none; text-transform: uppercase; color: #ffffff; text-align: center; display: inline-block;}
.btn:hover, .btn:focus{color: #7FDBFF; border: 1px solid #7FDBFF; background: #52A8E8;}
.btn:active{color: #0063aa; border: 1px solid #42d1f4; background: #2D7CD1;}
)=====";

const char PAGE_microajax_js[] PROGMEM = R"=====(
function microAjax (B, A){
this.bindFunction=function(E,D){return function(){return E.apply(D,[D])}};
this.stateChange=function (D){if(this.request.readyState==4){this.callbackFunction(this.request.responseText)}};
this.getRequest=function(){if(window.ActiveXObject){return new ActiveXObject("Microsoft.XMLHTTP")}else{if(window.XMLHttpRequest){return new XMLHttpRequest()}}return false};
this.postBody=(arguments[2]||"");
this.callbackFunction=A;
this.url=B;
this.request = this.getRequest ();
if(this.request){var C = this.request;C.onreadystatechange=this.bindFunction(this.stateChange,this);
if(this.postBody!==""){C.open("POST",B,true);C.setRequestHeader("X-Requested-With","XMLHttpRequest");C.setRequestHeader("Content-type","application/x-www-form-urlencoded");C.setRequestHeader("Connection","close")}else{C.open("GET",B,true)}
C.send(this.postBody)}};
function setValues(url){microAjax(url,function(res){res.split(String.fromCharCode(10)).forEach(function(entry){fields=entry.split("|");if(fields[2]=="input"){document.getElementById(fields[0]).value=fields[1];}else if(fields[2]=="div"){document.getElementById(fields[0]).innerHTML=fields[1];}else if(fields[2]=="chk"){document.getElementById(fields[0]).checked=fields[1];}});});}
)=====";
