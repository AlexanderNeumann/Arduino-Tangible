#include "Tangible.h"



Tangible::Tangible(int rx, int tx, int l)
{
  if (NULL != tangibleSerial)
    {
        delete tangibleSerial;
    }
  tangibleSerial = new SoftwareSerial(rx, tx);
  tangibleSerial->begin(19200);
	lightsensorThreshold = l;
	currentTime=0;
	old_time=0;
	onTable=false;
	lightsensor=-1;
	ACSR =
		(0 << ACD) |    // Analog Comparator: Enabled
		(0 << ACBG) |   // Analog Comparator Bandgap Select: AIN0 is applied to the positive input
		(0 << ACO) |    // Analog Comparator Output: Off
		(1 << ACI) |    // Analog Comparator Interrupt Flag: Clear Pending Interrupt
		(1 << ACIE) |   // Analog Comparator Interrupt: Enabled
		(0 << ACIC) |   // Analog Comparator Input Capture: Disabled
		(1 << ACIS1) | (1 << ACIS0);   // Analog Comparator Interrupt Mode: Comparator Interrupt on Rising Output Edge
}

void Tangible::update(){
	currentTime = millis();
	if(currentTime-old_time>150&&onTable==true){
		onTable=false;
		tangibleSerial->print("0#0");
	}
	int sensorValue = analogRead(A0);
	sensorValue = sensorValue >lightsensorThreshold ? 1 : 0;
	if (sensorValue != lightsensor && onTable){
		char tmp[15];
		sprintf(tmp, "%d", onTable);
		strcpy(msg,tmp);
		strcat(msg,"#");
		sprintf(tmp, "%d", sensorValue);
		strcat(msg,tmp);
		tangibleSerial->println(msg);
		lightsensor = sensorValue;
	}		
}

void Tangible::checkTable(){
	if(currentTime-old_time>150&&!onTable){  
	    old_time = currentTime;
	    onTable=true;
	    tangibleSerial->print("1#0");
	  }
	 old_time = currentTime;
}
