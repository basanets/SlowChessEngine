//
// Created by mikhail on 11.04.21.
//

#include "BB.h"

Bitboard BB::SQUARES[NUMBER_OF_SQUARES] =
{
    0x1ull, 0x2ull, 0x4ull, 0x8ull,
    0x10ull, 0x20ull, 0x40ull, 0x80ull,
    0x100ull, 0x200ull, 0x400ull, 0x800ull,
    0x1000ull, 0x2000ull, 0x4000ull, 0x8000ull,
    0x10000ull, 0x20000ull, 0x40000ull, 0x80000ull,
    0x100000ull, 0x200000ull, 0x400000ull, 0x800000ull,
    0x1000000ull, 0x2000000ull, 0x4000000ull, 0x8000000ull,
    0x10000000ull, 0x20000000ull, 0x40000000ull, 0x80000000ull,
    0x100000000ull, 0x200000000ull, 0x400000000ull, 0x800000000ull,
    0x1000000000ull, 0x2000000000ull, 0x4000000000ull, 0x8000000000ull,
    0x10000000000ull, 0x20000000000ull, 0x40000000000ull, 0x80000000000ull,
    0x100000000000ull, 0x200000000000ull, 0x400000000000ull, 0x800000000000ull,
    0x1000000000000ull, 0x2000000000000ull, 0x4000000000000ull, 0x8000000000000ull,
    0x10000000000000ull, 0x20000000000000ull, 0x40000000000000ull, 0x80000000000000ull,
    0x100000000000000ull, 0x200000000000000ull, 0x400000000000000ull, 0x800000000000000ull,
    0x1000000000000000ull, 0x2000000000000000ull, 0x4000000000000000ull, 0x8000000000000000ull,
};

Bitboard BB::RANKS[8] =
{
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
};

Bitboard BB::FILES[8] =
{
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H
};

Bitboard BB::DIAGONALS[15] =
{
    0x80ull,
    0x8040ull,
    0x804020ull,
    0x80402010ull,
    0x8040201008ull,
    0x804020100804ull,
    0x80402010080402ull,
    0x8040201008040201ull,
    0x4020100804020100ull,
    0x2010080402010000ull,
    0x1008040201000000ull,
    0x804020100000000ull,
    0x402010000000000ull,
    0x201000000000000ull,
    0x100000000000000ull,
};

Bitboard BB::ANTI_DIAGONALS[15] =
{
    0x1ull,
    0x102ull,
    0x10204ull,
    0x1020408ull,
    0x102040810ull,
    0x10204081020ull,
    0x1020408102040ull,
    0x102040810204080ull,
    0x204081020408000ull,
    0x408102040800000ull,
    0x810204080000000ull,
    0x1020408000000000ull,
    0x2040800000000000ull,
    0x4080000000000000ull,
    0x8000000000000000ull,
};

Bitboard BB::SQUARES_BETWEEN[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];
Bitboard BB::LINE[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];




