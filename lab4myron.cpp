#include <iostream>;
#include <cstdlib>;
#include <ctime>;
using namespace std;
void perm(int mas[][100],int a[],int n,int *chpe){
	int sum=0;
	for (int i=0;i<n-1;i++)
    { 
       sum=sum+mas[a[i]][a[i+1]];
       cout<<mas[a[i]][a[i+1]]<<" ";
    }
    cout<<mas[a[n-1]][a[0]]<<endl; 
    sum=sum+mas[a[n-1]][a[0]];
    
    if (sum<*chpe) *chpe=sum;
    cout<<"The cost of the way "<<sum<<endl;
}

void greed(int n,int mas[][100],int s,int *chgr){
	int min=101,dig=0,kol=1,m[100],num,k=0,ch[100],sum=0;
	m[-1]=s;ch[-1]=s;dig=s;
	for(int i=1;i<=n;i++){
		min=101;
		for(int j=1;j<=n;j++){
			k=0;
			for(int z=-1;z<kol;z++)
			    if (mas[dig][j]==m[z] || j==ch[z]) k=1;
	        if (mas[dig][j]<min && mas[dig][j]!=0 && k==0) {min=mas[dig][j];num=j;}
		}
		m[kol]=min;
		ch[kol]=num;
		dig=num;
		if (i==n) {m[kol]=mas[dig][s];min=m[kol];dig=s;ch[kol]=s;} 
		sum=sum+m[kol];
		kol++;
		cout<<min<<" "<<dig<<" ";
	}
	*chgr=sum;
	cout<<sum<<endl;
}

void alert(int n,int mas[][100]){
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
    	    cout<<mas[i][j]<<" ";
		}
		cout<<endl;
	}
}

void gen(int n,int mas[][100]){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if (i==j) mas[i][j]=0; 
			else if (j>i) mas[i][j]=1+rand()%+(100-1); else mas[i][j]=mas[j][i];
		}
	}
}

void swap(int a[], int i, int j)
{
  int s = a[i];
  a[i] = a[j];
  a[j] = s;
}

bool NextSet(int a[], int n)
{
  int j = n - 2;
  while (j != -1 && a[j] >= a[j + 1]) j--;
  if (j == -1)
    return false; 
  int k = n - 1;
  while (a[j] >= a[k]) k--;
  swap(a, j, k);
  int l = j + 1, r = n - 1;
  while (l<r)
    swap(a, l++, r--);
  return true;
}

void Print(int a[], int n)  
{
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;
}

int main(){
	int n,s,k,mas[100][100],a[100],chgr,chpe=10000;
	srand(time(0));
	cin>>n;
	cin>>s;
	cin>>k;
	for(int i=0;i<k;i++){
	    if (n>20) break;
		unsigned int start_time =  clock();
		gen(n,mas);
	    alert(n,mas);
	    cout<<endl;
		greed(n,mas,s,&chgr);
		unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        cout<<"A greedy method took "<<search_time<<" ms to compile"<<endl;
        cout<<endl;
        start_time =  clock();
		for (int i = 0; i < n; i++)
           a[i] = i + 1;
        Print(a, n);
        perm(mas,a,n,&chpe);
        while (NextSet(a, n)) {
	       Print(a, n);
	       perm(mas,a,n,&chpe);
	    }
	    end_time = clock();
        search_time = end_time - start_time;
        cout<<"Generating all permutations took "<<search_time<<" ms to compile"<<endl;
        cout<<"Let's compare them"<<endl;
        cout<<"Greedy algorithm-"<<chgr<<endl;
        cout<<"Permutations-"<<chpe<<endl;
    }
}
