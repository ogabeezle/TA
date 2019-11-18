import math

def findMax(arr1, exit, arr):
    n=len(arr1)
    arr1.sort()
    exit.sort()

    guest=0
    maxi=0
    i=0
    j=0

    for k in range(-20000,20001):
        if arr[k+20000]:
            continue
        while i<n and arr1[i]+0.0000001<=k:
            i+=1
            guest+=1
        while j<n and exit[j]+0.0000001<k:
            j+=1
            guest-=1
        maxi = max(guest,maxi)
    return maxi

tc=int(input())
while tc>0:
    arr = [False]*40005
    group = {}
    done = [False]*10001
    n, w, v = input().split(" ")
    print(n,w,v)
    n=int(n)
    w=int(w)
    v=int(v)
    for i in range(n):
        x, t, a = input().split(" ")
        x=int(x)
        t=int(t)
        a=int(a)
        arr[x+20000] = True
        if not done[t]:
            done[t]=True
            group[t]=[]
        group[t].append((x,a))

    maxi=0
    for it in group:
        ti=it
        if w - (ti*v)>0:
            continue
        vh = math.sqrt(1-(w/(ti*v)*w/(ti*v)))*v
        vhr = -vh
        temp=group[it]
        start=[]
        end=[]
        startr=[]
        endr=[]
        for i in temp:
            xi=i[0]
            ai=i[1]
            vih = w*math.tan(ai*math.pi/60.0/180)
            print(math.tan(ai*math.pi/60/180)+0.00000001)
            print(vih, vh)
            if vih-vh<0:
                xt = (xi+vih - vh *ti)
                start.append(xt)
                end.append(xi)
            else:
                xt = (xi+vih - vh *ti)
                start.append(xi)
                end.append(xt)
            if vih-vhr<0:
                xt = (xi+vih - vhr *ti)
                startr.append(xt)
                endr.append(xi)
            else:
                xt = (xi+vih - vhr *ti)
                startr.append(xi)
                endr.append(xt)
        maxi = max(maxi,findMax(start,end,arr))
        maxi = max(maxi,findMax(startr,endr,arr))
    print(maxi)
    tc-=1