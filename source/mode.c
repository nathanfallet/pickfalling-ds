#include "mode.h"

Mode nextMode(Mode mode) {
    switch (mode) {
        case MODE_CLASSIC:
            return MODE_UNICORN;
        case MODE_UNICORN:
            return MODE_CLASSIC;
    }
    return MODE_CLASSIC;
}

Mode previousMode(Mode mode) {
    switch (mode) {
        case MODE_CLASSIC:
            return MODE_UNICORN;
        case MODE_UNICORN:
            return MODE_CLASSIC;
    }
    return MODE_CLASSIC;
}

char *modeName(Mode mode) {
    switch (mode) {
        case MODE_CLASSIC:
            return "CLASSIC";
        case MODE_UNICORN:
            return "UNICORN";
    }
    return "UNKNOWN";
}