import cs50

x = cs50.get_int("x: ") # if u want 2 different libraries that may collide with eachother.
y = cs50.get_int("y: ")

if x<y:
    print("x is less than y")
elif x>y:
    print("x is greater than y")
else:
    print("x is equal to y")
