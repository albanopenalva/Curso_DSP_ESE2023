# -*- coding: utf-8 -*-
"""

Sistemas de Adquisición y Procesamiento de Señales
Facultad de Ingeniería - UNER

Módulo que contiene funciones para el cálculo de la FFT, pensado para 
ejemplificar el uso de funciones en Python.

Autor: Juani Cerrudo
Fecha: Marzo 2022

"""


import numpy as np
from glob import glob
from os.path import basename

def process_data(folder):
    #fs = 500
    #tiempo = 2
  
    dataset = None
    classmap = {}
    #folder = 'dataset'

    for class_idx, filename in enumerate(glob('%s/*.csv' % folder)):       
        class_name = basename(filename)[:-4]
        print(filename)
        classmap[class_idx] = class_name
        samples = np.loadtxt(filename, dtype=float, delimiter=',')
        labels = np.ones((len(samples), 1)) * class_idx
        print("Se encontraron {} eventos de la clase:  {}".format(len(samples), class_name))
        samples = np.hstack((samples, labels))
        dataset = samples if dataset is None else np.vstack((dataset, samples))

    return dataset, classmap                