import random        

def create_files(start, end, max):
    for i in range(start, end):
        N = random.randint(max//2, max)
        
        filename = f"test{i:02d}.in"
        
        with open(filename, 'w') as file:
            
            file.write(f"{N}\n")
            for _ in range(N):
                for _ in range(8):
                    x = random.randint(-10000, 10000)
                    file.write(f"{x} ")
                file.write("\n")
           

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(2, 11, 100)
    create_files(11, 51, 1000)
