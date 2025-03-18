#include <iostream> //for input and output
#include <string> //using strings
#include <fstream> //reading from file
#include <cstdlib> //using random numbers
#include <chrono> //time measuring
#include <set> //DO USUNIECIA
#include <algorithm> //DO USUNIECIA

using namespace std;
template <typename T>
class Sorter {
public:
    /* -----HELP CLASEES----- */
    /**
     *@brief This enum represents different pivots
     *We can categorize pivots by left, right, middle and random
     */
    enum class PivotType {
            LEFT,
            RIGHT,
            MIDDLE,
            RANDOM
        };

    /**
     *  Function that swaps two values of variables with eachother
     * @param a passed by reference, can be of any type
     * @param b passed by reference, can be of any type
     */
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    
    
    
    
    /* -----QUICKSORT----- */
    /**
     * Function that calls the function `quicksort` with pivot type left
     * @param tab pointer to the array of any type
     * @param size size of the array the pointer points at
     */
    long long quicksortLeft(T* tab, int size) {
        auto start = chrono::high_resolution_clock::now();
        quicksort(tab, 0, size - 1, PivotType::LEFT);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);
        return duration.count();
        }

    /**
     * Function that calls the function `quicksort` with pivot type right
     * @param tab pointer to the array of any type
     * @param size size of the array the pointer points at
     */
    long long quicksortRight(T* tab, int size) {
        auto start = chrono::high_resolution_clock::now();
        quicksort(tab, 0, size - 1, PivotType::RIGHT);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);
        return duration.count();
        }
    /**
     * Function that calls the function `quicksort` with pivot type middle
     * @param tab pointer to the array of any type
     * @param size size of the array the pointer points at
     */
    long long quicksortMiddle(T* tab, int size) {
        auto start = chrono::high_resolution_clock::now();
        quicksort(tab, 0, size - 1, PivotType::MIDDLE);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);
        return duration.count();
        }

    /**
     * Function that calls the function `quicksort` with pivot type random
     * @param tab pointer to the array of any type that we want to sort
     * @param size size of the array the pointer points at
     */
    long long quicksortRandom(T* tab, int size) {
        auto start = chrono::high_resolution_clock::now();
        quicksort(tab, 0, size - 1, PivotType::RANDOM);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);
        return duration.count();
        }
    
    /**
     * Function that is an implementation of quicksort algorithm. It divides the array to smaller parts, sorts it and then joins the subarrays to one sorted array. It works only if the left index is smaller than the right index. When left == right, recursion ends. It calls out function `partition`, and then recusively calls out itself for two parts: left of the pivot and right of the pivot.
     * Sort in-place, unstable.
     *
     * @param tab pointer to the array of any type that we want to sort
     * @param left left index, start of the array to sort
     * @param right right index, end of the array to sort
     * @param pivotType type of pivot we want to use from enum `PivotType`
     */
    void quicksort(T* tab, int left, int right, PivotType pivotType) {
        if (left < right) {  // Rekurencyjne sortowanie tylko wtedy, gdy left < right
            int pivot_index = partition(tab, left, right, pivotType);  // Ustal pivot i przeprowadź partycjonowanie
            quicksort(tab, left, pivot_index - 1, pivotType);   // Rekurencyjne sortowanie lewej części tablicy
            quicksort(tab, pivot_index + 1, right, pivotType);  // Rekurencyjne sortowanie prawej części tablicy
        }
    }

    /**
     *Function that is choosing pivot from the array, moves pivot to the end of the array and then sort the array so, that values smaller than pivot are on the left and bigger on the right, then moves pivot to the final place.
     *
     *@param tab pointer to the array of any type that we want to sort
     *@param left left index, start of the array to sort
     *@param right right index, end of the array to sort
     *@param pivotType type of pivot we want to use from enum `PivotType`
     *@return index of pivot after partitioning
     */
    int partition(T* tab, int left, int right, PivotType pivotType) {
        int pivot_index = choosePivot(tab, left, right, pivotType);  // chooses pivot index by pivottype
        T pivot_value = tab[pivot_index]; // gets the value of pivot
        swap(tab[pivot_index], tab[right]); // moves pivot to the end of the array
        int store_index = left; //variable that stores index of the element that shoukd be on the left of pivot

        for (int i = left; i < right; i++) {
            if (tab[i] < pivot_value) {  //if current element is smaller than pivot
                swap(tab[i], tab[store_index]);  //swap the elements
                store_index++;  //increment index of the element that should store pivot
            }
        }

        swap(tab[store_index], tab[right]); //move pivot to the final place
        return store_index;  //return index of pivot
    }

    /**
     * Function that chooses pivot index based on pivot type. 
     * Depending on pivot type, the function selects an appropriate element as the pivot:
     * - **PivotType::LEFT** - selects the leftmost element of he array
     * - **PivotType::RIGHT** - selects the rightmost element of the array
     * - **PivotType::MIDDLE** - selects the middle element of the array
     * - **PivotType::RANDOM** - selects randomly chosen pivot
     *
     * @param tab pointer to the array of any type that we want to sort
     * @param left left index, start of the array to sort
     * @param right right index, end of the array to sort
     * @param pivotType type of pivot we want to use from enum `PivotType`
     *
     * @return index of the element chosen as pivot
     */
    int choosePivot(T* tab, int left, int right, PivotType pivotType) {
        switch (pivotType) {
            case PivotType::LEFT:
                return left;
            case PivotType::RIGHT:
                return right;
            case PivotType::MIDDLE:
                return left + (right - left) / 2;
            case PivotType::RANDOM:
                return left + rand() % (right - left + 1);
            default:
                return right;
        }
    }
    
    
    
    
    /* -----HEAP SORT----- */
    /**
     * Function that performs heapify on a subtree in a heap. 
     * It ensures that heap is proper - every parent is greater than its children.
     * It is used in the heap sort algorith.
     *
     *@param tab pointer to the array of any type that we want to sort
     *@param size size of the array the pointer points at
     *@param i index of the root (parent) of subtree that needs to be heapified
     *
     *@note The function works recursively on the subtree, providig correct heap order. If the parent is swapped with a child, the function calls to itsel recursively on the affected subtree.
     */
    void heapify(T* tab, int size, int i) {
        int largest = i;           //root
        int left = 2 * i + 1;      //formula to calculate left child
        int right = 2 * i + 2;     //formula to calculate right child

        //check if left child exists and is bigger than the parent
        if (left < size && tab[left] > tab[largest])
            largest = left; //swapping left child with parent

        //check if right child exists and is bigger than the parent
        if (right < size && tab[right] > tab[largest])
            largest = right; //swapping right child with parent

        //checking if the largest element isnt the parent
        if (largest != i) {
            swap(tab[i], tab[largest]);  //swap root with biggest element
            //recursively heapify the subtree
            heapify(tab, size, largest);
        }
    }

    /**
     *Function that sorts an array using heap sort algorithm, it first builds a max heap from the input array, and then iteratively swaps the root of the heap
     * with the last element of the heap, reducing the heap size and reapplying the heapify operation.
     * Sort in-place, unstable.
     *
     *@param tab pointer to the array of any type that we want to sort
     *@param size size of the array the pointer points at
     */
    void heapsort(T* tab, int size) {
        // Budowanie kopca (porządkowanie tablicy)
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(tab, size, i);
        }

        for (int i = size - 1; i > 0; i--) {
            // swapping root with the last element on the tree
            swap(tab[0], tab[i]);

            //heapifying on the smaller tree
            heapify(tab, i, 0);
        }
    }
    
    
    
    /* -----SHELL SORT----- */
    /**
     * Function that sorts the array using the shell sort algorithm. 
     * Sorts the elements that are far apart first, then reducing the gap.
     * Gap is calculated with the use of Shell formula.
     * Gap is initially set to half the size of the array and us halved each iteration until it is 0.
     * It performs a modified insertion sort (with bigger gaps).
     * Sort in-place, unstable.
     *
     * @param tab pointer to the array of any type that we want to sort
     * @param size size of the array the pointer points at
     */
    void shellsortShell(T* tab, int size) {
        int gap = size / 2;  // Początkowy odstęp

        while (gap > 0) {
            for (int i = gap; i < size; i++) {
                T temp = tab[i];
                int j = i;
                while (j >= gap && tab[j - gap] > temp) {
                    tab[j] = tab[j - gap];
                    j -= gap;
                }
                tab[j] = temp;
            }
            gap /= 2;  // Zmniejszanie odstępu
        }
    }
    /**
     * Function that sorts the array using the shell sort algorithm. Sorts the elements increasing the gap sizes. Gap is calculated using Hibbard formula. Gap is calculated with the formula `2^k -1` where `k` is progressively decreased.
     *Sort in-place, unstable
     *
     *@param tab pointer to the array of any type that we want to sort
     *@param size  size of the array the pointer points at
     */
    void shellSortHibbard(T* tab, int size) {
        int k = 1;
        //the loop finds the maximum value of k, so the gap will be smaller than the size of the array
        while ((1 << k) - 1 < size) {
            k++;
        }

        k--; //decrementing k, so it is smaller than the size
        while (k >= 0) {
            int gap = (1 << k) - 1; //calculating the gap from hibbards formula
            for (int i = gap; i < size; i++) {
                T temp = tab[i];
                int j = i;
                while (j >= gap && tab[j - gap] > temp) {
                    tab[j] = tab[j - gap];
                    j -= gap;
                }
                tab[j] = temp;
            }
            k--; //decrementing k
        }
    }
    
    
    /* -----INSERTION SORT----- */
    /**
     *Function that implements the insertion sort algorithm. The function sorts the array by iterating through every element, comparing it to the element on the left and inserting it into the right position. It works by shifting the element to the right and placing the key in correct position.
     *Sort in-place, stable
     *
     *@param tab pointer to the array of any type that we want to sort
     *@param size size of the array the pointer points at
     */
    void insertionSort(T* tab, int size) {
        for (int i = 1; i < size; i++) {
                T key = tab[i];   //choosing the element to start comparing and inserting
                int j = i - 1;
                
                //moving bigger elements to the right
                while (j >= 0 && tab[j] > key) {
                    tab[j + 1] = tab[j];
                    j--;
                }
                
                //placing the element in the correct position
                tab[j + 1] = key;
            }
    }
    
    
};







