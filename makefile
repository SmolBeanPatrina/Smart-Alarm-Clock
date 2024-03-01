OUTFILE = proj
SOURCE = main.c joystick.c alarm.c LEDMatrix.c lightSensor.c
OUTDIR = $(HOME)/cmpt433/public/myApps
CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Wshadow -Werror -static

LFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB

all: app

app:
	$(CC_C) $(CFLAGS) $(SOURCE) -o $(OUTDIR)/$(OUTFILE)
	ls -l $(OUTDIR)/$(OUTFILE) 

	sudo mkdir -p $(HOME)/cmpt433/public/myApps/wave-files/
	sudo cp wave-files/* $(HOME)/cmpt433/public/myApps/wave-files/

clean:
	rm $(OUTDIR)/$(OUTFILE)
	#$(OUTDIR)/$(OUTFILE)

