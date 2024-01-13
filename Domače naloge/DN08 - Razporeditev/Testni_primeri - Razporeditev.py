import random        

def create_files(start, end, max):
    for i in range(start, end):
        N = random.randint(max//10, max)
        x = random.randint(1, 10)
        min = 1000 if N//x >= 1000 else N//x
        M = random.randint(min, N//x + 1)
        
        filename = f"test{i:02d}.in"
        with open(filename, 'w') as file:
            file.write(f"{N} {M}\n")
            for _ in range(M):
                a = random.randint(1, N)
                b = random.randint(1, N)
                while a == b:
                    b = random.randint(1, N)
                file.write(f"{a} {b}\n")

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(3, 11, 1000)
    create_files(11, 31, 10000)
    create_files(31, 51, 40000)
