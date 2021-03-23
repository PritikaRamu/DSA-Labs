#include "merge.h"

void merge(Element Ls1[], int sz1, Element Ls2[], int sz2, Element Ls[]){
	int i=0,j=0,k=0;

	while(i<sz1 && j<sz2){
		if(Ls1[i].cg<Ls2[j].cg){
			Ls[k++]=Ls1[i++];
		}
		else{
			Ls[k++]=Ls2[j++];
		}
	}

	if(i==sz1){
		while(j<sz2){
			Ls[k++]=Ls2[j++];		
		}
	}

	if(j==sz2){
		while(i<sz1){
			Ls[k++]=Ls1[i++];		
		}
	}

}

void mergeRec(Element Ls[],int l, int r){
    
    if(l<r){
        int mid = (l+r)/2;
        mergeRec(Ls,l,mid);
        mergeRec(Ls,mid+1,r);
        Element temp[r-l+1];
        merge(Ls+l, mid-l+1, Ls+mid+1, r-mid, temp);
        for(int i=0;i<r-l+1;i++){
			Ls[l+i]=temp[i];
		}
    }
}

void mergeIter(Element Ls[],int n){ 				//referred gfg
	int mid,right;
	for(int curr_size=1;curr_size<n;curr_size*=2){
		for(int start=0;start<n;start+=2*curr_size){
			mid = min(start+curr_size-1,n-1);
			right = min(start+2*curr_size-1,n-1);
			Element temp[right-start+1];
			merge(Ls+start,mid-start+1,Ls+mid+1,right-mid,temp);
			for(int i=0;i<right-start+1;i++){
				Ls[start+i]=temp[i];
			}
		}
	}
}

