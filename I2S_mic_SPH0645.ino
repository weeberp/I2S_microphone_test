#include "Arduino.h"
#include <I2S.h>

#define THRESHOLD 60000

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	// start I2S at 16 kHz with 32-bits per sample
	I2S.begin(I2S_PHILIPS_MODE, 16000, 32);
}

#define SAMPLES 128 // make it a power of two for best DMA performance

void loop()
{
	// read a bunch of samples:
	int samples[SAMPLES];

	for (int i = 0; i < SAMPLES; i++)
	{
		int sample = 0;
		while ((sample == 0) || (sample == -1))
		{
			sample = I2S.read();
		}
		// convert to 18 bit signed
		sample >>= 14;
		samples[i] = sample;
	}

	// get the mean (avg)
	float meanval = 0;
	for (int i = 0; i < SAMPLES; i++)
	{
		meanval += samples[i];
	}
	meanval /= SAMPLES;

	// subtract it from all samples to get a 'normalized' output
	for (int i = 0; i < SAMPLES; i++)
	{
		samples[i] -= meanval;
	}

	// find the 'peak to peak' max
	float maxsample, minsample, amplitude;
	minsample = 100000;
	maxsample = -100000;
	for (int i = 0; i < SAMPLES; i++)
	{
		minsample = min(minsample, samples[i]);
		maxsample = max(maxsample, samples[i]);
	}

	amplitude = maxsample - minsample;

	delayMicroseconds(1000);

	if (amplitude > THRESHOLD)
	{
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else
	{
		digitalWrite(LED_BUILTIN, LOW);
	}

}
