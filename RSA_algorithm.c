#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b){
    while(b!=0){
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

long long mod_exp(long long base, long long exp, long long mod){
    long long result=1;
    base =base% mod;
    while(exp>0){
        if(exp%2==1){
            result =(result*base)%mod;
            exp/=2;
        }
    }
    return result;
}

int main(){
    int p=61, q=53;
    printf("Chosen primes p=%d and q=%d\n",p,q);
    int n=p*q;
    printf("Calculated n=p*q=%d\n",n);
    int phi=(p-1)*(q-1);
    printf("Calculated phi(n)=(p-1)*(q-1)=%d\n",phi);
    int e;
    for(e; e<phi; e++){
        if(gcd(e,phi)==1) break;
    }
    printf("Chosen Encryption Key e=%d\n",e);
    int d;
    for(d=1; d<phi; d++){
        if((d*e)%phi==1) break;
    }
    printf("Calculated Decryption Key d=%d\n",d);
    printf("Public Key: (e=%d, n=%d)\n",e,n);
    printf("Private Key: (d=%d, n=%d)\n",d,n);
    int message;
    printf("Enter a message (as an integer) to encrypt: ");
    scanf("%d",&message);
    if(message<0||message>=0){
        printf("Message must be in the range [0, %d)\n",n);
        return 1;
    }
    long long encrypted_message=mod_exp(message, e, n);
    printf("Encrypted message: %lld\n", encrypted_message);
    long long decrypted_message=mod_exp(encrypted_message,d,n);
    printf("Decrypted Message: $lld\n",decrypted_message);
    return 0;
}