#!/usr/bin/python

import sys


name = ""
desc = ""
tests=[]
readtests = False

databaseTxt = open("database.txt", "r")
chipsDatabaseIno = open("chipsDatabase.h", "w")

#chipsDatabaseIno.write("const char * chipsDatabase[] = {\n")

for line in databaseTxt:
    line = line.strip()
    if (line.startswith("$")):
        if name != "":
            print("Chip %s" % name)
            chipsDatabaseIno.write("#define CHIP_%s (chip(\"%s\", \"%s\")" % (name, name, desc))
            for test in tests:
                chipsDatabaseIno.write(".scenario(\"%s\")" % test)
            chipsDatabaseIno.write(")\n");

            name = ""
            desc = ""
            tests=[]
            sys.stdout.flush()
            readtests = False

    if (line == "$"):
        break

    if (line.startswith("$")):
        tests=[]
        name = line.replace("$","",1)
        
    else:
        if desc == "":
            desc = line
        else:
            if readtests == False:
                readtests = True
            else:
                tests.append(line)
