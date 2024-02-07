#!/usr/bin/python3
import re
import sys

def main():
    file = open("wordlist.txt", "r")
    my_arr=[]
    for linex in file:
        linex = linex.rstrip()
        my_arr.append(linex)
    while True:
        print( "\nEnter format: WORDX|YGNYG")
        format= input()
        if format=='x':
            exit(1)
        word= format.split("|")
        word[0]=word[0].lower()
        word[1]=word[1].upper()
        i=0
        for i in range(5):
            if word[1][i]=='G':
                temp= list('.....')
                temp[i]=word[0][i]
                regex="".join(temp)
                for line in my_arr:
                    if not re.search(regex, line):
                        my_arr[my_arr.index(line)]="x"
            if word[1][i]=='Y':
                regex=word[0][i]
                for line in my_arr:
                    if not re.search(regex, line) or line[i]==regex:
                        my_arr[my_arr.index(line)]="x"
            if word[1][i]=='N':
                regex=word[0][i]
                for line in my_arr:
                    if word[0].count(regex)>1:
                        temp= list('.....')
                        temp[i]=word[0][i]
                        regex="".join(temp)
                    if re.search(regex, line):
                        my_arr[my_arr.index(line)]="x"
                

        for line in my_arr:
            if line !="x":
                print (line)
if __name__=="__main__":main()