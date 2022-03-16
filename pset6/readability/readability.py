from cs50 import get_string
import string


text = get_string("Text: ")

c_words = 1 
c_letters = c_sentences = 0


for letter in text:
    if letter == "!" or letter == "?" or letter == ".":
        c_sentences += 1
    elif letter in string.punctuation:  # commas, semicolon etc are disregarded
        continue
    elif letter in string.whitespace:
        c_words += 1
    else:
        c_letters += 1

grade = round((0.0588 * (100 * (c_letters / c_words))) - (0.296 * (100 * (c_sentences / c_words))) - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")