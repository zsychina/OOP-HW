class Grid:
    def __init__(self):
        self.BOX_SIZE = 3
        self.GRID_SIZE = 9
        self.grid = [[0] * self.GRID_SIZE for _ in range(self.GRID_SIZE)]

    def getRow(self, row):
        return self.grid[row]

    def getColumn(self, col):
        return [self.grid[i][col] for i in range(self.GRID_SIZE)]

    def getBox(self, row, col):
        box_row_start = (row // self.BOX_SIZE) * self.BOX_SIZE
        box_col_start = (col // self.BOX_SIZE) * self.BOX_SIZE
        box = []
        for i in range(box_row_start, box_row_start + self.BOX_SIZE):
            for j in range(box_col_start, box_col_start + self.BOX_SIZE):
                box.append(self.grid[i][j])
        return box

class Sudoku(Grid):
    def __init__(self, input_str):
        super(Sudoku, self).__init__()
        self.parse(input_str)

    def parse(self, input_str):
        for row in range(self.GRID_SIZE):
            for col in range(self.GRID_SIZE):
                index = row * self.GRID_SIZE + col
                value = int(input_str[index])
                self.grid[row][col] = value

    def getInference(self):
        candidates = [[set(range(1, 10)) for _ in range(self.GRID_SIZE)] for _ in range(self.GRID_SIZE)]
        for row in range(self.GRID_SIZE):
            for col in range(self.GRID_SIZE):
                if self.grid[row][col]!= 0:
                    candidates[row][col] = set()
                    value = self.grid[row][col]
                    for i in range(self.GRID_SIZE):
                        candidates[row][i].discard(value)
                        candidates[i][col].discard(value)
                    box_row = (row // self.BOX_SIZE) * self.BOX_SIZE
                    box_col = (col // self.BOX_SIZE) * self.BOX_SIZE
                    for i in range(box_row, box_row + self.BOX_SIZE):
                        for j in range(box_col, box_col + self.BOX_SIZE):
                            candidates[i][j].discard(value)
        return candidates

    def solve(self):
        candidates = self.getInference()
        for row in range(self.GRID_SIZE):
            for col in range(self.GRID_SIZE):
                if self.grid[row][col] == 0:
                    possible_values = candidates[row][col]
                    for value in possible_values:
                        self.grid[row][col] = value
                        if self.solve():
                            return True
                        else:
                            self.grid[row][col] = 0
                    return False
        return True



if __name__ == '__main__':
    input_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    sudoku = Sudoku(input_str)
    if sudoku.solve():
        for row in sudoku.grid:
            print(row)
    else:
        print("No solution found.")