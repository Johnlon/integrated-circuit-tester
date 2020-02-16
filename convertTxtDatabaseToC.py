#!/usr/bin/python3
#
# Understands the format of the Smark IC Tester database file.
# Converts this into a form that can be used by this tester.
#

import sys
import urllib.request


name = ""
desc = ""
tests=[]
readtests = False

src="https://raw.githubusercontent.com/akshaybaweja/Smart-IC-Tester/master/database.txt"

page = urllib.request.urlopen(src)
databaseTxtResp=page.read().decode("utf-8")

databaseTxt = databaseTxtResp.split("\n")
#databaseTxt = open("database.txt", "r")

chipsDatabaseIno = open("chipsDatabase.h", "w")

for line in databaseTxt:
    line = line.strip()
    if (line.startswith("$")):
        if name != "":
            print("Chip %s" % name)
            chipsDatabaseIno.write("const char CHIP_%s[] PROGMEM = (\"%s:%s\" \\\n" % (name, name, desc))

            for test in tests:
                chipsDatabaseIno.write("\t\":%s:\" \\\n" % test)
            chipsDatabaseIno.write(");\n");

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
