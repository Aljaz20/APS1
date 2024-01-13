import random        

def create_files(start, end, max, max_x, koren=0):
    for i in range(start, end):
        if koren == 0:
            N = random.randint(1, max)
            M = max // N + 1
        else:
            N = random.randint(300, 350)
            M = random.randint(300, 350)
        
        filename = f"test{i:02d}.in"
        
        with open(filename, 'w') as file:
            file.write(f"{N} {M}\n")
            for a in range(N):
                x = random.randint(0, max_x)
                file.write(f"{x}")
                for b in range(M-1):
                    x = random.randint(0, max_x)
                    file.write(f" {x}")
                file.write("\n")

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(2, 11, 100, 1000)
    create_files(11, 21, 1000, 1000)
    create_files(21, 31, 10000, 10000)
    create_files(31, 41, 100000, 100000)
    create_files(41, 51, 100000, 100000, 1)
