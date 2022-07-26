class PidRegSpeed
{
public:
    PidRegSpeed(int time,int pos);
    // ~PidRegSpeed();

    void set_kp();
    void set_ki();
    void set_kd();

    int update_pid(int time, int _pos, int setpoint);
    void calc_error(float pos);

private:
    int _time,_pos;
    float _prevErr,_error,_pid_I,_pid_D;
    float kp,ki,kd {0.01f};

    inline float constrain(float x, float a, float b){
    if ((x>a)&&(x<b)) return x;
    return (x<a)?a:b;
    }
};