Bitboard BB::PAWN_ATTACKS[NUMBER_OF_COLORS][NUMBER_OF_SQUARES] =
{
    {  // BLACK PAWNS ATTACKS TO WHITE
        0x200ull, 0x500ull, 0xa00ull, 0x1400ull,
        0x2800ull, 0x5000ull, 0xa000ull, 0x4000ull,
        0x20000ull, 0x50000ull, 0xa0000ull, 0x140000ull,
        0x280000ull, 0x500000ull, 0xa00000ull, 0x400000ull,
        0x2000000ull, 0x5000000ull, 0xa000000ull, 0x14000000ull,
        0x28000000ull, 0x50000000ull, 0xa0000000ull, 0x40000000ull,
        0x200000000ull, 0x500000000ull, 0xa00000000ull, 0x1400000000ull,
        0x2800000000ull, 0x5000000000ull, 0xa000000000ull, 0x4000000000ull,
        0x20000000000ull, 0x50000000000ull, 0xa0000000000ull, 0x140000000000ull,
        0x280000000000ull, 0x500000000000ull, 0xa00000000000ull, 0x400000000000ull,
        0x2000000000000ull, 0x5000000000000ull, 0xa000000000000ull, 0x14000000000000ull,
        0x28000000000000ull, 0x50000000000000ull, 0xa0000000000000ull, 0x40000000000000ull,
        0x200000000000000ull, 0x500000000000000ull, 0xa00000000000000ull, 0x1400000000000000ull,
        0x2800000000000000ull, 0x5000000000000000ull, 0xa000000000000000ull, 0x4000000000000000ull,
        0x0ull, 0x0ull, 0x0ull, 0x0ull,
        0x0ull, 0x0ull, 0x0ull, 0x0ull,
    }, // BLACK PAWNS ATTACKS TO WHITE

    {  // WHITE PAWNS ATTACKS TO BLACK
        0x0ull, 0x0ull, 0x0ull, 0x0ull,
        0x0ull, 0x0ull, 0x0ull, 0x0ull,
        0x2ull, 0x5ull, 0xaull, 0x14ull,
        0x28ull, 0x50ull, 0xa0ull, 0x40ull,
        0x200ull, 0x500ull, 0xa00ull, 0x1400ull,
        0x2800ull, 0x5000ull, 0xa000ull, 0x4000ull,
        0x20000ull, 0x50000ull, 0xa0000ull, 0x140000ull,
        0x280000ull, 0x500000ull, 0xa00000ull, 0x400000ull,
        0x2000000ull, 0x5000000ull, 0xa000000ull, 0x14000000ull,
        0x28000000ull, 0x50000000ull, 0xa0000000ull, 0x40000000ull,
        0x200000000ull, 0x500000000ull, 0xa00000000ull, 0x1400000000ull,
        0x2800000000ull, 0x5000000000ull, 0xa000000000ull, 0x4000000000ull,
        0x20000000000ull, 0x50000000000ull, 0xa0000000000ull, 0x140000000000ull,
        0x280000000000ull, 0x500000000000ull, 0xa00000000000ull, 0x400000000000ull,
        0x2000000000000ull, 0x5000000000000ull, 0xa000000000000ull, 0x14000000000000ull,
        0x28000000000000ull, 0x50000000000000ull, 0xa0000000000000ull, 0x40000000000000ull,
    } // WHITE PAWNS ATTACKS TO BLACK
};

Bitboard BB::KING_ATTACKS[NUMBER_OF_SQUARES] =
{
    0x302ull, 0x705ull, 0xe0aull, 0x1c14ull,
    0x3828ull, 0x7050ull, 0xe0a0ull, 0xc040ull,
    0x30203ull, 0x70507ull, 0xe0a0eull, 0x1c141cull,
    0x382838ull, 0x705070ull, 0xe0a0e0ull, 0xc040c0ull,
    0x3020300ull, 0x7050700ull, 0xe0a0e00ull, 0x1c141c00ull,
    0x38283800ull, 0x70507000ull, 0xe0a0e000ull, 0xc040c000ull,
    0x302030000ull, 0x705070000ull, 0xe0a0e0000ull, 0x1c141c0000ull,
    0x3828380000ull, 0x7050700000ull, 0xe0a0e00000ull, 0xc040c00000ull,
    0x30203000000ull, 0x70507000000ull, 0xe0a0e000000ull, 0x1c141c000000ull,
    0x382838000000ull, 0x705070000000ull, 0xe0a0e0000000ull, 0xc040c0000000ull,
    0x3020300000000ull, 0x7050700000000ull, 0xe0a0e00000000ull, 0x1c141c00000000ull,
    0x38283800000000ull, 0x70507000000000ull, 0xe0a0e000000000ull, 0xc040c000000000ull,
    0x302030000000000ull, 0x705070000000000ull, 0xe0a0e0000000000ull, 0x1c141c0000000000ull,
    0x3828380000000000ull, 0x7050700000000000ull, 0xe0a0e00000000000ull, 0xc040c00000000000ull,
    0x203000000000000ull, 0x507000000000000ull, 0xa0e000000000000ull, 0x141c000000000000ull,
    0x2838000000000000ull, 0x5070000000000000ull, 0xa0e0000000000000ull, 0x40c0000000000000ull,
};

