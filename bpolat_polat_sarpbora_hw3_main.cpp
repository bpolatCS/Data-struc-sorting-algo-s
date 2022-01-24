#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

#include <chrono>
using namespace std;


template <class Comparable>
void insertionSort (vector <Comparable> a)
{
	int j;
               // loop over the passes
	for (int p =1;  p < a.size(); p++)
	{
		
		Comparable tmp = a[p];
                            // loop over the elements
		for (j = p; j > 0 && tmp.name < a[j -1].name; j--)
			a[j] = a[j -1];

		a[j] =tmp;
	}
}


inline int leftChild( int i )
{
	return 2*i+1;
}



template <class Comparable>  // for deleteMax // a is the array, i is the position to percolate down from // n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;

    for (tmp=a[i]; leftChild(i) < n; i = child )
    {
		child = leftChild(i);
		if ( child != n-1 && a[ child  ].name < a[ child+1 ].name )
			child++;
		if ( a[child ].name > tmp.name )
			a[i] = a[ child ];
		else
			break;
    } 
    a[ i ] = tmp;
}
 
template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size() -1; j >0; j--)
	{
		swap(a[0], a[j]);    // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}

template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
           

	mergeSort( a, 0, a.size( ) - 1 );
}

         
template <class T>
void mergeSort( vector<T> & a,int left, int right )
{
    if( left < right )
    {
        int center = ( left  + right ) / 2;
        mergeSort( a,  left, center );
        mergeSort( a,  center + 1, right );
        merge( a, left, center, right );
    }
}

template <class T>
void merge(vector<T> &a, int start, int mid, int end)
{
	int start2 = mid + 1;
 
	// If the direct merge is already sorted
	if (a[mid].name <= a[start2].name) 
	{
	return;
	}
 
	// Two pointers to maintain start
	// of both arrays to merge
	while (start <= mid && start2 <= end)
	{
 
		// If element 1 is in right place
		if (a[start].name <= a[start2].name) 
		{
			start++;
		}
		else 
		{
			T value = a[start2];
			int index = start2;
 
			// Shift all the elements between element 1
			// element 2, right by 1.
			while (index != start) 
			{
				a[index] = a[index - 1];
				index--;
			}
			a[start] = value;
 
			// Update all the pointers
			start++;
			mid++;
			start2++;
		}
	}
}




/** Return median of left, center, and right.
    *   Order these and hide the pivot.
    */
template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ].name < a[ left ].name )
		swap( a[ left ], a[ center ] );
    if ( a[ right ].name < a[ left ].name )
		swap( a[ left ], a[ right ] );
    if ( a[ right ].name < a[ center ].name )
		swap( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
* Quicksort algorithm (driver).
*/
template <class Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}


/**
    * Internal insertion sort routine for subarrays
    * that is used by quicksort.
    * a is an array of Comparable items.
    * left is the left-most index of the subarray.
    * right is the right-most index of the subarray.
    */
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp.name < a[ j - 1 ].name; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}


// INTERNAL QUICKSORT

/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );
	// Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ].name < pivot.name ) {}
            while ( pivot.name < a[ --j ].name ) {}
            if ( i < j )
				swap( a[ i ], a[ j ] );
            else
             break;
        }
		
		swap( a[ i ], a[ right - 1 ] );   // Restore pivot

        quicksort( a, left, i - 1 );       // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
		insertionSort( a, left, right );
}

//Up until here functions coppied and pasted from course slides.

template <class Comparable>
vector<int> binarySearch(vector<Comparable> &arr, int l, int r, string x) //basicly, keep indices of elements from main vector and then put those array's into a integer vector. then return it.
{
	vector<int> indexKeeper;
	int right, left;
	
    if (r >= l) 
	{
        int mid = l + (r - l) / 2;

		string toBeSearched = arr[mid].name.substr(0,x.length());

        if (toBeSearched == x)
		{
			indexKeeper.push_back(mid);
			right = mid;
			
			//going left and right of the mid index, we want to take indices of all toBeSearched.
			while ( arr[++right].name.substr(0,x.length()) == x)
			{
				indexKeeper.push_back(right);			
			}
		
			left = mid;
			
			while ( arr[--left].name.substr(0,x.length()) == x)
			{
				indexKeeper.push_back(left);
				
			}
			return indexKeeper;
		}   
  
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (toBeSearched > x)
            return binarySearch(arr, l, mid - 1, x);
  
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
	return indexKeeper;
  
    // We reach here when element is not
    // present in array
 
}



template <class Comparable>
vector<int> sequentialSearch(vector<Comparable> &arr, string x) //basicly, keep indices of elements from main vector and then put those array's into a integer vector. then return it.
{
	vector<int> indexKeeper;
	int right;
	for (int i = 0; i < arr.size(); i++)
	{
		string y= arr[i].name.substr(0,x.length());
		if (arr[i].name.substr(0,x.length()) == x)
		{
			indexKeeper.push_back(i);
			right = i;
			//going only right of the mid index, we want to take indices of all toBeSearched.
			while ( arr[++right].name.substr(0,x.length()) == x)
			{
				indexKeeper.push_back(right);			
			}		
			return indexKeeper;		
		}
	}
	return indexKeeper;
}
  
string ToUpper(string s) //turning strings upper case
// postcondition: s all lower case     
{
	
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = toupper(s[k]);
		
    }
	return s;
}

struct info
{
	string name, rest;

	info() {}
	info(string n, string r): name(n), rest(r) {}

};



