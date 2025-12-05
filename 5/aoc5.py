import bisect

with open("day_05.txt") as fin:
    ranges, ids = fin.read().strip().split("\n\n")

ranges = [tuple(map(int, line.split("-"))) for line in ranges.split("\n")]
ids = list(map(int, ids.split("\n")))

ans = 0

points = []
for a, b in ranges:
    points.extend([a - 0.5, b + 0.5])

points = sorted(set(points))

good = [False] * len(points)
for a, b in ranges:
    ai, bi = points.index(a - 0.5), points.index(b + 0.5)
    for j in range(ai, bi):
        good[j] = True

print(points)
print(good)

# Query all query indices
for i in range(len(points) - 1):
    if good[i]:
        ans += points[i+1] - points[i]

print(ans)