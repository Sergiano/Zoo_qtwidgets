#include "vegan.h"

Vegan::Vegan(int coord_x, int coord_y)
{
    x = coord_x;
    y = coord_y;
    color = QColor(0,255,0);
    veloc = 1;
}
