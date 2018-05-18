#include "forest.h"

Node::~Node() {
	delete positions;
}