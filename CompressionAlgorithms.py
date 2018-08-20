"""
Author:       Gabriella Uwadiegwu (Restructured/Refactored)
Source:       rosettacode.org (For Algorithms)
"""

from heapq import heappush, heappop, heapify
from collections import defaultdict
import string,random, time

#THIS PROJECT IS DONE USING PYTHON2.7, USE OF PYTHON 3.x iIS NOT ADVISED DUE TO SIGNIFICANT SYNTAX CHANGES

class CompressionAlgorithms():

    #Global variables for data set initialization. Strings and numbers
    ten=""
    ten_l = [] #because LZW will be using list data structure this is analogous to array in java or c++
    hundred=""
    hund_l = []
    thousand=""
    thous_l = []
    ten_thousand=""
    ten_thous_l = []

    time_elapsed = 0
    operations = 0


    def generate_data(self):
        """
        Generates random letters for above sizes
        complexity: O(n)
        :return: None
        """
        for i in range(0, 10):
            word = random.choice(string.letters)
            self.ten += word
            self.ten_l.append(word)

        for i in range(0, 100):
            word = random.choice(string.letters)
            self.hundred += word
            self.hund_l.append(word)

        for i in range(0, 1000):
            word = random.choice(string.letters)
            self.thousand += word
            self.thous_l.append(word)

        for i in range(0, 10000):
            word = random.choice(string.letters)
            self.ten_thousand += word
            self.ten_thous_l.append(word)

    """
    Run-Length Encoding(RL)
    """
    def RLEncode(self,input_string):
        """
        complexity: O(n)
        :param input_string: String of data text to be compressed
        :return: A list of Tuple/Set of a word and it's compressed value
        """
        self.time_elapsed = 0 #timer
        self.operations = 0 #operation counter
        start_time = time.time()
        count = 1
        prev = ''
        lst = []
        for character in input_string: #all characters in input_string
            if character != prev:
                self.operations+=1
                if prev:
                    self.operations += 1
                    entry = (prev, count)
                    lst.append(entry)
                    # print lst
                count = 1
                prev = character
            else:
                self.operations+=1
                count += 1
        else: #executing this else statement after the for loop indicates that there was no
                # break in the loop and its statements should be executed
            self.operations += 1
            try:
                entry = (character, count)
                lst.append(entry)
                self.time_elapsed = time.time() - start_time
                return (lst, 0)
            except Exception as e:
                print("Exception encountered {e}".format(e=e))
                return (e, 1)


    """
    HuffMan Coding (HF)
    """
    def HFEncode(self, symbtofreq):
        """
        :The heapq library complexity: O(log n) for push and O(log n) for pop and O(n) for heapify
        :complexity of HFEncode: O(nlogn)
        :param symb2freq: String of frequency?
        :return:
        """
        """Huffman encode the given dict mapping symbols to weights"""
        self.operations = 0
        self.time_elapsed = 0   #timer
        start_time = time.time()

        heap = [[wt, [sym, ""]] for sym, wt in symbtofreq.items()]
        #heap variable is a list (aka array) of [weight, [Symbol, ""]] for all the sets of weights and symbol in symbtofreq dictionary (aka Map)

        heapify(heap)
        self.operations +=1 #for heapify
        while len(heap) > 1:
            lo = heappop(heap) #pop smallest item form heap
            hi = heappop(heap) #same
            for pair in lo[1:]: #item in position 1 i.e second element
                pair[1] = '0' + pair[1] #keep pair as is
            for pair in hi[1:]:
                pair[1] = '1' + pair[1]
            heappush(heap, [lo[0] + hi[0]] + lo[1:] + hi[1:]) #push into heap [lo[0] + hi[0]] + lo[1:] + hi[1:]
            self.operations += 3 # for two heappop and heappush
            self.time_elapsed = time.time() - start_time    #total time
        return sorted(heappop(heap)[1:], key=lambda p: (len(p[-1]), p))
        #In iterating through sorted function, keep popping pairs form the heap
        #p is the unknown function (Should be a list) and gets its -1 postions and the list p
        #which is passed into the function p which will then return a key. So
        #Huffman code is retuned

    """
    Lempel-Ziv-Welch Algorithm(LZW), Compressed
    runtime:
    """
    def LZWCompress(self, uncompressed):
        """
        :complexity: O(n)
        :param uncompressed: String of data text
        :return: list of the compressed data
        """
        """Compress a string to a list of output symbols."""

        self.operations = 0
        self.time_elapsed = 0   #timer
        start_time = time.time()
        # Build the dictionary.
        dict_size = 256
        dictionary = dict((chr(i), i) for i in xrange(dict_size)) #O(n)
        #dictionary gets ascii of all possible symbols,words, letters and keep them as a dictionary/map e.g {'0':48}
        # in Python 3: dictionary = {chr(i): i for i in range(dict_size)}

        w = ""
        result = []
        for c in uncompressed: #O(n)
            wc = w + c
            if wc in dictionary:
                w = wc
                self.operations += 1
            else:
                result.append(dictionary[w]) #puts ascii value of w into results
                # Add wc to the dictionary.
                dictionary[wc] = dict_size
                dict_size += 1
                w = c
                self.operations += 1

        # Output the code for w.
        if w:
            result.append(dictionary[w])
            self.operations += 1
        self.time_elapsed = time.time() - start_time #total time
        return result


