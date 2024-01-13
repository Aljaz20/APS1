import random        

def create_files(start, end, max):
    for i in range(start, end):
        N = random.randint(max//2, max)
        M = random.randint(max//2, max)
        x = random.randint(0, max)
        y = random.randint(0, max)
        z = random.randint(0, max)
        
        filename = f"test{i:02d}.in"
        
        with open(filename, 'w') as file:
            
            file.write(f"{x} {y} {z}\n")
            prva = ""
            druga = ""
            for j in range(N):
                prva += chr(random.randint(97, 122))
            for j in range(M):
                druga += chr(random.randint(97, 122))
            prva = prva.upper()
            druga = druga.upper()
            file.write(f"{prva}\n")
            file.write(f"{druga}\n")

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(3, 11, 100)
    create_files(11, 51, 1000)
