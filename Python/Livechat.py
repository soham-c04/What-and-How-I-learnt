from pickle import *
print('''Instructions:-
1)Open 2 tabs on IDLE. Then using one of them open Livechat.py and using the second one open Livehchat2.py
2)Enter name on one tab press Enter and then Enter name on the other tab.
3)Start chatting.
4)To end the chat type /end and then press Enter.''')
l=[]
lc=open('Livechat.dat','wb')
dump(l,lc)
lc.close()
a=2
b=input('Enter your name: ')
lc=open('Livechat.dat','rb+')
t=load(lc)
lc.seek(0)
t.append([1,b])
dump(t,lc)
lc.close()
zt=0
while zt==0:
    m=input('Me:')
    j=[1,m]
    if m=='/end':
        print('You ended the chat.')
        zt=1
        lc=open('Livechat.dat','rb+')
        t=load(lc)
        t.append(j)
        lc.seek(0)
        dump(t,lc)
    else:
        lc=open('Livechat.dat','rb+')
        t=load(lc)
        if t[0][0]!=1:
            b2=t[0][1]
        else:
            b2=t[1][1]
        t.append(j)
        lc.seek(0)
        dump(t,lc)
        lc.close()
        if zt==1:
            break
        for i in range(a,len(t)):
            if t[i][0]==2:
                if t[i][1]=='/end':
                    zt=1
                    print(b2,' ended the chat.')
                    break
                elif t[i][1]!='':
                    print(b2,': ',t[i][1])
        a=i+1
        lc.close()
                
