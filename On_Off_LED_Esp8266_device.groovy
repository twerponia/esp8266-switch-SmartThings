/**
 *  ESP8266 Simple On/Off Switch
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */

 // Simple device handler metadata, preferences, and tiles
metadata {
	definition (name: "On/Off ESPSwitch", namespace: "twerponia", author: "Marianne Breinig") {
		capability "Actuator"
		capability "Switch"
		capability "Sensor"
	}

	// Simulator metadata
	simulator {

	}
    
    // Preferences
	preferences {
		input "ip", "text", title: "IP Address", description: "ip", required: true, displayDuringSetup: true
		input "port", "text", title: "Port", description: "port", required: true, displayDuringSetup: true
		input "mac", "text", title: "MAC Addr", description: "mac", required: true, displayDuringSetup: true
	}
	// UI tile definitions
	tiles {
		standardTile("switch", "device.switch", width: 2, height: 2) {
			state "on", label: '${name}', action: "switch.off", icon: "st.switches.switch.on", backgroundColor: "#79b821"
			state "off", label: '${name}', action: "switch.on", icon: "st.switches.switch.off", backgroundColor: "#ffffff"
		}
		
		main (["switch"])
		details (["switch"])
	}
}

// parse responses from ESP8266 about the state of the switch
// this reponse is in the form of a json string
def parse(String description) {
//log.debug "Parsing '${description}'"
	def msg = parseLanMessage(description)
	def headerString = msg.header

	def result = []
	
	def bodyString = msg.body
    def value = "";
	if (bodyString) {
	///log.debug "BodyString: $bodyString"
        def json = msg.json;
        if( json?.name == "switch") {
        	value = json.state == 1 ? "on" : "off"
            //log.debug "switch state ${value}"
			result << createEvent(name: "switch", value: value)
        }	
    }
    result
}

private getHostAddress() {
    def ip = settings.ip
    def port = settings.port
	log.debug "Using ip: ${ip} and port: ${port} for device: ${device.id}"
    return ip + ":" + port
}

def sendEsp(message) {
	//log.debug "Executing 'sendEsp' ${message}"
	//post the on or off command to the ESP swithch by just appending it to the path
	new physicalgraph.device.HubAction(
    	method: "POST",
    	path: "/${message}?",
    	headers: [ HOST: "${getHostAddress()}" ]
	)
}

// Commands sent to the device
def on() {
	log.debug "Sending 'on'"
	sendEsp("on")
}

def off() {
	log.debug "Sending 'off'"
	sendEsp("off")
}

def configure() {
	log.debug "Executing 'configure'"
    if(device.deviceNetworkId!=settings.mac) {
    	log.debug "setting device network id"
    	device.deviceNetworkId = settings.mac
    }
}