Bitboard BB::KNIGHT_ATTACKS[NUMBER_OF_SQUARES] =
{
    0x20400ull, 0x50800ull, 0xa1100ull, 0x142200ull,
    0x284400ull, 0x508800ull, 0xa01000ull, 0x402000ull,
    0x2040004ull, 0x5080008ull, 0xa110011ull, 0x14220022ull,
    0x28440044ull, 0x50880088ull, 0xa0100010ull, 0x40200020ull,
    0x204000402ull, 0x508000805ull, 0xa1100110aull, 0x1422002214ull,
    0x2844004428ull, 0x5088008850ull, 0xa0100010a0ull, 0x4020002040ull,
    0x20400040200ull, 0x50800080500ull, 0xa1100110a00ull, 0x142200221400ull,
    0x284400442800ull, 0x508800885000ull, 0xa0100010a000ull, 0x402000204000ull,
    0x2040004020000ull, 0x5080008050000ull, 0xa1100110a0000ull, 0x14220022140000ull,
    0x28440044280000ull, 0x50880088500000ull, 0xa0100010a00000ull, 0x40200020400000ull,
    0x204000402000000ull, 0x508000805000000ull, 0xa1100110a000000ull, 0x1422002214000000ull,
    0x2844004428000000ull, 0x5088008850000000ull, 0xa0100010a0000000ull, 0x4020002040000000ull,
    0x400040200000000ull, 0x800080500000000ull, 0x1100110a00000000ull, 0x2200221400000000ull,
    0x4400442800000000ull, 0x8800885000000000ull, 0x100010a000000000ull, 0x2000204000000000ull,
    0x4020000000000ull, 0x8050000000000ull, 0x110a0000000000ull, 0x22140000000000ull,
    0x44280000000000ull, 0x0088500000000000ull, 0x0010a00000000000ull, 0x20400000000000ull,
};

Bitboard BB::BISHOP_ATTACKS[NUMBER_OF_SQUARES][512];
Bitboard BB::BISHOP_ATTACK_MASKS[NUMBER_OF_SQUARES];
int BB::BISHOP_ATTACK_SHIFTS[NUMBER_OF_SQUARES];
// THANK YOU SMALLCHESS ENGINE
Bitboard BB::BISHOP_MAGICS[NUMBER_OF_SQUARES] =
{
    0x0002020202020200ull, 0x0002020202020000ull, 0x0004010202000000ull, 0x0004040080000000ull,
    0x0001104000000000ull, 0x0000821040000000ull, 0x0000410410400000ull, 0x0000104104104000ull,
    0x0000040404040400ull, 0x0000020202020200ull, 0x0000040102020000ull, 0x0000040400800000ull,
    0x0000011040000000ull, 0x0000008210400000ull, 0x0000004104104000ull, 0x0000002082082000ull,
    0x0004000808080800ull, 0x0002000404040400ull, 0x0001000202020200ull, 0x0000800802004000ull,
    0x0000800400A00000ull, 0x0000200100884000ull, 0x0000400082082000ull, 0x0000200041041000ull,
    0x0002080010101000ull, 0x0001040008080800ull, 0x0000208004010400ull, 0x0000404004010200ull,
    0x0000840000802000ull, 0x0000404002011000ull, 0x0000808001041000ull, 0x0000404000820800ull,
    0x0001041000202000ull, 0x0000820800101000ull, 0x0000104400080800ull, 0x0000020080080080ull,
    0x0000404040040100ull, 0x0000808100020100ull, 0x0001010100020800ull, 0x0000808080010400ull,
    0x0000820820004000ull, 0x0000410410002000ull, 0x0000082088001000ull, 0x0000002011000800ull,
    0x0000080100400400ull, 0x0001010101000200ull, 0x0002020202000400ull, 0x0001010101000200ull,
    0x0000410410400000ull, 0x0000208208200000ull, 0x0000002084100000ull, 0x0000000020880000ull,
    0x0000001002020000ull, 0x0000040408020000ull, 0x0004040404040000ull, 0x0002020202020000ull,
    0x0000104104104000ull, 0x0000002082082000ull, 0x0000000020841000ull, 0x0000000000208800ull,
    0x0000000010020200ull, 0x0000000404080200ull, 0x0000040404040400ull, 0x0002020202020200ull,
};

