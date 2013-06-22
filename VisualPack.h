#ifndef VISUALPACK_H
#define VISUALPACK_H

#include "Pack.h"
#include "Graphics.h"

class VisualPack : public Pack, public Graphics
{
public:

    VisualPack(char* file_name);
};

#endif
