import random
import string
import os

def generate_test_file(file_number, X, words):
    filename = f"test{file_number:02d}.in"
    with open(filename, 'w') as file:
        
        N = random.randint(1, X)
        file.write(f"{N}\n")

        # Generate N lines with a unique word and a unique number
        used_words = random.sample(words, N)
        used_numbers = random.sample(range(1, 1000000), N)
        sum = 0
        sum1 = 0
        for i in range(N):
            sum += len(used_words[i])
            file.write(f"{used_words[i]} {used_numbers[i]}\n")
        M = random.randint(1, X)

        file.write(f"{M}\n")
        # Use words from the set used_words for the next M lines, generate new ones if needed
        for _ in range(M):
            num = random.randint(0,100)
            if num < 10:
                word = generateRandomWord(30)
            else:
                word = used_words[random.randint(0,N-1)]
                word_len = len(word)
                word = word[:random.randint(1, word_len)]
            sum1 += len(word)
            file.write(f"{word}\n")

    if sum > 1000000 or sum < X*2 or sum1 > 1000000:
        os.remove(filename)
        generate_test_file(file_number, X, words)
    else:
        print(f"Datoteka {filename} je bila ustvarjena. SUM: {sum}   SUM1: {sum1}")

def generate_unique_word(used_words, words):
    word = random.choice(words)
    while word in used_words:
        word = random.choice(words)

    used_words.add(word)
    return word

def generateRandomWord(max):
    min = 1
    # Generates a random word with a random length between min and max
    length = random.randint(min, max)
    word = ""
    for _ in range(length):
        word += chr(random.randint(97, 122))
    return word

def generate_unique_number(used_numbers, N):
    number = random.randint(1, N)
    while number in used_numbers:
        number = random.randint(1, N)
    used_numbers.add(number)
    return number

if __name__ == "__main__":
    trenutna_delovna_mapa = os.getcwd()
    nova_pot = os.path.join(trenutna_delovna_mapa, '..', '..')
    nova_pot_do_datoteke = os.path.join(nova_pot, 'SLObesede.txt')

    with open(nova_pot_do_datoteke, 'r') as file:
        words = file.read().splitlines()
    for i in range(2, 11):
        generate_test_file(i, 1000, words)
    for i in range(11, 21):
        generate_test_file(i, 10000, words)
    for i in range(21, 36):
        generate_test_file(i, 100000, words)
    for i in range(36, 51):
        generate_test_file(i, 200000, words)
