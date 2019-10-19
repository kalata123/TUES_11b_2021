def drop_breaks(floor, kill_floor):
    return 1 if floor >= kill_floor else 0


def main(kill_floor=99):
    building_floors = 100
    # eggs = 2
    j = 0
    for i in range(0, building_floors, 14):
        i -= j  # max-floor # 39 from 27 to 39 = 12 = i
        if drop_breaks(i, kill_floor):
            a = i - (14 - j)
            while (a < i):
                # pdb.set_trace()
                a = i - (14 - j)
                if drop_breaks(a, kill_floor):
                    return a
                j += 1
        j += 1


if __name__ == "__main__":
    print(f"kill_floor is {main(45)}")
