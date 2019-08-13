#ifndef __CAR_H__
#define __CAR_H__

#include "Arduino.h"



class CarController{
private:

    struct Waypoint{
        int duration;
        String order;
    };

    
    struct Waypoint wp_list[10];
    int wp_list_num;
    
    int maxSpeed;
    
    enum SIDE{ RIGHT = 0, LEFT};
    int pins[2][2];
    
    enum MODE{ SIMPLE = 0, ROUTE};
    enum MODE modo;
    
    
    enum DIRECTION{
        FWD = 0,
        BCK,
        RT,
        LF,
        CW, // Clockwise
        CCW, // Counter Clockwise
        NONE
    };
    
    // Store the current direction of movement.
    enum DIRECTION currDirection;
    
    /**
     * @function setMotor
     * 
     * @param side choose between right or left motor
     * @param speed (-255 .. 255)
     * 
     */
    void setMotor(enum SIDE side, int speed);
    
public:

    
    CarController(int right_pin1, int right_pin2, int left_pin1, int left_pin2);
    ~CarController(){};
    
    /**
     * @function Init
     *
     * Function that shall be called in setup()
     */
    void Init();
    
    /**
     * @function Move
     *
     * This function calls the correct movement function, it checks the current mode
     * and calls the correct function.
     *
     */
    void Move();
    
    /**
     * @function RawMove
     *
     * This function move the car in the 'currDirection' until it is demanded to stop.
     * This is called while in "SIMPLE" mode.
     *
     */
    void RawMove();
    
    /**
     * @function RouteMode
     *
     * This function move the car using the waypoint information.
     * This is called while in "ROUTE" mode.
     *
     */
     void RouteMode();
     
    
    int setDirection(String cmd);
    int getDirection(){ return (int)currDirection;}
    
    
    
    int setModeRoute(){ modo = MODE::ROUTE; return (int)modo;}
    int setModeSimple() { modo = MODE::SIMPLE;return (int)modo; }
    int setMaxSpeed(int m){ maxSpeed = m; return m;}
    int getMaxSpeed(){ return maxSpeed; }
    
};

#endif
