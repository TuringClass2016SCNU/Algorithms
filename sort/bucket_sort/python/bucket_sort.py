if __name__ == '__main__':
    l = []
    n = int(input())
    for i in range(0, n):
        l.append(float(input()))
    res = [[] for _ in range(0, n)]
    for g in range(0, n):
        res[int(n*l[g])].append(l[g])
    for g in range(0, n):
        res[g].sort()
    for i in range(n):
        for j in range(len(res[i])):
            print(res[i][j], end=' ')
    print()
