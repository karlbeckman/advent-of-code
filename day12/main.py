class Solution:
  def __init__(self, file_name: str) -> None:
    with open(file_name) as file:
      self.map = [list(line.strip()) for line in file.readlines()]
    
    self.rows, self.cols = len(self.map), len(self.map[0])
    self.garden_plots = {}

  def findGardenPlot(self, row, col, plant_type, visited: set, garden_plot: set):
    if not (0 <= row < self.rows and 0 <= col < self.cols):
      return
    if (row, col) in visited:
      return
    if self.map[row][col] != plant_type:
      return
    else:
      visited.add((row, col))
      garden_plot.add((col, row))

      neigbours = [(-1, 0), (1, 0), (0, -1), (0, 1)]
      for dr, dc in neigbours:
        new_row, new_col = row + dr, col + dc
        self.findGardenPlot(new_row, new_col, plant_type, visited, garden_plot)
      

  def findGardenPlots(self):
    visited = set()

    for row in range(self.rows):
      for col in range(self.cols):
        if not (row, col) in visited:
          plant_type = self.map[row][col]
          if not plant_type in self.garden_plots:
            self.garden_plots[plant_type] = []
          garden_plot = set()
          self.findGardenPlot(row, col, plant_type, visited, garden_plot)
          garden_plot = sorted(garden_plot, key=lambda x: (x[0], x[1]))
          self.garden_plots[plant_type].append(garden_plot)
        
  def calculateCostPart2(self):
    total_cost = 0
    for _, garden_plots in self.garden_plots.items():
      for garden_plot in garden_plots:
        #print(self.countSides(garden_plot))
        total_cost += len(garden_plot) * self.countSides(garden_plot)
    
    print(total_cost)

  def countSides(self, garden_plot: list[tuple[int, int]]):
    points = {} #in polygon
    deltas = [(0, 0), (1, 0), (0, 1), (1, 1)]
    for x, y in garden_plot:
      for dx, dy in deltas:
        if not (x + dx, y + dy) in points:
          points[(x + dx, y + dy)] = 1
        else:
          points[(x + dx, y + dy)] += 1

    sides = 0
    for point, occurrences in points.items():
      if occurrences % 2 != 0:
        sides += 1
      else:
        deltas = [[(-1, 0), (0, -1)], [(-1, -1), (0, 0)]]
        for delta in deltas:
          x1 = point[0] + delta[0][0]
          y1 = point[1] + delta[0][1]
          x2 = point[0] + delta[1][0]
          y2 = point[1] + delta[1][1]
          if not (0 <= x1 < self.cols and 0 <= y1 < self.rows and 0 <= x2 < self.cols and 0 <= y2 < self.rows):
            continue
          if (x1, y1) not in garden_plot and (x2, y2) not in garden_plot:
            sides += 2

    return sides

def main() -> None:
  solution = Solution("input.txt")
  solution.findGardenPlots()
  #print(solution.garden_plots)
  solution.calculateCostPart2()

main()