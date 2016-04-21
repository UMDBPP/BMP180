/*
 BMP180.h
 This is a simplified version of LowPowerLab's SFE_BMP180 pressure sensor library, meant for non programmers looking to make pressure sensors
 Written for the University of Maryland Balloon Payload Project

 Originally forked from BMP085 library by Mike Grusin at Sparkfun Electronics, then further forked from the SFE_BMP180 library by LowPowerLabs
 */

#ifndef BMP180_h
#define BMP180_h

#include <Arduino.h>
#include <Wire.h>

#define BMP180_ADDR 0x77 // 7-bit address

#define BMP180_REG_CONTROL 0xF4
#define BMP180_REG_RESULT 0xF6

#define BMP180_COMMAND_TEMPERATURE 0x2E
#define BMP180_COMMAND_PRESSURE0 0x34
#define BMP180_COMMAND_PRESSURE1 0x74
#define BMP180_COMMAND_PRESSURE2 0xB4
#define BMP180_COMMAND_PRESSURE3 0xF4

class BMP180
{
    public:
        char begin();
        double getTemperature();
        double getPressure();
        double getAltitude();
        String getMissionTimeString();
        void log(String message);
    private:
        char initialize();
        char startTemperature(void);
        char startPressure(char oversampling);
        char getTemperature(double &T);
        char getPressure(double &P, double &T);
        double getAltitude(double P, double P0);
        double sealevel(double P, double A);
        char getError(void);
        char readInt(char address, int &value);
        char readUInt(char address, unsigned int &value);
        char readBytes(unsigned char *values, char length);
        char writeBytes(unsigned char *values, char length);

        double temperature, altitude, pressure, baselinePressure;
        char status;
        int AC1, AC2, AC3, VB1, VB2, MB, MC, MD;
        unsigned int AC4, AC5, AC6;
        double c5, c6, mc, md, x0, x1, x2, y0, y1, y2, p0, p1, p2;
        char _error;
};

#endif
