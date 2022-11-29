#include "pid.h"
#include "macros.h"

#define KP              (2)
#define KI              (1000)
#define KD              (0)
#define MAX             (10000)
#define MIN             (-MAX)
#define SAMPLE_TIME     (1)
void PIDController_Init(PIDController *pid) {
        
        pid->Kp = KP;
        pid->Ki = KI;
        pid->Kd = KD;
        pid->limMax = MAX;
        pid->limMin = MIN;
        pid->T = SAMPLE_TIME;
        
	/* Clear controller variables */
	pid->integrator = 0;
	pid->prevError  = 0;

	pid->differentiator  = 0;
	pid->prevMeasurement = 0;

	pid->out = 0;

}

int PIDController_Update(PIDController *pid, int setpoint, int measurement) {

	/*
	* Error signal
	*/
    int error = setpoint - measurement;


	/*
	* Proportional
	*/
    int proportional = pid->Kp * error;


	/*
	* Integral
	*/
    pid->integrator = pid->integrator + pid->Ki * pid->T * (error + pid->prevError);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->limMaxInt) {

        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {

        pid->integrator = pid->limMinInt;

    }


	/*
	* Derivative (band-limited differentiator)
	*/
		
//    pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
//                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
//                        / (2.0f * pid->tau + pid->T);


	/*
	* Compute output and apply limits
	*/
    pid->out = proportional + pid->integrator; //+ pid->differentiator;

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	/* Store error and measurement for later use */
    pid->prevError       = error;
    pid->prevMeasurement = measurement;

	/* Return controller output */
    return pid->out;

}
