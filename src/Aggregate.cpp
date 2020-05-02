#include <Aggregate.h>

bool Aggregate::addDisplay(Cariad &dev, int x, int y) {
    DisplayChunk *chunk = (struct DisplayChunk *)malloc(sizeof(struct DisplayChunk));
    if (!chunk) return false;
    chunk->dev = &dev;
    chunk->x = x;
    chunk->y = y;
    chunk->w = dev.getWidth();
    chunk->h = dev.getHeight();
    chunk->next = NULL;

    if (x + dev.getWidth() > _width) {
        _width = x + dev.getWidth();
    }

    if (y + dev.getHeight() > _height) {
        _height = y + dev.getHeight();
    }

    if (_displays == NULL) {
        _displays = chunk;
        return true;
    }

    DisplayChunk *scan;
    for (scan = _displays; scan->next; scan = scan->next);
    scan->next = chunk;
    return true;
}

void Aggregate::setRotation(int rotation) {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->setRotation(rotation);
    }
}

void Aggregate::displayOn() {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->displayOn();
    }
}

void Aggregate::displayOff() {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->displayOff();
    }
}

void Aggregate::startBuffer() {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->startBuffer();
    }
}

void Aggregate::endBuffer() {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->endBuffer();
    }
}

void Aggregate::fillScreen(color_t color) {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->fillScreen(color);
    }
}

void Aggregate::invertDisplay(bool i) {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        scan->dev->invertDisplay(i);
    }
}

void Aggregate::setPixel(int x, int y, color_t color) {
    for (struct DisplayChunk *scan = _displays; scan; scan = scan->next) {
        if (x >= scan->x && y >= scan->y && x < scan->x + scan->w && y < scan->y + scan->h) {
            scan->dev->setPixel(x - scan->x, y - scan->y, color);
        }
    }
}


