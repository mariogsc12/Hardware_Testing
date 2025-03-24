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
		//float angle;
		const float PPR;
		int lastTime;
		int currentTime;
	public:
		Encoder(const int pinA, const int pinB);
		void initialize();
		long getPulses();
		void setPulses(long pulses_);
		void count1();
		void count2();
		void update();
		float getSpeed();

	};
#endif