/**
 * Function that reads an array from a file. The file should contain the size of the array as the first value, followed by the elements of the array. The function allocates memory for the array based on the size read from the file, then fills the array.
 * If an array already exists (if the pointer is not null), it deletes the previous array to free memory.
 *
 *@param tab reference to a pointer where the array will be stored
 *@param size reference to an integer that will store the size of the array
 *@param filename the name of the file from which the array is read
 *
 *@warning The function deletes the existing array (if it exists) before allocating a new one
 *@warning If the file cannot be opened, an error message is displayed, and the function returns without modifying the array.
*/
template <typename T>
void readArrayFromFile(T*& tab, int& size, const string& filename) {
    if (tab!= nullptr) delete[] tab; //Delete existing array
    ifstream file(filename);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    //Read the size of the array from file
    file >> size;

    //Allocate memory for the array
    tab = new T[size];

    //Read the elements of the array
    for (int i = 0; i < size; ++i) {
        file >> tab[i];
    }
}

/**
 *Function that prints the elements of an array to the standard output.
 *It iterates through the array and prints each element followed by a space.
 *After printing all elements, it outputs a newline.*
 *
 *@param tab  pointer to the array of elements to be printed
 * @param size the size of the array to be printed
 */
template <typename T>
void printArray(T* tab, int size) {
    for (int i = 0; i < size; ++i) {
        cout << tab[i] << " ";
    }
    cout << endl;
}

