#include "../include/nmpc.h"
#include <math.h>
#include <numeric>
#include <ros/ros.h>

using namespace std;
using namespace ros;

double* CalcTetaVW(double Vx, double aX, double Vy, double aY){
    //double tetaRef_ = atan(Vy/Vx) * (180/PI);
    double Vref_ = sqrt(pow(Vx, 2)+pow(Vy, 2));
    double Wref_ = ((Vx*aY)-(Vy*aX))/(pow(Vx, 2)+pow(Vy, 2));

    double p[2] = {Vref_, Wref_};
    return p;
}

void loopControl(vector<int> xref, vector<int> yref, vector<int> Vx, vector<int> Vy, vector<int> aX,
                  vector<int> aY, vector<int> x_pecorrido, vector<int> y_pecorrido){

    Trajectory traj;
    NMPC nmpc = NMPC();
    Publisher velPub = nmpc.node_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    Rate loop_rate(0.8);
    double *VW;

    for(int i = 0; i < aX.size(); i++) {
        cout << endl;

        cout << i << endl;
        traj.x_ref = xref[i];
        traj.y_ref = yref[i];
        traj.vx_ref = Vx[i];
        traj.vy_ref = Vy[i];
        cout << "Xrefp = " << traj.x_ref << ", Yrefp = " << traj.y_ref << endl;
        cout << "iRobot.x = " << nmpc.iRobot.x_rob << ", iRobot.y = " << nmpc.iRobot.y_rob << endl;

        nmpc.velocity = nmpc.NMPController(nmpc.iRobot, traj);

        geometry_msgs::Twist msg;
        msg.linear.x = nmpc.velocity.v_out;
        msg.angular.z = nmpc.velocity.w_out;
        
        velPub.publish(msg);

        loop_rate.sleep();

        x_pecorrido.push_back(nmpc.iRobot.x_rob);
        y_pecorrido.push_back(nmpc.iRobot.y_rob);

        VW = CalcTetaVW(Vx[i], aX[i], Vy[i], aY[i]);
        traj.v_ref = VW[0];
        traj.w_ref = VW[1];

        // Xref = xref[i] ???
        // Yref = yref[i] ???
        cout << endl;
    }
}

int main(){

	vector<int> x_pecorrido;
  vector<int> y_pecorrido;
  
  //ros::init(argc, argv, "control teste");

	return 0;
}

