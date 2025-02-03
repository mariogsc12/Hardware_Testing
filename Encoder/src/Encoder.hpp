// Inspired by https://github.com/LuSeKa/EncoderNano/tree/master

#ifndef ENCODER_HPP
#define ENCODER_HPP

class Encoder
{
	public:
		Encoder(const int pinA, const int pinB, const int PPR);
		long getPulses();
		void setPulses(long pulses_);
		void count1();
		void count2();
        int getPPR() const;
		
	private:
        const int Pin_A;
        const int Pin_B;
        const int Pulses_Per_Revolution;
		volatile long pulses;
	};
#endif