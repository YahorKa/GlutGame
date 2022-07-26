#include"PidRegSpeed.h"
#include <stdio.h>

PidRegSpeed::PidRegSpeed(int time,int pos) : _time(time), _pos(pos)
{
}

int PidRegSpeed::update_pid(int time, int _pos, int setpoint) {
    kp =1.1;//0.1;
    ki =0.3;//0.001; //0.0001;
    kd =0.1;//0.1;
    if (time == _time) return _prevErr;
    int _dt = (time -_time);
    _error = setpoint -_pos;
    _pid_I += constrain(_error*_dt*ki,-500,500);
    _pid_D = (_error-_prevErr)/_dt;
    _time = time;
    _prevErr = _error;
    return constrain(_error*kp+_pid_I+_pid_D*kd,-500,500);
}
