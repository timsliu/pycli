

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

