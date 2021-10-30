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

int* lerArquivo(string path, vector<double> xref, vector<double> yref){
    xref.clear();
    yref.clear();
    ifstream file;
    file.open(path);
    string n;
    int i = 0, num, MAP_X, MAP_Y;
    while(getline(file, n)){
        if(i == 0){
            MAP_X = atoi(n.c_str());
        }
        else if(i == 1){
            MAP_Y = atoi(n.c_str());
        }
        else if(i == 2){
            num = atoi(n.c_str());
        }
        else if(i <= num+2){
            xref.push_back(10.645*stod(n)/MAP_X);
        }
        else{
            yref.push_back(22.285*(MAP_Y - stod(n))/MAP_Y);
        }
        i++;
    }
    int result[3] = {num, MAP_X, MAP_Y};
    return result;
}

int main(int argc, char** argv){
  
    ros::init(argc, argv, "control_teste");
    NodeHandle no; // apagar?

    double mapx = 1064.5;
    double mapy = 2228.5;

    vector<double> xref;
    vector<double> yref;

    int num, MAP_X, MAP_Y;
    int *lerarquivo = lerArquivo("src/robot_control/mapas/coords.txt", xref, yref); 
    num = lerarquivo[0];
    MAP_X = lerarquivo[1];
    MAP_Y = lerarquivo[2];

    cout << xref.size() << endl 

    // ifstream file;
    // file.open("src/robot_control/mapas/coords1.txt");
    // string n;
    // int i = 0, num, MAP_X, MAP_Y;
    // while(getline(file, n)){
    //     if(i == 0){
    //         MAP_X = atoi(n.c_str());
    //     }
    //     else if(i == 1){
    //         MAP_Y = atoi(n.c_str());
    //     }
    //     else if(i == 2){
    //         num = atoi(n.c_str());
    //     }
    //     else if(i <= num+2){
    //         xref.push_back(10.645*stod(n)/MAP_X);
    //     }
    //     else{
    //         yref.push_back(22.285*(MAP_Y - stod(n))/MAP_Y);
    //     }
    //     i++;
    // }
    
    double Vx[num];
    double Vy[num];
    adjacent_difference(xref.begin(), xref.end(), Vx);
    adjacent_difference(yref.begin(), yref.end(), Vy);
    Vx[0] = 0;
    Vy[0] = 0;
    
    double acelX[num];
    double acelY[num];
    adjacent_difference(Vx, Vx + num, acelX);
    adjacent_difference(Vy, Vy + num, acelY);
    acelX[0] = 0;
    acelY[0] = 0;

    // for(int i = 0; i < xref.size(); i++){
    //     cout << yref[i] << " " << Vy[i] << " " << acelY[i] << endl;
    // }

    cout << "########## COMECO DA LOCOMOCAO ############" << endl;
    
    Trajectory traj;
    traj.v_ref = 0;
    traj.w_ref = 0;
    Rate loop_rate1(1);
    Rate loop_rate2(2);
    vector<double> VW = {0.0, 0.0};
    NMPC nmpc = NMPC();
    Publisher velPub = nmpc.node_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    for(int i = 0; i < xref.size(); i++) {
        spinOnce();
        cout << endl;

        cout << i << endl;
        traj.x_ref = xref[i];
        traj.y_ref = yref[i];
        traj.vx_ref = Vx[i];
        traj.vy_ref = Vy[i];

        VW = CalcTetaVW(Vx[i], acelX[i], Vy[i], acelY[i]);

        traj.v_ref = VW[0];
        traj.w_ref = VW[1];

        nmpc.velocity = nmpc.NMPController(nmpc.iRobot, traj);
        

        geometry_msgs::Twist msg;
        msg.linear.x = nmpc.velocity.v_out;
        msg.angular.z = nmpc.velocity.w_out;

        cout << "Querendo ir para X = " << traj.x_ref << ", Y = " << traj.y_ref << endl;
        cout << "iRobot.x = " << nmpc.iRobot.x_rob << ", iRobot.y = " << nmpc.iRobot.y_rob << endl;
        cout << "velo.linear.x = " << msg.linear.x << ", velo.angular.z = " << msg.angular.z << endl;
        
        velPub.publish(msg);

        loop_rate1.sleep();
        

        // while( abs(traj.y_ref - nmpc.iRobot.y_rob) >  0.1){
        //     spinOnce();

        //     VW = CalcTetaVW(Vx[i], acelX[i], Vy[i], acelY[i]);

        //     traj.v_ref = VW[0];
        //     traj.w_ref = VW[1];

        //     nmpc.velocity = nmpc.NMPController(nmpc.iRobot, traj);
            

        //     geometry_msgs::Twist msg;
        //     msg.linear.x = nmpc.velocity.v_out;
        //     msg.angular.z = nmpc.velocity.w_out;
        //     cout << "Querendo ir para X = " << traj.x_ref << ", Y = " << traj.y_ref << endl;
        //     cout << "iRobot.x = " << nmpc.iRobot.x_rob << ", iRobot.y = " << nmpc.iRobot.y_rob << endl;
        //     cout << "velo.linear.x = " << msg.linear.x << ", velo.angular.z = " << msg.angular.z << endl;
            
        //     velPub.publish(msg);

        //     loop_rate2.sleep();
        // }
        
        cout << "Chegou no ponto\n\n";
        

        // Xref = xref[i] ???
        // Yref = yref[i] ???
        cout << endl;
    }

    // while(1){
    //     spinOnce();
    //     VW = CalcTetaVW(0.05, 0.000001, 0.05, 0.000001);

    //     traj.v_ref = VW[0];
    //     traj.w_ref = VW[1];

    //     nmpc.velocity = nmpc.NMPController(nmpc.iRobot, traj);
        

    //     geometry_msgs::Twist msg;
    //     msg.linear.x = nmpc.velocity.v_out;
    //     msg.angular.z = nmpc.velocity.w_out;

    //     cout << "Querendo ir para X = " << traj.x_ref << ", Y = " << traj.y_ref << endl;
    //     cout << "iRobot.x = " << nmpc.iRobot.x_rob << ", iRobot.y = " << nmpc.iRobot.y_rob << endl;
    //     cout << "velo.linear.x = " << msg.linear.x << ", velo.angular.z = " << msg.angular.z << endl;
        
    //     velPub.publish(msg);

    //     loop_rate1.sleep();
    // }
    

	return 0;
}

