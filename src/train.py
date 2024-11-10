"""
Trainer:
Entrenar el modelo y guardarlo para que C++ pueda levantarlo.
"""

import librosa
from argparse import ArgumentParser

if __name__ == '__main__':
            
      # Parseo y validación de argumentos
      parser = ArgumentParser(description='c++ args')    
      parser.add_argument(
            '-dataset',
            type=str,
            required=True,
            help='dirección con el train/test data (archivos y clasificaciones)')
      
      parser.add_argument(
            '-results',
            type=str,
            required=True,
            help='dirección donde dejar el modelo')
      args = parser.parse_args();
      srcFolder = args.dataset 
      dstFolder = args.results

      # Lectura del dataset


      # # Split dataset
      # x_train, x_test, y_train, y_tests = train_test_split(songs_vector, expected, 0.8)

      # # build model
      # model = buildModel()

      # # train model
      # model.train()

      # # test model
      # testModel(model, srcFolder)

      # # save model
      # saveModel(model, dstFolder)