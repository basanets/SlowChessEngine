//
// Created by mikhail on 11.04.21.
//

#include "Move.h"

std::string Move::toString() const
{
    std::string promotionPiece = "";
    if (isPromotion())
    {
        if (type() == PROMOTION_KNIGHT || type() == PROMOTION_CAPTURE_KNIGHT)
            promotionPiece = "n";
        if (type() == PROMOTION_BISHOP|| type() == PROMOTION_CAPTURE_BISHOP)
            promotionPiece = "b";
        if (type() == PROMOTION_ROOK || type() == PROMOTION_CAPTURE_ROOK)
            promotionPiece = "r";
        if (type() == PROMOTION_QUEEN || type() == PROMOTION_CAPTURE_QUEEN)
            promotionPiece = "q";
    }

    return std::string(SQUARE_STRING[from()]) + std::string(SQUARE_STRING[to()] + promotionPiece);
}
