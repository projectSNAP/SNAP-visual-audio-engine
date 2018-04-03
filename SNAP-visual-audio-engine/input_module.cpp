#include "input_module.h"

input_module::input_module()
{
	frameX = 0;
	frameY = 0;
}


input_module::~input_module()
{
}

void input_module::set_dimensions(int x, int y)
{
	frameX = x;
	frameY = y;
}
