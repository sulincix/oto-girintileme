#!/usr/bin/python
#kullanim: cat kaynak_kod | pyton oto-girintileme.py > yeni_kaynak_kod
#C/C++ Java Php gibi dillerde gecerlidir. python gibi dillerde kullanmayiniz
line="\n"
newline=""
i=0
skipnot=0
word=""
while (1==1):
    line=raw_input()
    newline=""
    line=line.replace("\n","")
    line=line.replace("\t","")
    if("{" in line):
        i=i+1
    if("}" in line):
        i=i-1
    j=0
    clc=0
    while (j!=len(line)):
        if "for" in line:
            skipnot=2
        rep=0
        if  clc ==0:
            if " " in line[j] or "\t" in line[j]:
                j=j+1
            else:
                clc=1
        if  '"' in line[j]:
            if rep==0:
                rep=1
            else:
                rep=0
        if rep==0:
            if ";" in line[j]:
                if skipnot != 0:
                    skipnot=skipnot-1
                    word = line[j]
                else:
                    word = line[j] + "\n"
            else:
                word=line[j]
            newline=newline+word
        else:
            newline=newline+line[j]
        j=j+1
    newline=newline.replace("\n","")
    print "\t"*i+newline
