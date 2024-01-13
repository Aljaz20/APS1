import random        

def create_files(start, end, max):
    for i in range(start, end):
        M = random.randint(max//2, max)
        N = random.randint(0, 10000)
        
        filename = f"test{i:02d}.in"
        
        with open(filename, 'w') as file:
            
            file.write(f"{M}\n")
            file.write(f"{N}\n")
            for _ in range(N):
                x = random.randint(0, M)
                d = random.randint(0, 1000000000)
                file.write(f"{x} {d}\n")           

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(2, 11, 1000)
    create_files(11, 21, 10000)
    create_files(21, 31, 100000)
    create_files(31, 41, 1000000)
    create_files(41, 51, 1000000000)
