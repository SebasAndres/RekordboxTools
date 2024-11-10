"""
Trainer:
- 1. Leer los archivos desde la carpeta con el Dataset.
- 2. Leer el .csv con la clasificación de esos archivos.
- 3. Entrenar el modelo y guardarlo para que C++ pueda levantarlo.
"""

import librosa
from argparse import ArgumentParser

if __name__ == '__main__':
            
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

      print("hola :)")

      # # song_vector[track_id] = vector para la cancion de id track_id
      # songs_vector = vectorizeTracks(dir=srcFolder+"/files") 

      # # Y[track_id] = Expected classification for track_id
      # expected = getExpectedOutputs(dir=srcFolder+"/files")

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