// Hope you read the readme file

#include<bits/stdc++.h>
typedef long double ld;
using namespace std;

// Data sets
const int n=569,m=30;
ld x[n][m];
ld w[m],b;
ld bestw[m],bestb=0;
ld y[n];
ld predicted_value[n];
ld dj_dw[m],dj_db=0;
ld mxacc=0;
vector<ld> accuracy_history;

//Settings for gradient descent
int iterations=1000001;
ld alpha=0.00001;

ld sigmoid(ld z){
	ld one=1;
	ld sig=one/(one+exp(-z/1000));
	return sig;
}

void gradient_descent(){
	ld prediction,z;
	for(int i=0;i<n;i++){
		z=b;
		for(int j=0;j<m;j++) z+=w[j]*x[i][j];
		prediction=sigmoid(z);
		dj_db+=prediction-y[i];
		for(int j=0;j<m;j++) dj_dw[j]+=(prediction-y[i])*x[i][j];
	}
}

ld Accuracy(){
	ld acc=0;
	for(int i=0;i<n;i++) acc+=(predicted_value[i]==y[i]);
	acc*=100;
	acc/=n;
	return acc;
}

void final_value(){
	ld prediction,z;
	for(int i=0;i<n;i++){
		z=b;
		for(int j=0;j<m;j++) z+=w[j]*x[i][j];
		prediction=sigmoid(z);
		predicted_value[i]=(prediction>=0.5);
	}
}

void letsgoo(){
	cout<<"Mean(w) and b are :-\n\n";
	ld cost;
	for(int i=0;i<iterations;i++){
		gradient_descent();
		for(int j=0;j<m;j++) w[j]-=alpha*dj_dw[j];
		b-=dj_db;
		final_value();
		ld acc=Accuracy();
		if(acc>mxacc){
			mxacc=acc;
			bestb=b;
			for(int j=0;j<m;j++) bestw[j]=w[j];
		}
		accuracy_history.push_back(mxacc);
		if(i%(iterations/10)==0){
			ld mean = 0;
			for(int j=0;j<m;j++) mean+=bestw[j];
			mean/=m;
			cout<<fixed<<setprecision(4)<<mean<<" "<<bestb<<"\nAccuracy: "<<mxacc<<"\n\n";
		}
	}
}

int main(){
	freopen("data_notepad.txt","r",stdin);
	freopen("Output.txt","w",stdout);
	for(int i=0;i<n;i++){
		char p;
		cin>>p;
		y[i]=(p=='M');
		for(int j=0;j<m;j++) cin>>x[i][j];
	}
	letsgoo();
	
	cout<<fixed<<setprecision(4)<<"Accuracy: "<<mxacc<<"\n\n";
	cout<<fixed<<setprecision(15)<<"b: "<<bestb<<"\n\n";
	cout<<"The value of w[i]:-\n\n";
	for(int i=0;i<m;i++){
		cout<<fixed<<setprecision(15)<<bestw[i]<<"\n";
	}
	
	b=bestb;
	for(int j=0;j<m;j++) w[j]=bestw[j];
	final_value();
	cout<<"\nWrong Answer on Test Case:-\n";
	for(int i=0;i<n;i++) if(predicted_value[i]!=y[i]) cout<<i+1<<") "<<predicted_value[i]<<" "<<y[i]<<"\n";
	
	freopen("Training_history.txt","w",stdout);
	for(int i=0;i<iterations;i++){
		cout<<accuracy_history[i]<<"\n";
	}
	
	return 0;
}
