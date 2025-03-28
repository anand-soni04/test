#include<stdio.h>
#include<math.h>
int modular_exponent(int base, int exp, int mod){
    int result=1;
    base=base%mod;
    printf("Initial base: %d\n",base);
    while(exp>0){
        printf("Current exp: %d, Result: %d, Base: %d\n",exp, result, base);
        if(exp%2==1){
            result=(result*base)%mod;
            printf("Odd exp-> Result updated to %d\n", result);
        }
        else printf("Even exp-> No change in result.\n");
        exp=exp/2;
        printf("Exp divided by 2-> exp updated to %d\n", exp);
        base=(base*base)% mod;
        printf("Base squared-> Base updated to %d\n", base);
    }
    return result;
}
int main(){
    int p, g; //p = prime number & g = primitive root
    int private_key_A, private_key_B, public_key_A, public_key_B;
    printf("Enter a prime number: ");
    scanf("%d",&p);
    printf("Enter a primitive root modulo %d (g): ",p);
    scanf("%d",&g);
    printf("Enter Alice's private key: ");
    scanf("%d",&private_key_A);
    printf("Enter Bob's private key: ");
    scanf("%d",&private_key_B);
    printf("----------------------------------\n");
    printf("Calculating Alice's public key...\n");
    public_key_A=modular_exponent(g, private_key_A, p);
    printf("------------------------\n");
    printf("Alice's public key: %d\n", public_key_A);
    printf("------------------------\n");
    printf("Calculating Bob's public key...\n");
    public_key_B=modular_exponent(g, private_key_B,p);
    printf("------------------------\n");
    printf("Bob's public key: %d\n", public_key_B);
    printf("------------------------\n");
    int shared_secret_A=modular_exponent(public_key_B, private_key_A, p);
    int shared_secret_B=modular_exponent(public_key_A, private_key_B, p);
    printf("\nShared Secret calculated by Alice: %d\n", shared_secret_A);
    printf("Shared Secret calculated by Bob: %d\n", shared_secret_B);
    if(shared_secret_A == shared_secret_B){
        printf("\n-------------------------\n");
        printf("Keys Exchange Successful!");
        printf("\n-------------------------\n");
    }
    else{
        printf("\n--------------------------------------------\n");
        printf("Keys Exchange failed, Secrets do not match...\n");
        printf("----------------------------------------------\n");
    }
    return 0;
}