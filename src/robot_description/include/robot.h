#ifndef __ROBOT_H__
#define __ROBOT_H__


#include "NMPCSettings.h"

struct TRobotStateSim{
    public:
        double x;
        double y;
        double teta;

        double v;
        double w;
};

struct TTargetStateSim{
    double x;
    double y;
    double vx;
    double vy;
};

class MyRobot{
    public:
        MyRobot(): rob_num(1), x_rob(0), y_rob(0), teta_rob(0), v_rob(0), w_rob(0) {}
        MyRobot(int rob_num, double x_rob, double y_rob, double teta_rob, double v_rob, double w_rob): rob_num(rob_num), x_rob(x_rob), y_rob(y_rob), teta_rob(teta_rob), v_rob(v_rob), w_rob(w_rob) {}

        int rob_num;

        double x_rob;
        double y_rob;
        double teta_rob;
        double v_rob;
        double w_rob;

};


#endif