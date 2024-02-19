#include "predator.h"

Predator::Predator(int coord_x, int coord_y)
{
    x = coord_x;
    y = coord_y;
    color = QColor(255,0,0);
    veloc = 1.8;
}
