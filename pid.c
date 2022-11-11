#include "pid.h"
#include "macros.h"

#define KP              (20.0f)
#define KI              (0)
#define KD              (0)
#define MAX             (30000)
#define MIN             (-MAX)
#define SAMPLE_TIME     (0.1)
void PIDController_Init(PIDController *pid) {
        
        pid->Kp = KP;
        pid->Ki = KI;
        pid->Kd = KD;
        pid->limMax = MAX;
        pid->limMin = MIN;
        pid->T = SAMPLE_TIME;
        
	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->prevError  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prevMeasurement = 0.0f;

	pid->out = 0.0f;

}

float PIDController_Update(PIDController *pid, float setpoint, float measurement) {

	/*
	* Error signal
	*/
    float error = setpoint - measurement;


	/*
	* Proportional
	*/
    float proportional = pid->Kp * error;


	/*
	* Integral
	*/
    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

	/* Anti-wind-up via integrator clamping */
//    if (pid->integrator > pid->limMaxInt) {
//
//        pid->integrator = pid->limMaxInt;
//
//    } else if (pid->integrator < pid->limMinInt) {
//
//        pid->integrator = pid->limMinInt;
//
//    }


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
void pid_control(){
  //Want to update pid loop and set output
  float Motor_offset = PIDController_Update(&pid,0.0f,measurment());
  set_left_speed(BASE_SPEED+(unsigned int)Motor_offset);
  set_right_speed(BASE_SPEED-(unsigned int)Motor_offset);
  
}