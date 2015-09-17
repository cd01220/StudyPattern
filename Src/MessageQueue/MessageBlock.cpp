#include "SystemInclude.h"

#include "MessageQueue/MessageBlock.h"
using namespace std;

MessageBlock::MessageBlock(size_t size, uint_t type)
{
    this->data = new char[size];
    this->type = type;
    this->size = size;
}

MessageBlock::~MessageBlock()
{
    delete[] data;
}