import argparse
import librosa
import os
import pandas as pd

MFCC_COUNT = 13

def extractFeatures(src, valid_extensions):
    print("> Obteniendo features de", src)
    files = get_files_with_valid_extensions(src, valid_extensions)
    headers = ["file", "bpm", "spectral_centroid"] + [f"mfcc_{i+1}" for i in range(MFCC_COUNT)]
    dataset = [headers]
    for file in files:
        try:
            y, sr = librosa.load(os.path.join(src, file), sr=None)
            vector = vectorize_tracks(file, MFCC_COUNT, y, sr)
            dataset.append(vector)            
        except Exception as e:
            print(f"Error procesando {file}: {e}")
    return dataset

def vectorize_tracks(file, MFCC_COUNT, y, sr):
    bpm = librosa.beat.beat_track(y=y, sr=sr)[0][0]
    spectral_centroid = librosa.feature.spectral_centroid(y=y, sr=sr).mean()
    mfcc = librosa.feature.mfcc(y=y, sr=sr, n_mfcc=MFCC_COUNT).mean(axis=1)
    return [file, bpm, spectral_centroid] + list(mfcc)

def get_files_with_valid_extensions(src, extensiones_validas):
    return [
        file for file in os.listdir(src)
        if os.path.isfile(os.path.join(src, file)) and os.path.splitext(file)[1].lower() in extensiones_validas
    ]

def saveFeatures(features, dst):
    print("> Guardando features en", dst)
    df = pd.DataFrame(features[1:], columns=features[0])  # Crear un DataFrame de pandas
    df.to_csv(os.path.join(dst, "features.csv"), index=False)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--src", required=True)
    parser.add_argument("--dst", required=True)

    args = parser.parse_args()
    src = args.src
    dst = args.dst

    features = extractFeatures(src,valid_extensions = [".mp3", ".wav"])
    saveFeatures(features, dst)    


if __name__ == '__main__':
    main()