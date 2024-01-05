#include "Node.h"


int CNode::IsDirectionColliable(float nx, float ny)
{
	return 0;
}
CNode::CNode(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CNode::Render()
{
	//RenderBoundingBox();
}

void CNode::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}
