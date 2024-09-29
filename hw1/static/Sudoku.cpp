#include <iostream>
#include <vector>
#include <set>

class Grid {
public:
    const int BOX_SIZE = 3;
    const int GRID_SIZE = 9;
    std::vector<std::vector<int>> grid;

    Grid() {
        grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    }

    std::vector<int> getRow(int row) {
        return grid[row];
    }

    std::vector<int> getColumn(int col) {
        std::vector<int> column;
        for (int i = 0; i < GRID_SIZE; ++i) {
            column.push_back(grid[i][col]);
        }
        return column;
    }

    std::vector<int> getBox(int row, int col) {
        std::vector<int> box;
        int box_row_start = (row / BOX_SIZE) * BOX_SIZE;
        int box_col_start = (col / BOX_SIZE) * BOX_SIZE;
        for (int i = box_row_start; i < box_row_start + BOX_SIZE; ++i) {
            for (int j = box_col_start; j < box_col_start + BOX_SIZE; ++j) {
                box.push_back(grid[i][j]);
            }
        }
        return box;
    }
};

class Sudoku : public Grid {
public:
    Sudoku(std::string input_str) {
        parse(input_str);
    }

    void parse(std::string input_str) {
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                int index = row * GRID_SIZE + col;
                int value = input_str[index] - '0';
                grid[row][col] = value;
            }
        }
    }

    std::vector<std::vector<std::set<int>>> getInference() {
        std::vector<std::vector<std::set<int>>> candidates(GRID_SIZE, std::vector<std::set<int>>(GRID_SIZE, std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if (grid[row][col]!= 0) {
                    candidates[row][col] = std::set<int>();
                    int value = grid[row][col];
                    for (int i = 0; i < GRID_SIZE; ++i) {
                        candidates[row][i].erase(value);
                        candidates[i][col].erase(value);
                    }
                    int box_row = (row / BOX_SIZE) * BOX_SIZE;
                    int box_col = (col / BOX_SIZE) * BOX_SIZE;
                    for (int i = box_row; i < box_row + BOX_SIZE; ++i) {
                        for (int j = box_col; j < box_col + BOX_SIZE; ++j) {
                            candidates[i][j].erase(value);
                        }
                    }
                }
            }
        }
        return candidates;
    }

    bool solve() {
        std::vector<std::vector<std::set<int>>> candidates = getInference();
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if (grid[row][col] == 0) {
                    std::set<int> possible_values = candidates[row][col];
                    for (int value : possible_values) {
                        grid[row][col] = value;
                        if (solve()) {
                            return true;
                        } else {
                            grid[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    std::string input_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    Sudoku sudoku(input_str);
    if (sudoku.solve()) {
        for (const auto& row : sudoku.grid) {
            for (int value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "No solution found." << std::endl;
    }
    return 0;
}