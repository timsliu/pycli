from pycli.model import Model

def new_model(name):
    if name == "default":
        return Model(default = True)
    else:
        return Model(default = False)
    