//
// Created by Mai Pham Quang Huy on 2019-05-06.
//

#ifndef ASN2_ATT1_COORDINATOR_H
#define ASN2_ATT1_COORDINATOR_H

#include <stdio.h>

class Coordinator {

    private:
        int x;
        int y;

    public:
        Coordinator();

        Coordinator(int x, int y);

        virtual ~Coordinator();

        int getX() const;

        void setX(int x);

        int getY() const;

        void setY(int y);
};

#endif //ASN2_ATT1_COORDINATOR_H