if __name__ == "__main__": #main function

    instance = CompressionAlgorithms()
    instance.generate_data() #Create data sets

    #DATA SET USED ARE RANDOM LETTERS CONCATENATED, FROM SIZE 10 -> 10000

    """
    LZW Encoding Output
    """
    #Data size of size 10
    compressed = instance.LZWCompress(instance.ten_l)
    print "Compressed Lempel-Ziv-Welch size 10\n", compressed
    print "\nTime Taken:", instance.time_elapsed
    print "\nLZW Operation count:", instance.operations, "\n"


    #Data size of size 100
    compressed = instance.LZWCompress(instance.hund_l)
    print "Compressed Lempel-Ziv-Welch size 100\n", compressed
    print "\nTime Taken:", instance.time_elapsed
    print "\nLZW Operation count:", instance.operations, "\n"


    #Data size of size 1000
    compressed = instance.LZWCompress(instance.thous_l)
    print "Compressed LZW size 1000\n", compressed
    print "\nTime Taken:", instance.time_elapsed
    print "\nLZW Operation count:", instance.operations, "\n"


    #Data size of size 10000
    compressed = instance.LZWCompress(instance.ten_thous_l)
    print "Compressed Lempel-Ziv-Welch size 10000\n", compressed
    print "\nTime Taken:", instance.time_elapsed
    print "\nLZW Operation count:", instance.operations, "\n"


    """
    Huffman Coding Output
    """
    #Data size of size 10
    symbol_to_frequency = defaultdict(int)
    for ch in instance.ten:
        symbol_to_frequency[ch] += 1
    huff = instance.HFEncode(symbol_to_frequency)
    print "HUFFMAN DATA SET OF 10\nSymbol\t\tWeight\t\tHuffman Code\n"
    for p in huff:
        print "%s\t\t\t%s\t\t\t%s" % (p[0], symbol_to_frequency[p[0]], p[1])
    print "\nTime Taken:", instance.time_elapsed
    print "\nHUFFMAN Operation count:", instance.operations, "\n"

    #Data size of size 100
    symbol_to_frequency = defaultdict(int)
    for ch in instance.hundred:
        symbol_to_frequency[ch] += 1
    huff = instance.HFEncode(symbol_to_frequency)
    print "HUFFMAN DATA SET OF 100\nSymbol\t\tWeight\t\tHuffman Code\n"
    for p in huff:
        print "%s\t\t\t%s\t\t\t%s" % (p[0], symbol_to_frequency[p[0]], p[1])
    print "\nTime Taken:", instance.time_elapsed
    print "\nHUFFMAN Operation count:", instance.operations, "\n"

    #Data size of size 1000
    symbol_to_frequency = defaultdict(int)
    for ch in instance.thousand:
        symbol_to_frequency[ch] += 1
    huff = instance.HFEncode(symbol_to_frequency)
    print "HUFFMAN DATA SET OF 1000\nSymbol\t\tWeight\t\tHuffman Code\n"
    for p in huff:
        print "%s\t\t\t%s\t\t\t%s" % (p[0], symbol_to_frequency[p[0]], p[1])
    print "\nTime Taken:", instance.time_elapsed
    print "\nHUFFMAN Operation count:", instance.operations, "\n"

    #Data size of size 10000
    symbol_to_frequency = defaultdict(int)
    for ch in instance.ten_thousand:
        symbol_to_frequency[ch] += 1
    huff = instance.HFEncode(symbol_to_frequency)
    print "HUFFMAN DATA SET OF 10000\nSymbol\t\tWeight\t\tHuffman Code\n"
    for p in huff:
        print "%s\t\t\t%s\t\t\t%s" % (p[0], symbol_to_frequency[p[0]], p[1])
    print "\nTime Taken:", instance.time_elapsed
    print "\nHUFFMAN Operation count:", instance.operations, "\n\n\n\n"

    """
    Run-length Encoding  output
    """
    #Data size of size 10
    value = instance.RLEncode(instance.ten)
    print "\nTime Taken:", instance.time_elapsed
    print "\nRLE Operation count:", instance.operations, "\n"
    if value[1] == 0:
        print("Encoded value is {}".format(value[0]))

    #Data size of size 100
    value = instance.RLEncode(instance.hundred)
    print "\nTime Taken:", instance.time_elapsed
    print "\nRLE Operation count:", instance.operations, "\n"
    if value[1] == 0:
        print("Encoded value is {}".format(value[0]))

    #Data size of size 1000
    value = instance.RLEncode(instance.thousand)
    print "\nTime Taken:", instance.time_elapsed
    print "\nRLE Operation count:", instance.operations, "\n"
    if value[1] == 0:
        print("Encoded value is {}".format(value[0]))

    #Data size of size 10000
    value = instance.RLEncode(instance.ten_thousand)
    print "\nTime Taken:", instance.time_elapsed
    print "\nRLE Operation count:", instance.operations, "\n"
    if value[1] == 0:
        print("Encoded value is {}".format(value[0]))
