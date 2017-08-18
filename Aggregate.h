#ifndef _AGGREGATE_H
#define _AGGREGATE_H

#include <DisplayCore.h>

struct DisplayChunk {
    DisplayCore *dev;
    int x;
    int y;
    int w;
    int h;
    DisplayChunk *next;
};

class Aggregate : public DisplayCore {
    private:
        DisplayChunk *_displays;

    public:
        Aggregate() : _displays(NULL) {
            _width = 0;
            _height = 0;
        }
        bool addDisplay(DisplayCore &dev, int x, int y);

        void setRotation(int rotation);
        void displayOn();
        void displayOff();
        void invertDisplay(boolean i);
        void initializeDevice() {}
        void setPixel(int x, int y, color_t color);
        void startBuffer();
        void endBuffer();
        void fillScreen(color_t color);
};

#endif
