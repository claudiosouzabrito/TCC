#ifndef __NMPCSETTINGS_H__
#define __NMPCSETTINGS_H__

//Model
#define VMAX 0.4
#define d_Rob 0.2236

//Controller
#define N1 1
#define N2 10
#define NU 2

//Controller Weights
#define L1 800
#define L2 500
#define L3 0.05

//RPROP
#define JSTOP 0.05
#define IMAX 15
#define DELTA 0.1
#define ETA_M 0.5
#define ETA_P 1.2
#define STEP_MAX 0.1
#define STEP_MIN 0.000001
#define CURR_STEP 0.1

//Others
#define SIM_TIME_STEP 0.01
#define BFC 1
#define DVAL 0

#endif 