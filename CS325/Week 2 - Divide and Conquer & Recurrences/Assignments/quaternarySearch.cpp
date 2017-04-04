// A recursive ternary search function. It returns location of x in
// given array arr[l..r] is present, otherwise -1

#include <iostream>

using namespace std;

int ternarySearch(int arr[], int l, int r, int x)
{
if (r >= l)
{
		int mid1 = l + (r - l)/3;
		int mid2 = mid1 + (r - l)/3;

		// If x is present at the mid1
		if (arr[mid1] == x) return mid1;

		// If x is present at the mid2
		if (arr[mid2] == x) return mid2;

		// If x is present in left one-third
		if (arr[mid1] > x) return ternarySearch(arr, l, mid1-1, x);

		// If x is present in right one-third
		if (arr[mid2] < x) return ternarySearch(arr, mid2+1, r, x);

		// If x is present in middle one-third
		return ternarySearch(arr, mid1+1, mid2-1, x);
}
// We reach here when element is not present in array
return -1;
}

int quaternarySearch(int arr[], int l, int r, int x){

if(r >=0){
    int q1 = l + (r-1)/4;
    int q2 = q1 + (r-1)/4;
    int q3 = q2 + (r-1)/4;

    if(arr[q1]==x){
        return q1;
    }
    if(arr[q2]==x){
        return q2;
    }
    if(arr[q3]==x){
        return q3;
    }

    if(arr[q1] > x){
        return quaternarySearch(arr, l, q1-1, x);
    }
    if(arr[q2] > x){
        return quaternarySearch(arr, q1, q2-1, x);
    }
    if(arr[q3] > x){
        return quaternarySearch(arr, q2, q3-1, x);
    }
    return quaternarySearch(arr, q3, r, x);

}

return -1;


}




int main(){

    int x[9] = {1,2,3,4,5,6,7,8,9};

    //cout << ternarySearch(x, 0, 9, 8);

    cout << quaternarySearch(x, 0, 8, 1) << endl;
    cout << quaternarySearch(x, 0, 8, 2) << endl;
    cout << quaternarySearch(x, 0, 8, 3) << endl;
    cout << quaternarySearch(x, 0, 8, 4) << endl;
    cout << quaternarySearch(x, 0, 8, 5) << endl;
    cout << quaternarySearch(x, 0, 8, 6) << endl;
    cout << quaternarySearch(x, 0, 8, 7) << endl;
    cout << quaternarySearch(x, 0, 8, 8) << endl;
    cout << quaternarySearch(x, 0, 8, 9) << endl;


}


