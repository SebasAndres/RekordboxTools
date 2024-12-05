import argparse
import pandas as pd
import json

def normalize_bpm(bpm):
    if bpm < 80: return bpm * 2
    return bpm

if __name__ == '__main__':
    print("Logging from classifier_tempo.py")

    parser = argparse.ArgumentParser()
    parser.add_argument("--src", required=True)
    parser.add_argument("--dst", required=True)

    args = parser.parse_args()
    src = args.src
    dst = args.dst

    print("> Leyendo features.")    
    features = pd.read_csv(src+"/features.csv")

    print("> Clasificando según features.")    
    categories = {}
    for i, row in features.iterrows():
        filename = row.file
        bpm = int(normalize_bpm(row.bpm))

        category = str(bpm - bpm % 10)+"bpm"
        if category not in categories:
            categories[category] = []
        categories[category].append(filename)

    print("> Guardando clasificacion.")    
    with open(dst + "/classification.json", "w") as json_file:
        json.dump(categories, json_file, indent=4)

