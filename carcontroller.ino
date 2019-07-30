// This #include statement was automatically added by the Particle IDE.
#include "SensorUltrasound.h"

// This #include statement was automatically added by the Particle IDE.
#include "Car.h"

CarController Car( A4, A3, A0, A1);
UltraSoundSensor Sensor(D3, D6);

unsigned long int lastTime;
int periodMillis = 200;

void setup() {
    
    Car.Init();
    Sensor.Init();
    
    Particle.function("setDirection", pChangeDir);
    Particle.function("setMode", pSetMode);
    Particle.function("SensorTest", pSensorTest);
    Particle.function("Speed", pSetSpeed);
}


void loop() {
    unsigned long elapsed;
    Car.Move();
    
    if( Sensor.Measure() < 10.0f){
        Particle.publish("motion-detected", PUBLIC);
        pSetMode("simple");
    }
        
        
    elapsed = millis() - lastTime;
    if ( elapsed < periodMillis )
        delay(periodMillis - elapsed);
}

int pChangeDir(String cmd){
    return Car.setDirection(cmd);
}

int pSetMode(String cmd){
    if( cmd == "route"){
        return Car.setModeRoute();
    }else if(cmd=="simple"){
        Car.setDirection("none");
        return Car.setModeSimple();
    }else{
        Car.setDirection("none");
        return Car.setModeSimple();
    }
}

int pSensorTest(String cmd){
    if( cmd == "dist" ){
        return int(Sensor.Measure());
    }
    return -1;
}

int pSetSpeed(String cmd){
    int value;
    value = cmd.toInt();
    //return value;
    if(value > 0 && value < 255){
        return Car.setMaxSpeed(value);
    }
    return -1;
}
int pSetSpeed(String cmd){
    int value;
    value = cmd.toInt();
    //return value;
    if(value > 0 && value < 255){
        return Car.setMaxSpeed(value);
    }
    return -1;
}