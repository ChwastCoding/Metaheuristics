from os import stat
from numpy import average
from scipy import stats


def readCSV(filename):
  with open(filename) as file:
    return [[int(word) for word in line.split(",")[:-1]]
            for line in file.readlines()]


def rotate(data):
  return [[line[i] for line in data] for i in range(len(data[0]))]


def tripleWilcoxon(files, timeindex):
  data = [rotate(readCSV(file))[timeindex] for file in files]

  _, p1 = stats.wilcoxon(data[0], data[1])
  _, p2 = stats.wilcoxon(data[1], data[2])
  _, p3 = stats.wilcoxon(data[2], data[0])

  return [p1, p2, p3], [average(d) for d in data]


iter_no_aspiration = [
    "invert_no_aspiration.csv", "insert_no_aspiration.csv",
    "swap_no_aspiration.csv"
]

time_with_aspiration = [
    "invert_with_aspiration_time.csv", "insert_with_aspiration_time.csv",
    "swap_with_aspiration_time.csv"
]


time_no_aspiration = [
    "invert_no_aspiration_time.csv", "insert_no_aspiration_time.csv",
    "swap_no_aspiration_time.csv"
]
def experiment(filename, files):
  with open(filename, "w") as file:
    for i in range(4):
      pro, av = tripleWilcoxon(files, i)
      for p in pro:
        file.write("{},".format(p))
      for p in av:
        file.write("{},".format(p))
      file.write("\n")
      
def aspiration_comparison(with_, without, filename):
  with_data = [rotate(readCSV(file))for file in with_]
  without_data = [rotate(readCSV(file))for file in without] 

  with open(filename, "w") as file:
    for i in range(4):
      for j in range(3):
        if with_data[j][i] == without_data[j][i]:
          file.write("error,")
          continue
        _, p = stats.wilcoxon(with_data[j][i], without_data[j][i])
        file.write("{},".format(p))
      file.write("\n")

    with_average = [[average(row) for row in file] for file in with_data]
    without_average = [[average(row) for row in file] for file in without_data]

    for i in range(4):
      for j in range(3):
        a = with_average[j][i]
        b = without_average[j][i]
        print(a, b)
        file.write("{},".format((b - a) / b * 100))
      file.write("\n")

long_term = [
  "invert_with_aspiration_time_lt.csv", "invert_with_aspiration_time_no_lt.csv"
]

def lt_comparison(files, outfile):
  data = [rotate(readCSV(file)) for file in files]

  with open(outfile, "w") as file:
    for i in range(8):
      _, p = stats.wilcoxon(data[0][i], data[1][i])
      file.write("{},".format(p))
    file.write("\n")
    for i in range(8):
      file.write("{},".format(average(data[0][i])))
    file.write("\n")
    for i in range(8):
      file.write("{},".format(average(data[1][i])))
    file.write("\n")
      
  

if __name__ == "__main__":
  lt_comparison(long_term, "long_term_100.csv")
  # aspiration_comparison(time_with_aspiration, time_no_aspiration, "aspiration_comparison.csv")
  # experiment("timenoaspiration.csv", time_no_aspiration)