/**
 *Function that copies contents of one array into another. If the clone array exists, it is deleted and reallocated before allocating new array. It checks if the array to be cloned exists and size is bigger than 0. If no, it outputs an error.
 *
 *@param cloneArray reference to a pointer to the array that will store the copied elements
 *@param originalArray pointer to the array whose elements will be copied
 *@param size the number of elements to be copied from the original array
 */
template <typename T>
void copyArray(T*& cloneArray, T* originalArray, int size) {
    //Check if the original array is valid
    if (originalArray == nullptr || size <= 0) {
            cout << "Error: originalArray is not initialized or has invalid size.\n";
            return;
    }
    
    //Delete the existing cloneArray if it exists
    if (cloneArray != nullptr) {
        delete[] cloneArray;
    }
    
    //Allocate new memory for the cloneArray
    cloneArray = new T[size];
    
    //Copy the contents of the originalArray into the cloneArray
    for (int i = 0; i < size; ++i) {
        cloneArray[i] = originalArray[i];
    }
}

/**
 * Function that generates an array of random integers in the range of -100000 to 100000.
 * If the array already exists, it deletes the old array and allocates new memory.
 *
 * @param tab reference to a pointer where the generated array will be stored
 * @param size number of random integers to generate
 */
void generateRandomIntArray(int*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab;  //Delete the old array if it exists
    }
    tab = new int[size]; //Allocate new memory for the array
    for (int i = 0; i < size; ++i) {
        //Generate a random integer in the range of -100000 to 100000
        tab[i] = rand() % 200000 - 100000;
    }
}

