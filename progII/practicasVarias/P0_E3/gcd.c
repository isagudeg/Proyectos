int gcd(int n1, int n2) {
    
    if(n1==0){
        return n2;
    }else if(n2==0){
        return n2;
    }
   
    
    n1 = ( n1 > 0) ? n1 : n1;
    n2 = ( n2 > 0) ? n2 : -n2;

    while(n1!=n2){
        if(n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
    return n1;
}
