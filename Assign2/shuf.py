#!/usr/bin/python

import random, sys
import argparse

class randline:

    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close() 
    def chooseline(self):
        return random.choice(self.lines)
    def shuffle(self):
        random.shuffle(self.lines)
        
def main():
    version_msg = "%(prog)s 2.0"
    usage_msg = """\n%(prog)s [OPTIONS]... FILE
%(prog)s -e [OPTIONS]... [ARG]
%(prog)s -i LO-HI [OPTION]...
"""

    parser = argparse.ArgumentParser(prog= 'shuf', usage=usage_msg,description = 'Generate random permutations')
    parser.add_argument('--version', action='version', version=version_msg)
    parser.add_argument('input_file',nargs='?',default="")
    parser.add_argument("-e","--echo",nargs='+',action="store",
                        dest="echo",default="",
                        help="treat each ARG as an input line")
    parser.add_argument("-i","--input-range",action="store",
                        dest="input_range", default="",
                        help= "treat each number LO through HI as an input line")
    parser.add_argument("-n","--head-count",action="store",
                        dest="head_count",default = sys.maxsize,type=int,
                        help="output at most COUNT lines")
    parser.add_argument("-r","--repeat",action="store_true",
                        dest="repeat",default=False,
                        help="output lines can be repeated")
    args = parser.parse_args()
    try:
        head_count = int(args.head_count)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(head_count))
    if head_count < 0:
        parser.error("negative count: {0}".
                     format(head_count))
    listX=[args.echo,args.head_count,args.input_file,args.input_range,args.repeat]
    match listX:
        case ['', head_count, '','',repeat]|['',head_count,'-','',repeat]:
            args.input_file=""
            input= sys.stdin.readlines()
            random.shuffle(input)
            n=0
            i=0
            while i < len(input):
                if args.head_count<=n:
                    break
                sys.stdout.write(str(input[i]).strip()+'\n')
                n+=1
                i+=1
                if args.repeat==True:
                    i=0
                    random.shuffle(input)
                    
        case ['',head_count,'', input_range,repeat]:
            try:
                start,end = args.input_range.split("-")
            except:
                parser.error("invalid input range: {0}".format(args.input_range))
            if end<start:
                parser.error("invalid input range: {0}".format(args.input_range))
            start=int(start)
            end=int(end)+1
            list2 = []
            list2.extend(range(start,end))
            random.shuffle(list2)
            n=0
            i=0
            while i < len(list2):
                if args.head_count<=n:
                    break
                sys.stdout.write(str(list2[i])+'\n')
                n+=1
                i+=1
                if args.repeat==True:
                    i=0
                    random.shuffle(list2)
 
        case [echo,head_count,'','',repeat]:
            if args.echo!="":
                listT=args.echo
                random.shuffle(listT)
                n=0
                i=0
                while i < len(listT):
                    if args.head_count<=n:
                        break
                    sys.stdout.write(str(listT[i])+'\n')
                    n+=1
                    i+=1
                    if args.repeat==True:
                        i=0
                        random.shuffle(listT)
      
        case ['',head_count,input_file,'',repeat]:
            input_file = args.input_file
            if args.input_file!="":
                try: 
                    generator = randline(input_file)
                    if args.repeat==False:
                        generator.shuffle()
                        for i, line in enumerate(generator.lines):
                            if head_count<=i:
                                break
                            sys.stdout.write((generator.lines[i]).strip()+'\n')
                    else:
                        for i in range(head_count):
                            sys.stdout.write(generator.chooseline().strip()+'\n')
                except IOError as err:
                    errno, strerror =err.args
                    parser.error("I/O error({0}): {1}".
                                 format(errno, strerror))

if __name__ == "__main__": main()