Bitboard BB::ROOK_ATTACKS[NUMBER_OF_SQUARES][4096];
Bitboard BB::ROOK_ATTACK_MASKS[NUMBER_OF_SQUARES];
int BB::ROOK_ATTACK_SHIFTS[NUMBER_OF_SQUARES];
// THANK YOU SMALLCHESS ENGINE
Bitboard BB::ROOK_MAGICS[NUMBER_OF_SQUARES] =
{
    0x0080001020400080ull, 0x0040001000200040ull, 0x0080081000200080ull, 0x0080040800100080ull,
    0x0080020400080080ull, 0x0080010200040080ull, 0x0080008001000200ull, 0x0080002040800100ull,
    0x0000800020400080ull, 0x0000400020005000ull, 0x0000801000200080ull, 0x0000800800100080ull,
    0x0000800400080080ull, 0x0000800200040080ull, 0x0000800100020080ull, 0x0000800040800100ull,
    0x0000208000400080ull, 0x0000404000201000ull, 0x0000808010002000ull, 0x0000808008001000ull,
    0x0000808004000800ull, 0x0000808002000400ull, 0x0000010100020004ull, 0x0000020000408104ull,
    0x0000208080004000ull, 0x0000200040005000ull, 0x0000100080200080ull, 0x0000080080100080ull,
    0x0000040080080080ull, 0x0000020080040080ull, 0x0000010080800200ull, 0x0000800080004100ull,
    0x0000204000800080ull, 0x0000200040401000ull, 0x0000100080802000ull, 0x0000080080801000ull,
    0x0000040080800800ull, 0x0000020080800400ull, 0x0000020001010004ull, 0x0000800040800100ull,
    0x0000204000808000ull, 0x0000200040008080ull, 0x0000100020008080ull, 0x0000080010008080ull,
    0x0000040008008080ull, 0x0000020004008080ull, 0x0000010002008080ull, 0x0000004081020004ull,
    0x0000204000800080ull, 0x0000200040008080ull, 0x0000100020008080ull, 0x0000080010008080ull,
    0x0000040008008080ull, 0x0000020004008080ull, 0x0000800100020080ull, 0x0000800041000080ull,
    0x00FFFCDDFCED714Aull, 0x007FFCDDFCED714Aull, 0x003FFFCDFFD88096ull, 0x0000040810002101ull,
    0x0001000204080011ull, 0x0001000204000801ull, 0x0001000082000401ull, 0x0001FFFAABFAD1A2ull,
};

