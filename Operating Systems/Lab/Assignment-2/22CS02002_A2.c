#include<stdio.h>
#include<pthread.h>
#define f(n) for(int i=0;i<(n);i++)

const int INF=1e9;
int a[1000],sorted[1000];

pthread_t thread1, thread2;
struct end{
    int l,r;
};
void merge(int l,int r){
    int mid=(l+r)>>1;
    int len1=mid-l+1,len2=r-mid;
    int b[len1+1],c[len2+1];
    f(len1) b[i]=a[l+i];
    f(len2) c[i]=a[mid+1+i];
    b[len1]=c[len2]=INF;
    int p=0,q=0,cur=l;
    while(p<len1 || q<len2){
        if(b[p]<=c[q]) a[cur]=b[p++];
        else a[cur]=c[q++];
        cur++;
    }
}
void* mergeSort(void *arg){
    struct end st=*(struct end *)arg;
    int l=st.l,r=st.r;
    if(!(l^r) || l>r) return NULL;
    int mid=(l+r)>>1;
    struct end st1,st2;
    st1.l=l;st1.r=mid;
    st2.l=mid+1;st2.r=r;

    mergeSort(&st1);
    mergeSort(&st2);

    merge(l,r);
}
void main(){
    int n;
    printf("Enter the number of integers n: ");
    scanf("%d",&n);
    printf("Enter the array: ");
    f(n) scanf("%d",&a[i]);
    struct end st1,st2;
    int mid=(n-1)>>1;
    st1.l=0;st1.r=mid;
    st2.l=mid+1;st2.r=n-1;

    pthread_create(&thread1, NULL, mergeSort, &st1);
    pthread_create(&thread2, NULL, mergeSort, &st2);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    merge(0,n-1);

    printf("Final sorted array: ");
    f(n) printf("%d ",a[i]);
    printf("\n");
}