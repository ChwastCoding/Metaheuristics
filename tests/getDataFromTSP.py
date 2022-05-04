from distutils.log import debug
import gatherData
import os
import json


def getFilesList():
    return os.popen("ls tests/problems/*.tsp tests/problems/*.atsp").read().split()

def getSolutions(path):
    with open(path, "r") as file:
        return json.loads(file.read())

def solveForFiles(files, solvers, resfile, iterations, k, optimalSolutions=None, limitByNN = False):
    res = {file: {} for file in files}
    res_errors = {file: {} for file in files}
    res_avg = {solver: 0 for solver in solvers}

    def dataEntry(solver, file, k = 1, start = 0, additionalOptions = ""):
        return gatherData.gatherDataEntry(solver, "--from-file {}".\
            format(file) + additionalOptions, k=k,start=start, verbose=False)
    
    if optimalSolutions != None:
        for file in files:
            res[file]["optimal"] = optimalSolutions[file.split(".")[0].split("/")[-1]]

    for file in files:
        addOpts = ""
        if limitByNN:
            addOpts = " --step-limit {}".format(dataEntry("NN", file)[1])
        
        for solver in solvers:
            print("Solving: {} {}".format(solver, file))
            if solver == "2Opt" or solver == "kRandom":
                path = 0
                for _ in range(iterations):
                    path += dataEntry(solver, file, k, 0, addOpts)[0]
                path /= iterations
                res[file][solver] = path
            else:
                res[file][solver] = dataEntry(solver, file, k, 0, addOpts)[0]
            if optimalSolutions != None:
                optimalError =  (res[file]["optimal"] - res[file][solver])\
                    / res[file]["optimal"]
                res_errors[file][solver] = optimalError
                res_avg[solver] += optimalError
            
    if optimalSolutions != None:
        for solver in solvers:
            res_avg[solver] /= len(files)
        with open(resfile + "errors.json", "w") as file:
            file.write(json.dumps(res_errors, indent=2))

        with open(resfile + "erros_avg.json", "w") as file:
            file.write(json.dumps(res_avg, indent=2))

    with open(resfile + ".json", "w") as file:
        file.write(json.dumps(res, indent=2))
    return res


def solutionsToJSON(inFile, resFile):
    with open(inFile) as file:
        lines = file.readlines()
        res = {}
        for line in lines:
            words = line.split()
            res[words[0] if words[0][-1] != ":" else words[0][:-1]] = int(words[-1])
        with open(resFile, "w") as jsonFile:
            jsonFile.write(json.dumps(res, indent=2))

if __name__ == "__main__":
    files = getFilesList()
    # optimals = getSolutions("solutions.json")
    # res = solveForFiles(files, gatherData.solvers, "unlimited_solutions.json", 10, 1000, optimals)
    # res = solveForFiles(files, gatherData.solvers, "limited_solutions.json", 10, 1000, optimals, True)
    