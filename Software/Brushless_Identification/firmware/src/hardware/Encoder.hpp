// Inspired by https://github.com/LuSeKa/EncoderNano/tree/master

#ifndef ENCODER_HPP
#define ENCODER_HPP

class Encoder
{
	private:
        const int Pin_A;
        const int Pin_B;
		volatile long pulses;
		float speed;
		float sample_time;
		const float PPR;
		unsigned long lastTime;
		unsigned long currentTime;
		float filtered_speed;
		float x[3] = {0, 0, 0};  // Historial de velocidades medidas
		float y[3] = {0, 0, 0};  // Historial de salidas filtradas
		const float b[3] = {0.02008337, 0.04016673, 0.02008337};
		const float a[2] = {1.56101808, -0.64135154};
	public:
		Encoder(const int pinA, const int pinB,const int PPR, const float sampleTime);
		void initialize();
		long getPulses();
		void setPulses(long pulses_);
		void count1();
		void count2();
		void update();
		float getSpeed();
		float getFilteredSpeed();
	};
#endif