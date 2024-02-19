#ifndef VEGAN_H
#define VEGAN_H

#include <QObject>
#include <QPainter>
#include "globalconst.h"
#include "animal.h"

class Vegan : public Animal
{
public:
    Vegan(int coord_x, int coord_y);
};

#endif // VEGAN_H
