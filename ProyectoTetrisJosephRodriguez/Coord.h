#pragma once

class Coord {
public:
    int row;
    int col;
    Coord() {
        row = 0;
        col = 0;
    }
    Coord(int r, int c) {
        row = r;
        col = c;
    }
    bool equals(const Coord& other) const {
        return row == other.row && col == other.col;
    }
};
