# Makefile (simple)
#
# Lothar Rubusch

SOURCE = main.c
OBJECTS = ${SOURCE:%.c=%.o}
CC = g++
CFLAGS = -g -Wall `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`
RM = rm -f

%.o: %.c
	${CC} -c ${CFLAGS} $<

main.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm ${LIBS}
# -L/opt/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_video


all: main.exe

clean:
	${RM} $(OBJECTS) main.exe *~ core

.PHONY: clean all


