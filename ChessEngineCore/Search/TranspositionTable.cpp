#include "TranspositionTable.h"

void TranspositionTable::clear()
{
    tt.clear();
}

void TranspositionTable::put(const TranspositionTable::Entry & entry)
{
    uint16_t key = (uint16_t) entry.fullHash;
    tt[key] = entry;
}

TranspositionTable::Entry * TranspositionTable::find(uint64_t hash)
{
    uint16_t key = (uint16_t) hash;
    auto it = tt.find(key);

    if (it != tt.end())
        return &it->second;
    else
        return nullptr;
}
