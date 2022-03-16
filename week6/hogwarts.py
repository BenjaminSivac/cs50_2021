import csv

houses = {
    "Gryffindor": 0,
    "hmm": 0,
    "hmk": 0
}

with open("filename.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        house = row[1]
        houses[house] += 1 #counting the house names in a csv file.
        
for house in houses:
    print(f"{house}: {houses[house]}")