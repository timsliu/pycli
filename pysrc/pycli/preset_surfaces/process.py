import sys

if __name__ == "__main__":
    infile = sys.argv[1]
    f = open(infile, "r")
    lines = f.readlines()
    f.close()

    with open("out.txt", "w") as out:
        for i in range(len(lines)):
            print(i)
            if i < 90 or i > 810:
                # replace with all ice
                out.write(lines[i].replace("0", "2").replace("1", "2"))
            else:
                print("hello!")
                out_line = lines[i].replace("0", "2")
                out_line = out_line.replace("1", "0")
                out_line = out_line.replace("2", "1")
                out.write(out_line)
