#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class mono{
    public:
        int coe;
        int pow;
        mono(int _coe=-1,int _pow=-1){
            coe=_coe;
            pow=_pow;
        }
};
class poly{
    public:
        mono *point;
        int size;
        int maxpow=0;
    public:
        poly(mono data[]={}){
            size=sizeof(data)/8;
            point=new mono[size];
            for(int pos=0;pos<size;pos++){
                point[pos].coe=data[pos].coe;
                point[pos].pow=data[pos].pow;
                if(point[pos].pow>maxpow)maxpow=point[pos].pow;
            }
            simplify();
        }
        poly(poly *data){
            size=data->size;
            maxpow=data->maxpow;
            for(int pos=0;pos<size;pos++){
                point[pos].coe=data->point[pos].coe;
                point[pos].pow=data->point[pos].pow;
                if(point[pos].pow>maxpow)maxpow=point[pos].pow;
            }
            simplify();
        }
        poly(mono data){
            size=1;
            point=new mono[1];
            point[0].coe=data.coe;
            point[0].pow=data.pow;
        }
        poly(int data){
            size=1;
            point=new mono[1];
            point[0].coe=data;
            point[0].pow=0;
        }
        ~poly(){
            delete [] point;
        }
    public:
        void simplify(){
            mono *temp=new mono[maxpow+1];
            for(int pos=maxpow;pos>=0;pos--){
                temp[pos].pow=pos;
                for(int posn=0;posn<size;posn++)
                    if(point[posn].pow==posn)
                        temp[pos].coe+=point[posn].coe;
            }
            size=maxpow+1;
            for(int pos=0;pos<=maxpow;pos++){
                point[pos].coe=temp[maxpow-pos].coe;
                point[pos].pow=temp[maxpow-pos].pow;
            }
            delete [] temp;
        }
    public:
        friend poly operator+(const poly&,const poly&);
        poly operator*(const poly&);
        friend poly operator*(const int&,const poly&);
        poly operator/(const poly&);
        poly operator%(const poly&);
        friend ostream & operator<<(ostream&,const poly&);
};
poly operator+(const poly& one,const poly& two){
    int maxsize=max(one.size,two.size);
    mono *sum=new mono[maxsize];
    int sum_maxpow=(one.maxpow,two.maxpow);
    for(int pos=sum_maxpow;pos>=0;pos--){
        sum[pos].pow=pos;
        for(int posn=0;posn<maxsize;posn++)
            if(one.point[posn].pow==posn)
                sum[pos].coe+=one.point[posn].coe;
    }
    for(int pos=sum_maxpow;pos>=0;pos--)
        for(int posn=0;posn<maxsize;posn++)
            if(two.point[posn].pow==posn)
                sum[pos].coe+=two.point[posn].coe;
    poly result(sum);// *
    delete sum;
    return result;
}
poly poly::operator*(const poly& multiplier){ //not finished.  also: "this" refers to the first one.

}
poly operator*(const int& num,const poly& one){
    poly result=one;
    for(int pos=one.maxpow;pos>=0;pos--)
        result.point[pos].coe*=num;
    return result;
}
poly poly::operator/(const poly& divisor){ //not finished! try to check it.
    mono *sum=new mono[this->size-1]; //
    poly *_this=this;
    int lastpow=_this->maxpow-divisor.maxpow;
    for(int pos=_this->size-1;pos>=0;pos--){
        int dividecoe=_this->point[pos].coe/divisor.point[divisor.size-1].coe;
        sum[pos-(divisor.size-1)].coe=dividecoe; sum[pos-(divisor.size-1)].pow=pos-(divisor.size-1); //could 'this' change?
        for(int posn=divisor.size-1;posn>=0;posn--)
            _this->point[pos+(size-posn)].coe-=divisor.point[posn].coe*dividecoe;
    }
    _this->~poly();
    poly result(sum);
    delete sum;
    return result;
}
poly poly::operator%(const poly& divisor){ //not finished.
    poly *_this=this;
    int lastpow=_this->maxpow-divisor.maxpow;
    for(int pos=_this->size-1;pos>=0;pos--){
        int dividecoe=_this->point[pos].coe/divisor.point[divisor.size-1].coe;
        for(int posn=divisor.size-1;posn>=0;posn--)
            _this->point[pos+(size-posn)].coe-=divisor.point[posn].coe*dividecoe;
    }
    _this->~poly();
    return _this;
}
ostream & operator<<(ostream& os,const poly& out){
    os<<out.point[out.size-1].coe;
    if(out.point[out.size-1].pow!=0) os<<"x^"<<out.point[out.size-1].pow;
    for(int pos=out.size-2;pos>=0;pos--){
        if(out.point[pos].coe>0) os<<'+';
        os<<out.point[pos].coe;
        if(out.point[pos].pow!=0) os<<"x^"<<out.point[pos].pow;
    }
    return os;
}
