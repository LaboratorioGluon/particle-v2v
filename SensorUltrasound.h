#ifndef __SENSOR_ULTRASOUND_H__
#define __SENSOR_ULTRASOUND_H__

class UltraSoundSensor{
private:

    int triggerPin;
    int echoPin;
    
    // Last measured time
    unsigned long echotime; 
    
public:
    UltraSoundSensor(int trigger, int echo);
    ~UltraSoundSensor(){};
    
    /**
     * @function Init
     *
     * Function that shall be called in setup()
     */
    void Init();
    
    /**
     * @function Measure
     *
     * When this function is called, a measured is started, and the program blocks until it is ready.
     */
    float Measure();
};

#endif