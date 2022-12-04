#!/usr/bin/python3

class Assignment:
  def __init__(self, assignments):
    self.first = self.parse_range(assignments[0])
    self.second = self.parse_range(assignments[1])
    self.first = set(range(self.first[0], self.first[1] + 1))
    self.second = set(range(self.second[0], self.second[1] + 1))

    self.has_overlap = False
    self.has_partial_overlap = False

    intersection = self.first.intersection(self.second)
    if intersection == self.first or intersection == self.second:
      self.has_overlap = True

    if len(intersection) > 0:
      self.has_partial_overlap = True

  # take a str in form X-Y and return (X, Y)
  def parse_range(self, assign):
    overlaps = 0
    line = assign.split('-')
    return (int(line[0]), int(line[1]))


def part1(assignments):
    overlaps = 0
    for a in assignments:
      if a.has_overlap:
        overlaps = overlaps + 1

    return overlaps

def part2(assignments):
    overlaps = 0
    for a in assignments:
      if a.has_partial_overlap:
        overlaps = overlaps + 1

    return overlaps


def main():
  with open("input.txt") as file:
    lines = [line.rstrip().split(',') for line in file.readlines()]
    assignments = [Assignment(assign) for assign in lines]
    print(f"part1: {part1(assignments)}")
    print(f"part2: {part2(assignments)}")


if __name__ == "__main__":
  main()