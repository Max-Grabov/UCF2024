def solve(p, a, b, points):
    for i in range(p):
        c = int((i ** 3 + a * i + b)) % p

        if c == 0:
            #points.append((i, 0))
            print(f"{i} {0}")
            continue

        remainder = pow(c, (p - 1) // 2, p) #int((c ** ((p - 1) // 2))) % p

        if remainder == p - 1:
            continue

        sol1 = pow(c, (p + 1) // 4, p) #int((c ** ((p + 1) // 4))) % p
        sol2 = p - sol1

        if(sol1 < sol2):
            #points.append((i, sol1))
            #points.append((i, sol2))
            print(f"{i} {sol1}")
            print(f"{i} {sol2}")

        else:
            #points.append((i, sol2))
            #points.append((i, sol1))
            print(f"{i} {sol2}")
            print(f"{i} {sol1}")

def main():
    inputs = input().split(" ")

    p = int(inputs[0])
    a = int(inputs[1])
    b = int(inputs[2])
    points = []

    solve(p, a, b, points)

    # for point in points:
    #     print(f"{int(point[0])} {int(point[1])}")
main()