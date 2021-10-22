#include "../include/nmpc.h"
#include <math.h>
#include <numeric>
#include <ros/ros.h>
#include <fstream>

using namespace std;
using namespace ros;

vector<double> CalcTetaVW(double Vx, double aX, double Vy, double aY){
    //double tetaRef_ = atan(Vy/Vx) * (180/PI);
    double Vref_ = sqrt(pow(Vx, 2)+pow(Vy, 2));
    double Wref_ = ((Vx*aY)-(Vy*aX))/(pow(Vx, 2)+pow(Vy, 2));

    vector<double> p = {Vref_, Wref_};
    return p;
}

void loopControl(vector<int> xref, vector<int> yref, int* Vx, int* Vy, vector<int> aX, vector<int> aY){

    Trajectory traj;
    traj.v_ref = 0;
    traj.w_ref = 0;
    Rate loop_rate(0.8);
    vector<double> VW;
    NMPC nmpc = NMPC();
    Publisher velPub = nmpc.node_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

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

        VW = CalcTetaVW(Vx[i], aX[i], Vy[i], aY[i]);

        traj.v_ref = VW[0];
        traj.w_ref = VW[1];

        // Xref = xref[i] ???
        // Yref = yref[i] ???
        cout << endl;
    }



}

int main(int argc, char** argv){

	vector<int> x_pecorrido;
    vector<int> y_pecorrido;
  
    ros::init(argc, argv, "control_teste");
    NodeHandle no; // apagar?

    ifstream file;
    file.open("src/robot_control/mapas/coords.txt");
    string n;
    vector<int> xref;
    vector<int> yref;
    int i = 0, num;
    while(getline(file, n)){
        if(i == 0){
            num = atoi(n.c_str());
        }
        else if(i <= num){
            xref.push_back(atoi(n.c_str()));
        }
        else{
            yref.push_back(atoi(n.c_str()));
        }
        i++;
    }
    // cout << xref.size() << endl << yref.size() << endl;

    int auxVx[num];
    int auxVy[num];
    adjacent_difference(xref.begin(), xref.end(), auxVx);
    adjacent_difference(yref.begin(), yref.end(), auxVy);
    int Vx[num-1];
    int Vy[num-1];
    copy(auxVx + 1, auxVx + num, Vx);
    copy(auxVy + 1, auxVy + num, Vy);
    
    int auxaX[num-1];
    int auxaY[num-1];
    adjacent_difference(Vx, Vx + num - 1, auxaX);
    adjacent_difference(Vy, Vy + num - 1, auxaY);
    vector<int> aX (auxaX + 1, auxaX + num - 1);
    vector<int> aY (auxaY + 1, auxaY + num - 1);

    // cout << xref.size() << endl;
    // cout << Vx[0] << endl;
    // cout << aX.size() << endl;

    cout << "########## COMECO DA LOCOMOCAO ############" << endl;
    
    loopControl(xref, yref, Vx, Vy, aX, aY);
	return 0;
}

