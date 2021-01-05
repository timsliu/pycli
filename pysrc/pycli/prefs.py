# prefs.py
#
# This file contains a list of allowed preferences and the preferences class
# for specifying model parameters


import sys
import os
import json

# default preference dictionary 
DEFAULT = {"backend_model": "simple",
           "save_intermeds": True,
           "colors": "RdBu_r",
           "verbose": True}


# list of allowed preferences
ALLOWED = {"backend_model": ["simple", "accel"],           # backend climate model
         "save_intermeds": [True, False],                  # save intermediate temps
         "verbose": [True, False],                         # verbose mode
         "colors":                                         # color schemes 
            ['Greys', 'Purples', 'Blues', 'Greens', 'Oranges', 'Reds',
            'YlOrBr', 'YlOrRd', 'OrRd', 'PuRd', 'RdPu', 'BuPu',
            'GnBu', 'PuBu', 'YlGnBu', 'PuBuGn', 'BuGn', 'YlGn',
            'binary', 'gist_yarg', 'gist_gray', 'gray', 'bone', 'pink',
            'spring', 'summer', 'autumn', 'winter', 'cool', 'Wistia',
            'hot', 'afmhot', 'gist_heat', 'copper',
            'PiYG', 'PRGn', 'BrBG', 'PuOr', 'RdGy', 'RdBu',
            'RdYlBu', 'RdYlGn', 'Spectral', 'coolwarm', 'bwr', 'seismic',
            'twilight', 'twilight_shifted', 'hsv',
            'Pastel1', 'Pastel2', 'Paired', 'Accent',
            'Dark2', 'Set1', 'Set2', 'Set3',
            'tab10', 'tab20', 'tab20b', 'tab20c',
            'flag', 'prism', 'ocean', 'gist_earth', 'terrain', 'gist_stern',
            'gnuplot', 'gnuplot2', 'CMRmap', 'cubehelix', 'brg',
            'gist_rainbow', 'rainbow', 'jet', 'turbo', 'nipy_spectral',
            'gist_ncar', 'hot_r', 'Accent_r', 'PuBuGn_r', 'flag_r', 'cubehelix_r',
            'BuGn_r', 'summer_r', 'twilight_shifted_r', 'rainbow_r', 'gist_yarg_r',
            'bone_r', 'ocean_r', 'gist_earth_r', 'gnuplot_r', 'twilight_r', 'gray_r',
            'Paired_r', 'autumn_r', 'PuBu_r', 'copper_r', 'Pastel2_r', 'spring_r',
            'GnBu_r', 'Pastel1_r', 'binary_r', 'tab20b_r', 'tab20_r', 'gnuplot2_r',
            'BrBG_r', 'gist_ncar_r', 'BuPu_r', 'Greys_r', 'PuRd_r', 'gist_gray_r',
            'RdBu_r', 'gist_heat_r', 'winter_r', 'nipy_spectral_r', 'Purples_r',
            'Oranges_r', 'Greens_r', 'RdPu_r', 'terrain_r', 'YlOrRd_r', 'RdGy_r',
            'Set3_r', 'CMRmap_r', 'YlOrBr_r', 'gist_rainbow_r', 'brg_r', 'prism_r',
            'seismic_r', 'hsv_r', 'afmhot_r', 'Wistia_r', 'OrRd_r', 'cool_r', 
            'PuOr_r', 'bwr_r', 'pink_r', 'Reds_r', 'tab20c_r', 'Set2_r', 'Set1_r',
            'Spectral_r', 'YlGn_r', 'Dark2_r', 'coolwarm_r', 'tab10_r', 
            'RdYlGn_r', 'jet_r', 'PiYG_r', 'turbo_r', 'RdYlBu_r', 'YlGnBu_r',
            'PRGn_r', 'Blues_r', 'gist_stern_r']

    }


class Preferences:
    '''Preference class holds the model configuration preferences such as
    which model to use, whether to save intermediate values, and visualization
    preferences'''

    def __init__(self):
        '''initialization - create dictionary for holding the preferences. Initialize
        to the default settings'''
        self.prefs = DEFAULT

    def set_pref(self, pref_dic):
        '''add new preferences to the preference dictionary. Preferences are passed
        as key-value pairs. Invalid key value pairs are rejected and valid ones are
        added to the preference list. More than one preference can be added at once,
        or multiple preferences can be added'''

        good_prefs = {}      # dictionary with allowed preference settings 
        
        # check all key value pairs in the preference dic
        for key in pref_dic.keys():
            # preference is invalid
            if key not in ALLOWED.keys():
                print("Preference: '{}' not in allowed preferences".format(key))
                print("List of allowed preferences: ", ALLOWED.keys())
            else:
                # setting not an allowed value for the preference
                if pref_dic[key] not in ALLOWED[key]:
                    print("Setting {} not compatible for preference '{}'")
                    print("List of allowed settings for preference '{}': ".format(key), ALLOWED[key])
                # valid key value preference 
                else:
                    good_prefs[key] = pref_dic[key]

        self.prefs = {**self.prefs, **good_prefs}

    def write_preferences(self):
        '''save all preferences to a json file'''
        # find the name of the model - TODO check this works
        model_name = sys.argv[0][0:sys.argv[0].find(".")]

        # write to json file
        with open(os.path.join(model_name, "prefs.json"), "w") as outfile:
            json.dump(self.prefs, outfile)