/**
 * Function that generates an array of random floats in the range of `-FLT_MAX` to `FLT_MAX`.
 * If he array already exists, it deletes the old array and allocates new memory.
 *
 * @param tab reference to a pointer where the generated array will be stored
 * @param size Number of random floating-point numbers to generate
 */
void generateRandomFloatArray(float*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab; //Delete the old array if it exists
    }
    tab = new float[size]; //Allocate new memory for the array
    for (int i = 0; i < size; ++i) {
        tab[i] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/20000.f)) - 10000.0f; //Generating random floats with range of -10000.0 to 10000.0
    }
}

/**
 *Function that checks if the array is sorted asceding
 *@param tab pointer to the array
 *@param size size of the array
 *@return true if array is sorted ascending, false if not
 */
template<typename T>
bool isSorted(T* tab, int size) {
    for (int i = 1; i < size; i++) {
        if (tab[i - 1] > tab[i]) {
            return false;
        }
    }
    return true;
}


/**
 *Function that tests all of the sorting algorithms: shell, quick, heap and insertion sort. It generates a random array of size 10000 and outputs on the console  if each algorithm works correctly.
 */

void testSorting()
{
    Sorter<int> sorterInt;
    Sorter<float> sortetFloat;
    const int size = 10000;
    
    int* arrInt = nullptr;
    int* cloneArrInt = nullptr;

    generateRandomIntArray(arrInt, size);
    
    //testing for quicksort
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.quicksortLeft(cloneArrInt, size);
       cout << "QuickSort (Pivot: Left): " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.quicksortRight(cloneArrInt, size);
       cout << "QuickSort (Pivot: Right): " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.quicksortMiddle(cloneArrInt, size);
       cout << "QuickSort (Pivot: Middle): " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.quicksortRandom(cloneArrInt, size);
       cout << "QuickSort (Pivot: Random): " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    //testing for heapsort
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.heapsort(cloneArrInt, size);
       cout << "Heapsort: " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    //testing for insertionsort
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.insertionSort(cloneArrInt, size);
       cout << "Inserion sort: " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.shellsortShell(cloneArrInt, size);
       cout << "Shellsort by Shell's formula: " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrInt, arrInt, size);
       sorterInt.shellSortHibbard(cloneArrInt, size);
       cout << "Shellsort by Hibbard's formula: " << (isSorted(cloneArrInt, size) ? "Sorted" : "Not Sorted") << endl;
    
    delete [] arrInt;
    delete [] cloneArrInt;
    
    float* arrFloat = nullptr;
    float* cloneArrFloat = nullptr;
    
    generateRandomFloatArray(arrFloat, size);
    
    
    //testing for quicksort
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.quicksortLeft(cloneArrFloat, size);
       cout << "QuickSort (Pivot: Left): " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.quicksortRight(cloneArrFloat, size);
       cout << "QuickSort (Pivot: Right): " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.quicksortMiddle(cloneArrFloat, size);
       cout << "QuickSort (Pivot: Middle): " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.quicksortRandom(cloneArrFloat, size);
       cout << "QuickSort (Pivot: Random): " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    //testing for heapsort
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.heapsort(cloneArrFloat, size);
       cout << "Heapsort: " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    //testing for insertionsort
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.insertionSort(cloneArrFloat, size);
       cout << "Inserion sort: " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.shellsortShell(cloneArrFloat, size);
       cout << "Shellsort by Shell's formula: " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    copyArray(cloneArrFloat, arrFloat, size);
       sortetFloat.shellSortHibbard(cloneArrFloat, size);
       cout << "Shellsort by Hibbard's formula: " << (isSorted(cloneArrFloat, size) ? "Sorted" : "Not Sorted") << endl;
    
    delete [] arrFloat;
    delete [] cloneArrFloat;
}