void BB::initializeAll()
{
    // initialize rook tables
    for (Square sq = A1; sq <= H8; ++sq)
    {
        Bitboard boardEdges = ((FILE_A | FILE_H) & ~FILES[fileOf(sq)])
                              | ((RANK_1 | RANK_8) & ~RANKS[rankOf(sq)]);
        ROOK_ATTACK_MASKS[sq] = (RANKS[rankOf(sq)] ^ FILES[fileOf(sq)]) & ~boardEdges;
        ROOK_ATTACK_SHIFTS[sq] = 64 - ROOK_ATTACK_MASKS[sq].populationCount();

        Bitboard subset = 0;
        do
        {
            uint64_t index = static_cast<uint64_t>(subset);
            index = index * static_cast<uint64_t>(ROOK_MAGICS[sq]);
            index = index >> ROOK_ATTACK_SHIFTS[sq];
            ROOK_ATTACKS[sq][index] = Bitboard::slidingAttacks(sq, Bitboard(subset), FILES[fileOf(sq)])
                                      | Bitboard::slidingAttacks(sq, Bitboard(subset), RANKS[rankOf(sq)]);
            subset = (subset - ROOK_ATTACK_MASKS[sq]) & ROOK_ATTACK_MASKS[sq];
        }
        while (subset);
    }

    // initialize bishop tables
    for (Square sq = A1; sq <= H8; ++sq)
    {
        Bitboard boardEdges = ((FILE_A | FILE_H) & ~FILES[fileOf(sq)])
                              | ((RANK_1 | RANK_8) & ~RANKS[rankOf(sq)]);
        BISHOP_ATTACK_MASKS[sq] = (DIAGONALS[diagonalOf(sq)]
                                   ^ ANTI_DIAGONALS[antiDiagonalOf(sq)]) & ~boardEdges;
        BISHOP_ATTACK_SHIFTS[sq] = 64 - BISHOP_ATTACK_MASKS[sq].populationCount();

        Bitboard subset = 0;
        do
        {
            uint64_t index = static_cast<uint64_t>(subset);
            index = index * static_cast<uint64_t>(BISHOP_MAGICS[sq]);
            index = index >> BISHOP_ATTACK_SHIFTS[sq];
            BISHOP_ATTACKS[sq][index] = Bitboard::slidingAttacks(sq, subset, DIAGONALS[diagonalOf(sq)])
                                        | Bitboard::slidingAttacks(sq, subset, ANTI_DIAGONALS[antiDiagonalOf(sq)]);
            subset = (subset - BISHOP_ATTACK_MASKS[sq]) & BISHOP_ATTACK_MASKS[sq];
        }
        while (subset);
    }

    // initialize squares between
    for (Square sI = A1; sI <= H8; ++sI)
    {
        for (Square sJ = A1; sJ <= H8; ++sJ)
        {
            Bitboard squares = SQUARES[sI] | SQUARES[sJ];
            if (sI == sJ)
            {
                SQUARES_BETWEEN[sI][sJ] = EMPTY;
            }
            else if (fileOf(sI) == fileOf(sJ) || rankOf(sI) == rankOf(sJ))
            {
                SQUARES_BETWEEN[sI][sJ] = Bitboard::rookAttacks(sI, squares) & Bitboard::rookAttacks(sJ, squares);
            }
            else if (diagonalOf(sI) == diagonalOf(sJ) || antiDiagonalOf(sI) == antiDiagonalOf(sJ))
            {
                SQUARES_BETWEEN[sI][sJ] = Bitboard::bishopAttacks(sI, squares) & Bitboard::bishopAttacks(sJ, squares);
            }
            else
            {
                SQUARES_BETWEEN[sI][sJ] = EMPTY;
            }
        }
    }

    // initialize lines
    for (Square sI = A1; sI <= H8; ++sI)
    {
        for (Square sJ = A1; sJ <= H8; ++sJ)
        {
            Bitboard squares = SQUARES[sI] | SQUARES[sJ];
            if (sI == sJ)
            {
                LINE[sI][sJ] = EMPTY;
            }
            else if (fileOf(sI) == fileOf(sJ) || rankOf(sI) == rankOf(sJ))
            {
                LINE[sI][sJ] = (Bitboard::rookAttacks(sI, EMPTY) & Bitboard::rookAttacks(sJ, EMPTY)) | squares;
            }
            else if (diagonalOf(sI) == diagonalOf(sJ) || antiDiagonalOf(sI) == antiDiagonalOf(sJ))
            {
                LINE[sI][sJ] = (Bitboard::bishopAttacks(sI, EMPTY) & Bitboard::bishopAttacks(sJ, EMPTY)) | squares;
            }
            else
            {
                LINE[sI][sJ] = EMPTY;
            }
        }
    }
}
