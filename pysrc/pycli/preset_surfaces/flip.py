import sys

if __name__ == "__main__":
    infile = sys.argv[1]
    f = open(infile, "r")
    lines = f.readlines()
    f.close()

    with open("out.txt", "w") as out:
        for line in reversed(lines):
            out.write(line)

