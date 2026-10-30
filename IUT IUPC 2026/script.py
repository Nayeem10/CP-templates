#!/usr/bin/env python
import os
Base = './Codes/'
def ProcessFile(f, name, W):
    if f.endswith((".txt", ".cpp")):
        W.write("\\begin{lstlisting}\n")
        with open(f) as CPP:
            for lines in CPP:
                W.write(lines)
        W.write("\\end{lstlisting}\n")


def ProcessDir(dir, name, depth, W):
    for subdir in sorted(os.listdir(dir)):
        if subdir == 'desktop.ini':
            continue
        s = '\\'
        for i in range(depth):
            s += 'sub'
        s += 'section{'
        s += os.path.splitext(subdir)[0].split(']')[-1]
        s += '}\n'
        W.write(s)
        pth = os.path.join(dir, subdir)
        if os.path.isfile(pth):
            ProcessFile(pth, subdir, W)
        else : 
            ProcessDir(pth, subdir, depth + 1, W)

def get_info():
    print("Enter Team Name")
    team = input()
    print("Enter Uni Name")
    uni = input()
    print("Enter Number of Columns")
    cols = input()
    print("Which Orientation Do You Want?\n1. Portrait\n2. Landscape")
    x = int(input())
    ort = "portrait" if x == 1 else "landscape"
    print("What font size?\n1. 10\n2. 11\n3. 12\n4. 13")
    x = int(input())
    fs = '10'
    if x == 2: fs = '11'
    if x == 3: fs = '12'
    if x == 4: fs = '13'
    return (team, uni,cols, ort, fs)
    
def load():
    if os.path.getsize('cache.txt') == 0:
        data = get_info()
        with open('cache.txt', 'w') as cache:
            for str in data:
                cache.write(str + '\n')
        return data
    print("Do you want to load saved data?\n1. Yes\n2. No")
    x = int(input())
    if x == 1:
        with open('cache.txt', 'r') as cache:
            team = cache.readline().rstrip()
            uni = cache.readline().rstrip()
            cols = cache.readline().rstrip()
            ort = cache.readline().rstrip()
            fs = cache.readline().rstrip()
        return (team, uni, cols, ort, fs)
    else:
        data = get_info()
        with open('cache.txt', 'w') as cache:
            for str in data:
                cache.write(str + '\n')
        return data
        


def main():
    s = ""
    data = load()
    team, uni, cols, ort, fs = data
    with open('out.tex', 'w') as W:
        W.write('\\newcommand\\TEAM{' + team + '}\n')
        W.write('\\newcommand\\UNI{' + uni + '}\n')
        W.write('\\newcommand\\COLS{' + cols + '}\n')
        W.write('\\newcommand\\ORT{' + ort + '}\n')
        W.write('\\newcommand\\FSZ{' + fs + '}\n')
        with open("start.tex") as F:
            for line in F:
                W.write(line)

        ProcessDir(Base, '', 0, W)
        with open("end.tex") as F:
            for line in F:
                W.write(line)
if __name__ == '__main__':
    main()