void generatePartiallySortedArray(int*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab;
    }
    tab = new int[size];
    int sortedSize = size / 3;
    for (int i = 0; i < sortedSize; ++i) {
        tab[i] = i - 100000;
    }
    set<int> usedNumbers;
    for (int i = 0; i < sortedSize; ++i) {
        usedNumbers.insert(tab[i]);
    }
    for (int i = sortedSize; i < size; ++i) {
        int randomNumber;
        do {
            randomNumber = rand() % 200000 - 100000;
        } while (usedNumbers.find(randomNumber) != usedNumbers.end());

        tab[i] = randomNumber;
    }
}


void generatePartiallySortedArray66(int*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab;
    }
    tab = new int[size];
    int sortedSize = 2 *size / 3;
    for (int i = 0; i < sortedSize; ++i) {
        tab[i] = i - 100000;
    }
    set<int> usedNumbers;
    for (int i = 0; i < sortedSize; ++i) {
        usedNumbers.insert(tab[i]);
    }
    for (int i = sortedSize; i < size; ++i) {
        int randomNumber;
        do {
            randomNumber = rand() % 200000 - 100000;
        } while (usedNumbers.find(randomNumber) != usedNumbers.end());

        tab[i] = randomNumber;
    }
}

void generatePartiallySortedFloatArray(float*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab; }
    tab = new float[size];
    int sortedSize = size / 3;
    for (int i = 0; i < sortedSize; ++i) {
        tab[i] = static_cast<float>(i) - 100000.0f;  // Pierwsze 33% to wartości rosnące od -100000
    }
    set<float> usedNumbers;
    for (int i = 0; i < sortedSize; ++i) {
        usedNumbers.insert(tab[i]);
    }
    for (int i = sortedSize; i < size; ++i) {
        float randomNumber;
        do {
            randomNumber = static_cast<float>(rand() % 200000 - 100000);
        } while (usedNumbers.find(randomNumber) != usedNumbers.end());
        tab[i] = randomNumber;
    }
}

void generatePartiallySortedFloatArray66(float*& tab, int size) {
    if (tab != nullptr) {
        delete[] tab; }
    tab = new float[size];
    int sortedSize = 2* size / 3;
    for (int i = 0; i < sortedSize; ++i) {
        tab[i] = static_cast<float>(i) - 100000.0f;  // Pierwsze 33% to wartości rosnące od -100000
    }
    set<float> usedNumbers;
    for (int i = 0; i < sortedSize; ++i) {
        usedNumbers.insert(tab[i]);
    }
    for (int i = sortedSize; i < size; ++i) {
        float randomNumber;
        do {
            randomNumber = static_cast<float>(rand() % 200000 - 100000);
        } while (usedNumbers.find(randomNumber) != usedNumbers.end());
        tab[i] = randomNumber;
    }
}


/**
 * Main program function providing an interactive menu for the user to:
 * - Choose between sorting integers or floats
 * - Read an array from a file or generate a random array
 * - Sort the array using various algorithms (Insertion, Shell, Heap, Quick Sort)
 * - Display the current or sorted array
 * The program repeatedly prompts the user until the user decides to exit.
 *
 *@param argc Number of command line arguments (unused)
 *@param argv Array of command line arguments (unused)
 *@return 0 if the program completes successfully
 */
