#ifndef MODE_H
#define MODE_H

typedef enum {
    MODE_CLASSIC = 0,
    MODE_UNICORN = 1
} Mode;

Mode nextMode(Mode mode);
Mode previousMode(Mode mode);
char *modeName(Mode mode);

#endif