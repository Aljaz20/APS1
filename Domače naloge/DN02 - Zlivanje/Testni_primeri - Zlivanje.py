import random        

def create_files(start, end, max):
    for i in range(start, end):
        N = random.randint(max//2, max)
        K = random.randint(2, 10)
        A = random.randint(1, 20)
        
        filename = f"test{i:02d}.in"
        
        with open(filename, 'w') as file:
            
            file.write(f"{N} {K} {A}\n")
            for _ in range(N):
                x = random.randint(0, 1000000000)
                file.write(f"{x}\n")        

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(2, 11, 100)
    create_files(11, 21, 10000)
    create_files(21, 31, 10000)
    create_files(31, 41, 10000)
    create_files(41, 51, 10000)