int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    
    //testSorting(); this function call is used to test each algorithm if it works correctly
    
    
    int* intArray = nullptr;
    float* floatArray = nullptr;
    int* cloneIntArray = nullptr;
    float* cloneFloatArray = nullptr;
    int size = 0;
    int clonesize = 0;
        
    int dataTypeChoice;
    int choice;
    bool isFloat = false;
    
    Sorter<float> floatSorter;
    Sorter<int> intSorter;
    
    
    do {
        cout << "Choose data type:\n";
        cout << "1. int\n";
        cout << "2. float\n";
        cout << "3. EXIT\n\n";
        cin >> dataTypeChoice;

        if (dataTypeChoice == 3) break;

        if (dataTypeChoice == 1) {
            isFloat = false;
        }
        else if (dataTypeChoice == 2) {
            isFloat = true;
        }
        else {
            cout << "Incorrect choice, try again\n";
            continue;
        }
        
        
    do {
        cout << "\nMenu\n";
        cout << "1. Read array from file\n";
        cout << "2. Generate array of given size with random numbers\n";
        cout << "3. Output lastly created array\n";
        cout << "4. Sort the array with chosen algorithm\n";
        cout << "5. Output sorted array\n";
        cout << "6. EXIT\n";
        cin >> choice;
        switch(choice) {
            case 1:
            {
                string filename;
                cout << "Enter filename: \n";
                cin >> filename;
                
                if (isFloat) {
                    readArrayFromFile(floatArray, size, filename);
                } else {
                    readArrayFromFile(intArray, size, filename);
                }
                break;
            }
            case 2:
            {
                cout << "Enter the size of the array: \n";
                cin >> size;
                if (isFloat) {
                    generateRandomFloatArray(floatArray, size);
                } else {
                    generateRandomIntArray(intArray, size);
                }
                break;
            }
                
            case 3:
            {
                if (isFloat)
                {
                    if (floatArray != nullptr && size > 0)
                        printArray(floatArray, size);
                    else
                        cout << "No array\n";
                    break;
                }
                else if (!isFloat)
                {
                    if (intArray != nullptr && size > 0)
                    {
                        printArray(intArray, size);
                    }
                    else
                        cout << "no array\n";
                }
                break;
            }
            case 4:
            {
                if (isFloat)
                {
                    copyArray(cloneFloatArray, floatArray, size);
                    clonesize = size;
                    int sortChoice;
                    cout << "Choose sorting algorithm:\n";
                    cout << "1. Insertion Sort\n";
                    cout << "2. Shell Sort\n";
                    cout << "3. Heap Sort\n";
                    cout << "4. Quick Sort\n";
                    cin >> sortChoice;
                    if (isFloat) {
                        switch(sortChoice) {
                            case 1:
                                floatSorter.insertionSort(cloneFloatArray, clonesize);
                                printArray(cloneFloatArray, clonesize);
                                break;
                            case 2:
                            {
                                int shellChoice;
                                cout << "Choose Shell Sort variant:\n";
                                cout << "1. Classic Shell Sort\n";
                                cout << "2. Shell Sort with Hibbard's gaps\n";
                                cin >> shellChoice;
                                switch(shellChoice) {
                                    case 1:
                                    {
                                        floatSorter.shellsortShell(cloneFloatArray, clonesize);
                                        printArray(cloneFloatArray, clonesize);
                                        break;
                                    }
                                    case 2:
                                    {
                                        floatSorter.shellSortHibbard(cloneFloatArray, clonesize);
                                        printArray(cloneFloatArray, clonesize);
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice. Returning to previous menu.\n";
                                        break;
                                }
                            case 3:
                                {
                                    floatSorter.heapsort(cloneFloatArray, clonesize);
                                    printArray(cloneFloatArray, clonesize);
                                    break;
                                }
                            case 4:
                                {
                                    int pivotChoice;
                                    cout << "Choose pivot selection strategy for Quick Sort:\n";
                                    cout << "1. Left\n";
                                    cout << "2. Right\n";
                                    cout << "3. Middle\n";
                                    cout << "4. Random\n";
                                    cin >> pivotChoice;
                                    
                                    switch(pivotChoice) {
                                        case 1:
                                        {
                                            floatSorter.quicksortLeft(cloneFloatArray, clonesize);
                                            printArray(cloneFloatArray, clonesize);
                                            break;
                                        }
                                        case 2:
                                        {
                                            floatSorter.quicksortRight(cloneFloatArray, clonesize);
                                            printArray(cloneFloatArray, clonesize);
                                            break;
                                        }
                                        case 3:
                                        {
                                            floatSorter.quicksortMiddle(cloneFloatArray, clonesize);
                                            printArray(cloneFloatArray, clonesize);
                                            break;
                                        }
                                        case 4:
                                        {
                                            floatSorter.quicksortRandom(cloneFloatArray, clonesize);
                                            printArray(cloneFloatArray, clonesize);
                                            break;
                                        }
                                    }
                                    break;
                                }
                            default:
                                cout << "Invalid choice. Try again.\n";
                                break;
                            }
                        }
                    }
                }
                else if (!isFloat)
                {
                    copyArray(cloneIntArray, intArray, size);
                    clonesize = size;
                    int sortChoice;
                    cout << "Choose sorting algorithm:\n";
                    cout << "1. Insertion Sort\n";
                    cout << "2. Shell Sort\n";
                    cout << "3. Heap Sort\n";
                    cout << "4. Quick Sort\n";
                    cin >> sortChoice;
                    switch(sortChoice) {
                        case 1:
                        {
                            intSorter.insertionSort(cloneIntArray, clonesize);
                            printArray(cloneIntArray, clonesize);
                            break;
                        }
                        case 2:
                        {
                            int shellChoice;
                            cout << "Choose Shell Sort variant:\n";
                            cout << "1. Classic Shell Sort\n";
                            cout << "2. Shell Sort with Hibbard's gaps\n";
                            cin >> shellChoice;
                            switch(shellChoice) {
                                case 1:
                                {
                                    intSorter.shellsortShell(cloneIntArray, clonesize);
                                    printArray(cloneIntArray, clonesize);
                                    break;
                                }
                                case 2:
                                {
                                    intSorter.shellSortHibbard(cloneIntArray, clonesize);
                                    printArray(cloneIntArray, clonesize);
                                    break;
                                }
                                default:
                                    cout << "Invalid choice. Returning to previous menu.\n";
                                    break;
                            }
                        case 3:
                            {
                                intSorter.heapsort(cloneIntArray, clonesize);
                                printArray(cloneIntArray, clonesize);
                                break;
                            }
                        case 4:
                            {
                                int pivotChoice;
                                cout << "Choose pivot selection strategy for Quick Sort:\n";
                                cout << "1. Left\n";
                                cout << "2. Right\n";
                                cout << "3. Middle\n";
                                cout << "4. Random\n";
                                cin >> pivotChoice;
                                
                                switch(pivotChoice) {
                                    case 1:
                                    {
                                        intSorter.quicksortLeft(cloneIntArray, clonesize);
                                        printArray(cloneIntArray, clonesize);
                                        break;
                                    }
                                    case 2:
                                    {
                                        intSorter.quicksortRight(cloneIntArray, clonesize);
                                        printArray(cloneIntArray, clonesize);
                                        break;
                                    }
                                    case 3:
                                    {
                                        intSorter.quicksortMiddle(cloneIntArray, clonesize);
                                        printArray(cloneIntArray, clonesize);
                                        break;
                                    }
                                    case 4:
                                    {
                                        intSorter.quicksortRandom(cloneIntArray, clonesize);
                                        printArray(cloneIntArray, clonesize);
                                        break;
                                    }
                                }
                                break;
                            }
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                        }
                    }
                }
                break;
            }
            case 5:
            {
                if (isFloat)
                {
                    if (cloneFloatArray != nullptr && clonesize > 0)
                        printArray(cloneFloatArray, clonesize);
                    else
                        cout << "No array\n";
                }
                else if (!isFloat)
                {
                    if (cloneIntArray != nullptr && clonesize > 0)
                        printArray(cloneIntArray, size);
                    else
                        cout << "no array\n";
                    break;
                }
                break;
            }
        }
    } while (choice != 6);
    if (isFloat) {
        delete[] floatArray;
        floatArray = nullptr;
    } else {
        delete[] intArray;
        intArray = nullptr;
    }

} while (dataTypeChoice != 3);
    return 0;
}
