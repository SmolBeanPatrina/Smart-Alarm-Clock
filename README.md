# Smart Alarm Clock

Have you ever set your alarm and woken up only to snooze it and fall right back asleep? Well, we have a solution for you! 
Our Smart Alarm Clock will make sure you wake up with a few adjustments to the traditional design. 
It includes a photoresistor which detects when your light has been turned on before deactivation. 
Additionally, we've included a feature that sends an email to your boss if your alarm hasn't been deactivated for an extended period of time. The fear of this feature activating is sure to wake you up!

## Tech Stack

### Hardware
- **BeagleBone Green**
- **8x8 matrix**
- **joystick**
- **USB Audio Adapter**
- **headphone/speaker**
- **photoresistor**

### Software
- **C**

### System Dependencies
- **usbutils**
- **i2c-tools**
- **alsa-utils**

### Development Libraries
- **libasound2-dev**

### Email Utilities
- **postfix**
- **mailutils**
- **ssmtp**
- **msmtp**
- **msmtp-mta**

## How It Works

1. Use the joystick to control the menu on your computer's terminal to set the alarm.
2. The program waits until the time matches your designated alarm time.
3. It plays a jingle and waits for the photoresistor to detect a high frequency.
4. If it doesn't detect for a long period of time, it will send an email using postfix.

## Additional Information

This project was completed in ENSC 351 at Simon Fraser University from September-December 2023.
Originally developed by Patrina Cheung, Alex Su, Viraj Patel, and Zhaofeng Jiang
Report from the orignal project can be found [here](ENSC351_Final_Project_Write-Up_Guide.pdf)