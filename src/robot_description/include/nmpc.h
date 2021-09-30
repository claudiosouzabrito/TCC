

#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Twist.h"
//#include "sensor_msgs/Image.h"
//#include "sensor_msgs/PointCloud2.h"
//#include "sensor_msgs/LaserScan.h"
#include <string>
#include "ekf.h"
#include "robot.h"
#include "astar.h"

using std::vector;
using std::string;
using namespace Eigen;
using namespace std;


class Vout{
    public:
        Vout(): v_out(0), w_out(0) {}
        Vout(double v_out, double w_out): v_out(v_out), w_out(w_out) {}

        double v_out;
        double w_out;

};

class NMPC{
    private:
        ros::NodeHandle node_;
        ros::Subscriber ekf_estim;
        ros::Subscriber Rob_vel;
        
        double DiffAngle(double a1, double a2);
        int mysign(double x);
        double CostFunction(TRobotStateSim Robot, TTargetStateSim Target, Matrix2d& Ut);
        Matrix<double,2,8> calcUSteps(Matrix2d& Ud);
        Matrix2d saturate(Matrix2d& u);

    //    ros::Subscriber vision;
    
    public:
        NMPC(){
            //subscreve valores do EKF
            ekf_estim = node_.subscribe("/mycode/odom_combined", 1, &NMPC::OdomCallback, this);

            //subscreve valores de velocidade do robo
            Rob_vel = node_.subscribe("/odom", 1, &NMPC::VelCallback, this);
            
            //vision = node_.subscribe("/camera/rgb/image_raw",10, &NMPC::ImageCallback,this);
        }
        ~NMPC(){}

        Vout velocity;    
        MyRobot iRobot;

        Vout NMPController(MyRobot iRobot, Trajectory Traj);
         
        void OdomCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);

        void VelCallback(const nav_msgs::Odometry::ConstPtr& vel);
        
        //void ImageCallback(const sensor_msgs::Image img)
        
};

