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
	public:
		Encoder(const int pinA, const int pinB,const int PPR, const float sampleTime);
		void initialize();
		long getPulses();
		void setPulses(long pulses_);
		void count1();
		void count2();
		void update();
		float getSpeed();

	};
#endif