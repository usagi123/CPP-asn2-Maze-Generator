//
// Created by Mai Pham Quang Huy on 2019-05-06.
//

#include "Maze.h"

Maze::Maze() {}

Maze::Maze(int seed, int width, int height, bool withSeed) : seed(seed), width(width), height(height), withSeed(withSeed) {}

Maze::~Maze() {}

int Maze::getSeed() const {
    return seed;
}

void Maze::setSeed(int seed) {
    Maze::seed = seed;
}

int Maze::getWidth() const {
    return width;
}

void Maze::setWidth(int width) {
    Maze::width = width;
}

int Maze::getHeight() const {
    return height;
}

void Maze::setHeight(int height) {
    Maze::height = height;
}

bool Maze::isWithSeed() const {
    return withSeed;
}

void Maze::setWithSeed(bool withSeed) {
    Maze::withSeed = withSeed;
}

