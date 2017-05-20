
# esp8266-switch-SmartThings
I wanted to write a simple SmartThings device handler for a ESP8266 NodeMCU based switch.  I am not a developer and when I look at the many code examples available, I often have trouble figuring what the essential part the code are.

So I tried to write the most basic handler, that can turn on the LED  on the EPS8266 NodeMCU using the Smartthings App on my phone and therefore also Amazon Echo.  I mostly used code from Charles Schwer (cannot find anymore) and Daniel Ogorchock (https://github.com/DanielOgorchock/ST_Anything)  as a guide.

My SmartThings hub and ESP8266 NodeMCU have manually assigned fixed IP addresses.  I assigned then in the router.
The portion of the Arduino code that turns on/off the LED can be modified to torn on/off any other Arduino controlled switch.

I only recently learned about node.js, because I wanted to write an Amazon Alexa skill, so that Alexa would tell me the temperature and humidity inside and outside of my house.
So to become more familiar with node.js, I tried to write a node.js server node-js server running on my computer, that  simulates the action of the SmartThings App and Hub for the ESP8266 NodeMCU smartswitch.
If you want to try it, download the folder nodeHubsimulator to your computer.  
In the file server.js change the line 
unirest.post('http://192.168.1.60:9070/on??')
to your ESP8288 NodeMCU iP address.

Upload the Arduino code smartswitch_ESP8266 to your NodeMCU.  For the hubIP use your computers local Ip address and for the hubPort use 3000.

Download the node.js runtime from https://nodejs.org/en/

Open a command prompt and navigate to the nodeHubsimulator folder on your computer.
For example, on a Windows system, put the folder on the desktop, and in the command prompt window type

cd C:\Users\your_user_name\Desktop\nodeHubsimulator

Install the necessary packages by typing in sequence

npm install express --save
npm install cors --save
npm install body-parser --save
npm install unirest --save

Then start the server.
node server.js

Open your browser and go to http://localhost:3000/

Click the buttons to turn the LED on and off.

