//
// Created by Mai Pham Quang Huy on 2019-05-06.
//

#ifndef ASN2_ATT1_MAZE_H
#define ASN2_ATT1_MAZE_H

#include <stdio.h>
#include <vector>
#include "Edge.h"

using namespace std;

class Maze {

    private:
        int seed;
        int width;
        int height;
        bool withSeed;

    public:
        Maze();

        Maze(int seed, int width, int height, bool withSeed);

        virtual ~Maze();

        int getSeed() const;

        void setSeed(int seed);

        int getWidth() const;

        void setWidth(int width);

        int getHeight() const;

        void setHeight(int height);

        bool isWithSeed() const;

        void setWithSeed(bool withSeed);
};

#endif //ASN2_ATT1_MAZE_H
