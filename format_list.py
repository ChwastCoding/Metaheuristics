import os

path = "http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/{}/{}.{}.gz"
"http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/atsp/br17.atsp.gz"

with open("file_list_atsp") as file:
    for line in file.readlines():
        try:
            words = line.split()
            if (words[2] == "EUC" or words[2] == "MATRIX")\
                and int(words[1]) < 4000:
                print("df")
                os.system("wget {}".format(path.format("atsp", words[0], "atsp")))
                # os.system("wget {}".format(path.format("atsp", words[0], "atsp")))
        except:
            continue
    
    files = os.popen("ls *.tsp.gz *.atsp.gz").read().split()
    print(files)
    for file in files:
        os.system("mv {} tests/problems/".format(file))
        os.system("gzip -d tests/problems/{}".format(file))
