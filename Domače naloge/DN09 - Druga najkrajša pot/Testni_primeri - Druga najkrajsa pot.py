import random        

def create_files(start, end, max):
    for i in range(start, end):
        #N = random.randint(max//2, max)
        #N = 2000
        N = max
        M = N * 10
        
        filename = f"test{i:02d}.in"
        pari = set()
        with open(filename, 'w') as file:
            file.write(f"{N} {M}\n")
            for _ in range(10):
                a = 0
                b = random.randint(1, N-1)
                x = random.randint(1, 10000)
                while a == b or (a,b) in pari:
                    b = random.randint(1, N-1)
                pari.add((a,b))
                file.write(f"{a} {b} {x}\n")
                M -= 1
            for _ in range(M):
                a = random.randint(0, N-1)
                b = random.randint(0, N-1)
                x = random.randint(1, 10000)
                while a == b or (a,b) in pari or (b,a) in pari:
                    a = random.randint(1, N-1)
                    b = random.randint(1, N-1)
                pari.add((a,b))
                file.write(f"{a} {b} {x}\n")

            print(f"File {filename} created.")

def create_files_max(start, end, max):
    for i in range(start, end):
        N = max
        M = N * (N-1) // 2
        if M > 50000:
            M = 50000
        
        filename = f"test{i:02d}.in"
        pari = set()
        with open(filename, 'w') as file:
            file.write(f"{N} {M}\n")
            for a in range(N):
                for b in range(a+1, N):
                    x = random.randint(1, 10000)
                    file.write(f"{a} {b} {x}\n")
                    M -= 1
                    if M == 0:
                        break
                if M == 0:
                    break

            print(f"File {filename} created.")

if __name__ == "__main__":
    create_files(3, 11, 2000)
    create_files(11, 31, 5000)
    create_files(31, 45, 10000)
    create_files(45, 51, 15000)
    #create_files_max(11, 31, 100)
    #create_files(31, 45, 800)
