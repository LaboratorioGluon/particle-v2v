
#include "SensorUltrasound.h"
#include "Arduino.h"

UltraSoundSensor::UltraSoundSensor(int trigger, int echo):
    triggerPin(trigger),
    echoPin(echo){
        
}

void UltraSoundSensor::Init(){
    
    pinMode(triggerPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    
    digitalWrite(triggerPin,LOW); 
}

float UltraSoundSensor::Measure(){
    digitalWrite(triggerPin,LOW);
    delayMicroseconds(5);
    digitalWrite(triggerPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(triggerPin,LOW);
    echotime = pulseIn(echoPin, HIGH);  
    Serial1.println(echotime);
    digitalWrite(triggerPin, LOW); 
    return 0.01715f*echotime; 
    
}