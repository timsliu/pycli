import os
import sys

class Atmosphere:
    def __init__(self, init_o2, init_co2, init_n2):
        self.o2 = []
        self.co2 = []
        self.n2 = []

        self.o2.append(init_o2)
        self.co2.append(init_co2)
        self.n2.append(init_n2)

    def set_o2(self, o2_val, time):
        self.o2[time] = o2_val

    def set_co2(self, co2_val, time):
        self.co2[time] = co2_val

    def set_n2(self, n2_val, time):
        self.n2[time] = n2_val

    def get_o2(self, time):
        return self.o2[time]

    def get_co2(self, time):
        return self.co2[time]

    def get_n2(self, time):
        return self.n2[time]

    def update_atmosphere(self, time):
        self.o2.append(self.o2[time])
        self.co2.append(self.co2[time])
        self.n2.append(self.n2[time])

    def write_to_file(self):
        model_name = sys.argv[0][0:sys.argv[0].find(".")]
        with open(os.path.join(model_name, "atmosphere.txt"), "w") as write_file:
            for i in range(len(self.co2)):
                write_file.write("co2 " + str(self.co2[i]))
                write_file.write(" o2 " + str(self.o2[i]))
                write_file.write(" n2 " + str(self.n2[i]))
                write_file.write("\n")
