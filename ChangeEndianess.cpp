#include "ChangeEndianess.h"
#include <stdlib.h>
#include <string.h>

ChangeEndianess::ChangeEndianess()
{

}

void ChangeEndianess::ReverseArray(void *array, int elemSize, int len)
{
    void *temp = new char[elemSize];
    if (temp == NULL)
        throw 1;

    for (int i = 0; i < (len / 2); i++)
    {
        memcpy(temp, ((char*)array) + (i * elemSize), elemSize);
        //dat crazy math
        memcpy(((char*)array) + (i * elemSize), ((char*)array) + (((len - 1) * elemSize) - (i * elemSize)), elemSize);
        memcpy(((char*)array) + (((len - 1) * elemSize) - (i * elemSize)), temp, elemSize);
    }

    delete temp;
}

void ChangeEndianess::Short(short &s)
{
    ReverseArray(&s, sizeof(char), sizeof(short));
}

void ChangeEndianess::Int(int &i)
{
    ReverseArray(&i, sizeof(char), sizeof(int));
}

void ChangeEndianess::Long(long &l)
{
    ReverseArray(&l, sizeof(char), sizeof(long));
}

void ChangeEndianess::LongLong(long long &ll)
{
    ReverseArray(&ll, sizeof(char), sizeof(long long));
}


