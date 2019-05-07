//
// Created by Mai Pham Quang Huy on 2019-05-06.
//

#ifndef ASN2_ATT1_EDGE_H
#define ASN2_ATT1_EDGE_H

#include <stdio.h>
#include "Coordinator.h"

class Edge {

    private:
        Coordinator coordinator1;
        Coordinator coordinator2;

    public:
        Edge();

        Edge(const Coordinator &coordinator1, const Coordinator &coordinator2);

        virtual ~Edge();

        const Coordinator &getCoordinator1() const;

        void setCoordinator1(const Coordinator &coordinator1);

        const Coordinator &getCoordinator2() const;

        void setCoordinator2(const Coordinator &coordinator2);
};

#endif //ASN2_ATT1_EDGE_H
