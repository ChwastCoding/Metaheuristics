from fileinput import filename
import json
import os
import scipy.stats as st 
import numpy as np

solvers = ["2Opt", "NN", "ExtNN", "2Opt-NN", "kRandom"]
instanceSize = 100
instance = "--euc2d {}".format(instanceSize)

# data format: objective_function, iterations
def gatherDataEntry(solver, additionalOptions = "", size = 100, k = 1000, start = 0, verbose=False):
    if solver == "NN":
        additionalOptions += (" --starting-node {}".format(start))
    elif solver == "kRandom":
        additionalOptions += (" --k {}".format(k))
    if verbose:
        call = "./build/Metaheurisitics --solver {} --size {} {} 2>/dev/null"\
            .format(solver, size, additionalOptions)
        print(call)
    return [int(x) for x in os.popen("./build/Metaheurisitics --solver {} --size {} {} 2>/dev/null"\
        .format(solver, size, additionalOptions)).read().split(" ")]


def gatherData(fileName = "noLimits", iterations = 100, k = 100, solvers_=solvers, additionalOptions = ""):
    res = {solver: {"dist": [], "iter": []} for solver in solvers_}
    for solver in solvers_: 
        for i in range(iterations):
            entry = gatherDataEntry(solver, additionalOptions=instance +\
                " --seed {}".format(i + 1) + additionalOptions, k=k)
            res[solver]["dist"].append(entry[0])
            res[solver]["iter"].append(entry[1])
    if fileName != "":
        with open(fileName, "w") as resFile:
            resFile.write(json.dumps(res, indent=2))
    return res

def gatherDataLimitMin(fileName = "noLimits", iterations = 100, solvers_=solvers):
    # res = gatherData("", iterations, solvers_=solvers_[:-2])
    # minMedian = min([np.median(np.array([res[solver]["iter"]])) for solver in solvers_[:-2]])
    return gatherData(fileName, iterations, instanceSize, solvers_, " --step-limit {}".format(instanceSize))


def analize(solvers, data):
    res = {}
    for a in range(len(solvers)):
        for b in range(a + 1, len(solvers)):
            solA = solvers[a]
            solB = solvers[b]
            res["{} {}".format(solA, solB)] = [st.wilcoxon(data[solA]["dist"], data[solB]["dist"])]
    return res


def average(filePath, solvers):
    with open(filePath, "r") as file:
        data = json.loads(file.read())
        for solver in solvers:
            avg = sum(data[solver]["dist"]) / len(data[solver]["dist"])
            print(solver + " avg distaace: {}".format(avg)) 


if __name__ == "__main__":
    iterations = 1
    fileName = "iterations_{}_fast_problems_sizes_{}".format(iterations, instanceSize)
    data = gatherData(fileName+".json", iterations, k=1000, solvers_=solvers)
    dataNoLimits = gatherDataLimitMin(fileName + "_no_limit.json", iterations, solvers)
    stats = analize(solvers, data)
    statsNoLimit = analize(solvers, dataNoLimits)
    with open(fileName + "_stats.json", "w") as file:
        file.write(json.dumps(stats, indent=2))
    with open(fileName + "_stats_no_limit.json", "w") as file:
        file.write(json.dumps(statsNoLimit, indent=2))
    average("iterations_100_problems_sizes_100.json", solvers)
    