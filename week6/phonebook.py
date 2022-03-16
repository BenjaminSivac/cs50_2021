from cs50 import get_string

people = {                              # Dictionary
    "Brian": "+1-617-495-1000",
    "David": "+1-949-468-2750"
    }
    
name = get_string("Name: ")
if name in people:
    print(f"Number: {people[name]}") # index into it by a string to get a value
# not linear search, but hash.