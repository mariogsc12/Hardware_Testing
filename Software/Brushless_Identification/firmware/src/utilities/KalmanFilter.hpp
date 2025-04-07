#ifndef KALMANFILTER_HPP
#define KALMANFILTER_HPP

class KalmanFilter {
public:
    KalmanFilter(float q_angle = 0.001, float q_bias = 0.003, float r_measure = 0.03);

    float update(float acc_angle, float gyro_rate, float dt);

private:
    float Q_angle;
    float Q_bias;
    float R_measure;

    float bias;
    float angle;
    float P[2][2];
};

#endif
