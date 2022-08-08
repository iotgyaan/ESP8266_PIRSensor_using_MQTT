# PIR_Sensor_LED_MQTT
Led ON and OFF using PIR Sensor with MQTT using ESP8266.


-------> Install nodejs and node-red <--------

STEP 1
1. Install Node.js

STEP 2
EMQX MQTT Broker
1. Download zip from here --> https://www.emqx.com/en/downloads/broker?osType=Linux

2. Unzip the file
unzip emqx-4.4.1-otp23.0-windows-amd64.zip

3. Start emqx
.\bin\emqx start

4. Check if emqx is running
.\bin\emqx_ctl status
.\bin\emqx ping

5. Stop emqx
.\bin\emqx stop

STEP 3
Node-RED
Windows CMD:

node --version && npm --version
npm install -g --unsafe-perm node-red
node-red