int main()
{

	string fileName, word;
	cout<<"Please enter the contact file name: "<<endl;
	cin>>fileName;
	cout<<"Please enter the word to be queried:  "<<endl;
	cin.ignore();
	getline(cin, word);

	ifstream file;

	file.open(fileName.c_str()); //reading data
	string lines;
	string sectionNames= "";
	bool enough = true;
	vector<info> QSList, ISlist, MSList, HSList;

	while (!file.eof()) //writing lines into 4 different list
	{
		getline(file,lines);
		int firstB, secB;
		firstB = lines.find(" ");
		secB = lines.find(" ", firstB+1);
		string name= lines.substr(0,secB);
		string rest = lines.substr(secB+1);

		QSList.push_back(info(name, rest));
		ISlist.push_back(info(name, rest));
		MSList.push_back(info(name, rest));
		HSList.push_back(info(name, rest));	
	}

	cout<<endl;
	cout<<"Sorting the vector copies"<<endl;
	cout<<"======================================"<<endl; //vectors are sorting
	int N=100;
	vector<info>Temp = QSList;
	auto startQS =chrono::high_resolution_clock::now(); //timers starts here until notebooks are fullfilled.
	for (int i = 0; i < N; i++)
	{
		quicksort(QSList);
		QSList = Temp;
	}	
	auto endQS = chrono::high_resolution_clock::now();
	long long timerAVLQS = (endQS-startQS).count() / N;
	cout<<"Quick Sort Time: "<< double(timerAVLQS)<<" Nanoseconds"<<endl;
	quicksort(QSList);

	auto startIS =chrono::high_resolution_clock::now(); //timers starts here until notebooks are fullfilled.
	for (int i = 0; i < 10; i++)
	{
		insertionSort(ISlist);	
		ISlist = Temp;
	}
	auto endIS = chrono::high_resolution_clock::now();
	long long timerAVLIS = (endIS-startIS).count() / 10;
	cout<<"Insertion Sort Time: "<< timerAVLIS<<" Nanoseconds"<<endl;
	insertionSort(ISlist);	
	
	auto startMS =chrono::high_resolution_clock::now(); //timers starts here until notebooks are fullfilled.
	for (int i = 0; i < N; i++)
	{
		mergeSort(MSList);
		MSList = Temp;
	}

	auto endMS = chrono::high_resolution_clock::now();
	long long timerAVLMS = (endMS-startMS).count() / N;
	cout<<"Merge Sort Time: "<< timerAVLMS<<" Nanoseconds"<<endl;
	mergeSort(MSList);
	
	auto startHS =chrono::high_resolution_clock::now(); //timers starts here until notebooks are fullfilled.
	for (int i = 0; i < N; i++)
	{
		heapsort(HSList);
		HSList = Temp;
	}
	auto endHS = chrono::high_resolution_clock::now();
	long long timerAVLHS = (endHS-startHS).count() /N;
	cout<<"Heap Sort Time: "<< timerAVLHS<<" Nanoseconds"<<endl;
	heapsort(HSList);

	cout<<endl<<"Searching for "<<word<<endl;
	cout<<"======================================"<<endl;
	

	//here we search a string in one of the list above
	vector<int> tempList;
	cout<<"Search results for Binary Search:"<<endl;
	auto startBST =chrono::high_resolution_clock::now(); //timers starts here until notebooks are fullfilled.
	for (int i = 0; i < 1000; i++)
		tempList = binarySearch(QSList,0,QSList.size()-1,word); //searched string in whole array/vector
	auto endBST = chrono::high_resolution_clock::now();
	
	
	if (tempList.empty()) //if list is empty then no string found, otherwise print all indicies from base list.
	{	
		cout<<ToUpper(word)<<" does NOT exist in the dataset"<<endl;
	}
	else
	{
		for (int i = 0; i < tempList.size(); i++)
		{
			int index = tempList[i];
			cout<<ToUpper(QSList[index].name)<<" "<<QSList[index].rest<<endl;
		} 	
	}	
	long long timerAVLBST = (endBST-startBST).count() /1000;
	cout<<endl<<"Binary Search Time: "<<timerAVLBST<<" Nanoseconds";



	if (!tempList.empty())
	{
		tempList.clear();
	}


	cout<<endl<<endl<<"Search results for Sequential Search:"<<endl;	
	auto startSST =chrono::high_resolution_clock::now(); //timers starts here until notebooks are fullfilled.
	for (int i = 0; i < 1000; i++)
		tempList = sequentialSearch(QSList,word);
	auto endSST = chrono::high_resolution_clock::now();
	//if list is empty then no string found, otherwise print all indicies from base list.

	if (tempList.empty()) //if list is empty then no string found, otherwise print all indicies from base list.
	{	
		cout<<ToUpper(word)<<" does NOT exist in the dataset"<<endl;
	}
	else
	{
		for (int i = 0; i < tempList.size(); i++)
		{
			int index = tempList[i];
			cout<<ToUpper(QSList[index].name)<<" "<<QSList[index].rest<<endl;
		} 	
	}

	long long timerAVLSST = (endSST-startSST).count() / 1000;
	cout<<endl<<"Sequential Search Time: "<<timerAVLSST<<" Nanoseconds"<<endl;
	


	cout<<"SpeedUp between Search Algorithms"<<endl<<endl;
	cout<<"======================================"<<endl;
	cout<<"(Sequential Search / Binary Search) SpeedUp = "<< double(timerAVLSST)/double(timerAVLBST);

	cout<<endl<<endl<<"SpeedUps between Sorting Algorithms"<<endl;
	cout<<"======================================"<<endl;
	cout<<"(Insertion Sort / Quick Sort) SpeedUp = "<< double(timerAVLIS)/double(timerAVLQS)<<endl;
	cout<<"(Merge Sort / Quick Sort) SpeedUp = "<< double(timerAVLMS)/double(timerAVLQS)<<endl;
	cout<<"(Heap Sort / Quick Sort) SpeedUp = "<< double(timerAVLHS)/double(timerAVLQS)<<endl;
	return 0;
}
