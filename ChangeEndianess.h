#ifndef CHANGE_ENDIANESS_H
#define CHANGE_ENDIANESS_H

class ChangeEndianess
{
    public:
        ChangeEndianess();
        static void ReverseArray(void *array, int elemSize, int len);
        static void Short(short &s);
        static void Int(int &i);
        static void Long(long &l);
        static void LongLong(long long &ll);
};

#endif // CHANGE_ENDIANESS_H
