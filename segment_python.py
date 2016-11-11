words=['share','as','a','sale','bla','other','any','sha','sh']
wdict={}
best=[]

def scan(input,i,prevarr):
    global best
    arr=list(prevarr)
    # If array is empty, we automatically add first letter
    if len(arr)<1:
        arr.append(input[0:1])
        return scan(input,i+1,arr)
    # If no more input is available, evaluate the solution
    if i>=len(input):
        # Is the last word a valid word
        if wdict.has_key(arr[-1]):
            # Is there a current best solution?
            if len(best)==0:
                best=arr      # No current solution so select this one
            elif len(arr[0])>len(best[0]):
                best=arr      # If new solution has a longer first word
        return best
    # If the last word in the sequence is a valid word, we can add a space and try
    if wdict.has_key(arr[-1]):
        arr.append(input[i:i+1])
        scan(input,i+1,arr)
        del arr[-1]
    # Add a letter to the last word and recurse
    arr[-1]=arr[-1]+input[i:i+1]
    return scan(input,i+1,arr)

def main():
    for w in words:
        wdict[w]=True
    res=scan('shareasasale',0,[])
    print res

if __name__ == '__main__':
    main()