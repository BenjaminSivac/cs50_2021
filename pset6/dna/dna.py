from sys import argv, exit
import csv


if len(argv) != 3:
    print(f"Usage: python dna.py data.csv sequence.txt")
    exit(1)

csvfile = argv[1]  # argument 1 in vector
textfile = argv[2]  # argument 2 in vector


STR_MaxCount = []

with open(csvfile, 'r') as csvfile:  # open and convert to a dictionary
    reader = csv.DictReader(csvfile)
    person_list = list(reader)

with open(textfile, 'r') as textfile:
    sequence = textfile.readline().rstrip("\n")  # convert to a list


for i in range(1, len(reader.fieldnames)):  # fieldnames identifies sequences.
    STR_list = reader.fieldnames[i]  # an array for repeated sequences of STR strings, turned into a list.
    STR_MaxCount.append(0)

    for j in range(len(sequence)):  # Counter for number of STRs.
        STR_count = 0

        if sequence[j:(j + len(STR_list))] == STR_list:  # if characters are found to match one of the STR strings.
            count = 0

            while sequence[(j + count):(j + count + len(STR_list))] == STR_list:  # Count if it keeps repeating.
                STR_count += 1
                count += len(STR_list)

                if STR_count > STR_MaxCount[i - 1]:  # if larger than the record, overwrite the record with the new value. 
                    STR_MaxCount[i - 1] = STR_count

for i in range(len(person_list)):  # loop through the length of list of persons.
    matches = 0

    for j in range(1, len(reader.fieldnames)):  # inner-loop through the list of STRs.

        if int(STR_MaxCount[j - 1]) == int(person_list[i][reader.fieldnames[j]]):  # maxcount compared to max STR sequences for each individual person. 
            matches += 1

        if matches == (len(reader.fieldnames) - 1):
            print(person_list[i]['name'])
            exit(0)
print("No match")

