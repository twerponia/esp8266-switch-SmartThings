# esp8266-switch-SmartThings
I wanted to write a simple SmartThings device handler for a ESP8266 NodeMCU based switch.  I am not a developer and when I look at the many code examples available, I often have trouble figuring what the essential part the code are.

So I tried to write the most basic handler, that can turn on the LED  on the EPS8266 NodeMCU using the Smartthings App on my phone and therefore also Amazon Echo.  I mostly used code from Charles Schwer (cannot find anymore) and Daniel Ogorchock (https://github.com/DanielOgorchock/ST_Anything)  as a guide.

My SmartThings hub and ESP8266 NodeMCU have manually assigned fixed IP addresses.  I assigned then in the router.
The portion of the Arduino code that turns on/off the LED can be modified to torn on/off any other Arduino controlled switch.
