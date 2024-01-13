import random        

def create_files(start, end, max, max_x):
    for i in range(start, end):
        N = random.randint(max//2, max)
        k = 0
        
        filename = f"test{i:02d}.in"
        arr = []
        
        with open(filename, 'w') as file:
            for j in range(N):
                x = random.randint(1, max_x)
                y = random.randint(x, max_x)
                k += y - x + 1
                arr.append((x, y))
                if k > 1000000000:
                    N = j
                    break
            k = random.randint(k//2, k)
            file.write(f"{N} {k}\n")
            for x, y in arr:
                if N == 0:
                    break
                file.write(f"{x} {y}\n")
                N -= 1

            print(f"File {filename} created.")

if __name__ == "__main__":
    #create_files(2, 11, 10, 10000)
    create_files(11, 21, 100, 100000)
    create_files(21, 31, 200, 1000000)
    create_files(31, 41, 500, 10000000)
    create_files(41, 51, 1000, 1000000000)
