#ifndef TRANSPOSITIONTABLE_H
#define TRANSPOSITIONTABLE_H

#include <unordered_map>
#include <inttypes.h>

class TranspositionTable
{
public:
    class Entry
    {
    public:
        enum EvalType: uint16_t
        {
            Exact,
            UpperBound,
            LowerBound
        };

        uint64_t fullHash;
        int32_t evaluation;
        uint16_t plyFromRoot;
        EvalType evalType;
    };

    void clear();
    void put(const Entry & entry);
    Entry * find(uint64_t hash);

private:
    std::unordered_map<uint16_t, Entry> tt;
};

#endif // TRANSPOSITIONTABLE_H
