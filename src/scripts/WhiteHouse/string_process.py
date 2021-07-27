empty_char = ['\t',' ','\n']

def exist(list,target):
    for i in list:
        if i == target:
            return True
    return False

def remove_empty(str):
    ret = ""
    flag = False
    for i in str:
        if exist(empty_char,i) :
            if not flag:
                flag = True
                ret += i
        else:
            flag = False
            ret += i
    
    start = 0
    end = len(ret)-1
    
    while exist(empty_char,ret[start]):
        start += 1
    while exist(empty_char,ret[end]):
        end -= 1

    return ret[start:end+1]

a = input()
print("#"+remove_empty(a)+"#")