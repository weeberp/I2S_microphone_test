# I2S Microphone Test

This is an test example showing how to read audio from an I2S microphone (Tested with SPH0645 and ICS-43432).

The signal amplitude is then compared to a defined threshold :

```
#define THRESHOLD 60000
```

If the audio amplitude exceeds the threshold, the LED_BUILTIN will light up.

Try claping your hands near the microphone.

# Tests

| Board        | Working | Not Tested | Not Working |
| ------------ | ------- | ---------- | ----------- |
| Feather M0   | x       |            |             |
| Feather 32u4 |         | x          |             |
| STM32L476    |         | x          |             |
| nRF52        |         |            | x           |

Feather M0 use SAMD 1.6.15 board package.
