
#include "Car.h"
#include "Arduino.h"

CarController::CarController(int right_pin1, int right_pin2, int left_pin1, int left_pin2){
    pins[SIDE::RIGHT][0] = right_pin1;
    pins[SIDE::RIGHT][1] = right_pin2;
    
    pins[SIDE::LEFT][0] = left_pin1;
    pins[SIDE::LEFT][1] = left_pin2;
    
    modo = MODE::SIMPLE;
    currDirection = DIRECTION::NONE;
    maxSpeed = 125;
    
    wp_list[0] = { 500, "fwd"};
    wp_list[1] = { 700, "left"};
    wp_list[2] = { 500, "fwd"};
    wp_list[3] = { 700, "left"};
    wp_list[4] = { 500, "fwd"};
    wp_list[5] = { 700, "left"};
    wp_list[6] = { 500, "fwd"};
    wp_list[7] = { 700, "left"};
    wp_list_num = 8;
}

void CarController::Init(){
    // Set pin mode output
    pinMode(pins[SIDE::RIGHT][0], OUTPUT);
    pinMode(pins[SIDE::RIGHT][1], OUTPUT);
    
    pinMode(pins[SIDE::LEFT][0] , OUTPUT);
    pinMode(pins[SIDE::LEFT][1] , OUTPUT);
}

void CarController::Move(){
    if(modo == MODE::SIMPLE){
        RawMove();
    }else if( modo == MODE::ROUTE){
        RouteMode();
        RawMove();
    }
}
void CarController::RawMove(){
    switch(currDirection){
        case DIRECTION::FWD:
            setMotor(SIDE::RIGHT,  maxSpeed);
            setMotor(SIDE::LEFT ,  maxSpeed);
        break;
        case DIRECTION::BCK:
            setMotor(SIDE::RIGHT, -maxSpeed);
            setMotor(SIDE::LEFT , -maxSpeed);
        break;
        case DIRECTION::RT:
            setMotor(SIDE::RIGHT, -maxSpeed);
            setMotor(SIDE::LEFT ,  maxSpeed);
        break;
        case DIRECTION::LF:
            setMotor(SIDE::RIGHT,  maxSpeed);
            setMotor(SIDE::LEFT , -maxSpeed);
        break;
        default:
            setMotor(SIDE::RIGHT, 0);
            setMotor(SIDE::LEFT, 0);
    }
}

void CarController::setMotor(enum SIDE side, int speed){
    int maxFreq = analogWriteMaxFrequency(pins[side][0]);
    // Check for limits. If they fail, stop the motor
    if( (speed > 255 || speed < -255) || speed == 0){
        digitalWrite(pins[side][1], LOW);
        digitalWrite(pins[side][0], LOW);
    }else{
        if (speed > 0 ){
            analogWrite(pins[side][0], speed, maxFreq / 2);
            analogWrite(pins[side][1], 0);
        }else{
            analogWrite(pins[side][0], 0);
            analogWrite(pins[side][1], -speed, maxFreq / 2);
        }
    }
    
}

int CarController::setDirection(String cmd){
    if( cmd == "fwd"){
        currDirection = DIRECTION::FWD;
        return 1;
    }else if( cmd == "bck"){
        currDirection = DIRECTION::BCK;
        return 2;
    }else if( cmd == "right"){
        currDirection = DIRECTION::RT;
        return 3;
    }else if( cmd == "left"){
        currDirection = DIRECTION::LF;
        return 4;
    }else if( cmd == "none"){
        currDirection = CarController::DIRECTION::NONE;
        return 5;
    }
}

void CarController::RouteMode(){
    static unsigned long routetimer = millis();
    static int step = 0;
    static int duraciones[] = {500,500,500,500,500,500,500,500};
    
    unsigned long tiempo = millis();
    
    setDirection(wp_list[step].order);
        
    
    if( (tiempo - routetimer) >= wp_list[step].duration){
        routetimer = millis();
        step++;
    }
        
    if( step >= wp_list_num)
        step = 0;
    
    
}