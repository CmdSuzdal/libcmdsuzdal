#include "cmdsuzdal/bbdefines.h"

namespace cSzd
{
    // Given file and rank returns the cell
    Cell toCell(File f, Rank r)
    {
        if ((f >= f_a) && (f <= f_h) && (r >= r_1) && (r <= r_8))
            return static_cast<Cell>(r * 8 + f);
        return InvalidCell;
    }

    // Given a cell, returns File, Rank, Diagonal, AntiDiagonal (and combinations)
    File file(const Cell &c) { return static_cast<File>(c % 8); }
    Rank rank(const Cell &c) { return static_cast<Rank>(c >> 3); }
    Diagonal diag(const Cell &c) { return static_cast<Diagonal>(file(c) - rank(c) + 7); }
    AntiDiagonal antiDiag(const Cell &c) { return static_cast<AntiDiagonal>(file(c) + rank(c)); }
    std::pair<File, Rank> coords(const Cell &c)
    {
        return std::make_pair(file(c), rank(c));
    }
    std::pair<Diagonal, AntiDiagonal> diagonals(const Cell &c)
    {
        return std::make_pair(diag(c), antiDiag(c));
    }

    // Given a cell, returns west/east files and south/north ranks
    File west(const Cell &c)
    {
        auto f = file(c);
        return static_cast<File>((f > 0) ? (f - 1) : InvalidFile);
    }
    File east(const Cell &c)
    {
        auto f = file(c);
        return static_cast<File>((f < 7) ? (f + 1) : InvalidFile);
    }
    Rank south(const Cell &c)
    {
        auto r = rank(c);
        return static_cast<Rank>((r > 0) ? (r - 1) : InvalidRank);
    }
    Rank north(const Cell &c)
    {
        auto r = rank(c);
        return static_cast<Rank>((r < 7) ? (r + 1) : InvalidRank);
    }

    // "Compass rose" methods
    Cell w(const Cell &c) { return static_cast<Cell>((file(c) > 0) ? c - 1 : InvalidCell); }
    Cell nw(const Cell &c) { return static_cast<Cell>((file(c) > 0 && rank(c) < 7) ? c + 7 : InvalidCell); }
    Cell n(const Cell &c) { return static_cast<Cell>((rank(c) < 7) ? c + 8 : InvalidCell); }
    Cell ne(const Cell &c) { return static_cast<Cell>((file(c) < 7 && rank(c) < 7) ? c + 9 : InvalidCell); }
    Cell e(const Cell &c) { return static_cast<Cell>((file(c) < 7) ? c + 1 : InvalidCell); }
    Cell se(const Cell &c) { return static_cast<Cell>((file(c) < 7 && rank(c) > 0) ? c - 7 : InvalidCell); }
    Cell s(const Cell &c) { return static_cast<Cell>((rank(c) > 0) ? c - 8 : InvalidCell); }
    Cell sw(const Cell &c) { return static_cast<Cell>((file(c) > 0 && rank(c) > 0) ? c - 9 : InvalidCell); }

    Cell calcCellAfterSteps(const Cell &c, int stepNorth, int stepEast)
    {
        // Computes the position of the cells reached starting from Cell c
        // and performing stepNorth steps towards north and stepEast steps
        // towards east. If stepNorth is negative the steps are done towards
        // south, if stepEast is negative, the steps are done towards west
        auto newRank = (static_cast<int>(rank(c)) + stepNorth);
        auto newFile = (static_cast<int>(file(c)) + stepEast);
        if (newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7)
            return InvalidCell;
        return static_cast<Cell>(c + stepEast + (stepNorth * 8));
    }

    BitBoardState singlecell(const Cell &c) { return (1ULL << c); }

    BitBoardState neighbour(const Cell &c)
    {
        File f, w, e;
        Rank r, s, n;
        f = file(c);
        r = rank(c);
        w = west(c);
        e = east(c);
        s = south(c);
        n = north(c);
        return ((FilesBB[w] | FilesBB[f] | FilesBB[e]) &
                (RanksBB[n] | RanksBB[r] | RanksBB[s])) ^
               singlecell(c);
    }

    BitBoardState fileMask(const Cell &c) { return (FilesBB[file(c)]); }
    BitBoardState rankMask(const Cell &c) { return (RanksBB[rank(c)]); }
    BitBoardState fileRankMask(const Cell &c) { return fileMask(c) | rankMask(c); }
    BitBoardState diagMask(const Cell &c) { return (DiagsBB[diag(c)]); }
    BitBoardState antiDiagMask(const Cell &c) { return (AntiDiagsBB[antiDiag(c)]); }
    BitBoardState diagonalsMask(const Cell &c) { return diagMask(c) | antiDiagMask(c); }
    BitBoardState queenMask(const Cell &c) { return fileMask(c) | rankMask(c) | diagMask(c) | antiDiagMask(c); }

    // conversion from string functions
    File toFile(const char &f)
    {
        if (f >= 'a' && f <= 'h')
            return static_cast<File>(f - 'a');
        return InvalidFile;
    }
    Rank toRank(const char &r)
    {
        if (r >= '1' && r <= '8')
            return static_cast<Rank>(r - '1');
        return InvalidRank;
    }
    Cell toCell(const std::string_view c)
    {
        if (c.size() == 2)
            return toCell(toFile(c.at(0)), toRank(c.at(1)));
        return InvalidCell;
    }

    File prevFile(File f) { return (f > f_a && f <= f_h) ? (static_cast<File>(f - 1)) : InvalidFile; };
    File nextFile(File f) { return (f < f_h && f >= f_a) ? (static_cast<File>(f + 1)) : InvalidFile; };
    Rank prevRank(Rank r) { return (r > r_1 && r <= r_8) ? (static_cast<Rank>(r - 1)) : InvalidRank; };
    Rank nextRank(Rank r) { return (r < r_8 && r >= r_1) ? (static_cast<Rank>(r + 1)) : InvalidRank; };

    std::string cellName(const Cell &c)
    {
        std::string s;
        s += 'a' + file(c);
        s += '1' + rank(c);
        return s;
    }

}