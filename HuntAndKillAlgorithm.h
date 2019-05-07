//
// Created by Mai Pham Quang Huy on 2019-05-06.
//

#ifndef ASN2_ATT1_HUNTANDKILLALGORITHM_H
#define ASN2_ATT1_HUNTANDKILLALGORITHM_H

#include <stdio.h>
#include "Maze.h"

class HuntAndKill: public Maze {

    public:
        vector<Edge> generate();
};

#endif //ASN2_ATT1_HUNTANDKILLALGORITHM_H
