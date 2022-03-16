from cs50 import get_string
import sys
import re

ccnumber = get_string("Number: ")
check = []

if (len(ccnumber)) not in (13, 15, 16):
    print("INVALID")
    sys.exit(1)

for i in range(len(ccnumber)):
    if i % 2 == (-2+len(ccnumber)) % 2:  # if modulo equals 1 (a check for every other digit)
        digits = str(int(ccnumber[i]) * 2)  # multiply the first and every other digit
        for j in range(len(digits)):
            check.append(int(digits[j]))  # add the digits to the check
    else:
        check.append(int(ccnumber[i]))  # add digit to the check

total = str(sum(check))

if re.search("0$", total):  # Luhn Algorithm
    if re.search("^5(1|2|3|4|5)", ccnumber):
        print("MASTERCARD")
    elif re.search("^3(4|7)", ccnumber):
        print("AMEX")
    elif ccnumber[0] == str(4):
        print("VISA")
else:
    print("INVALID")
