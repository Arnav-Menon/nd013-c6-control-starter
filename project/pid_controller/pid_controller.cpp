/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
   _kp = Kpi;
   _ki = Kii;
   _kd = Kdi;
   _output_lim_max = output_lim_maxi;
   _output_lim_min = output_lim_mini; 
   _p_error = 0.0;
   _i_error = 0.0;
   _d_error = 0.0;
   _delta_time = 0.0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
   if (_delta_time > 0.0) {
      _d_error = (cte - _p_error) / _delta_time;
   }
   else {
      _d_error = 0.0;
   }

   _p_error = cte;
   _i_error += (cte * _delta_time);
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control;
   control = (_kp * _p_error) + (_ki * _i_error) + (_kd * _d_error);

   if (control > _output_lim_max) {
      control = _output_lim_max;
   }
   else if (control < _output_lim_min) {
      control = _output_lim_min;
   }

   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
   _delta_time = new_delta_time;
   return _delta_time;
}