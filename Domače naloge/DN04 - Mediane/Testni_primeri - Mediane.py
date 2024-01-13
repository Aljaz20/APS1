import random        

def create_files(start, end, max):
    for i in range(start, end):
        N = random.randint(max//2, max)
        
        filename = f"test{i:02d}.in"
        
        with open(filename, 'w') as file:
            
            file.write(f"{N}\n")
            for _ in range(N):
                x = random.randint(0, 1000000000)
                file.write(f"{x}\n")           

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(2, 11, 100)
    create_files(11, 21, 1000)
    create_files(21, 51, 10000)
