#include <iostream>
struct arraySegment{
    int startPos;
    int endPos;
    int length;
};
using namespace std;

void arrayCombine(int primaryArray[], arraySegment firstSegment,arraySegment secondSegment){

    //cache the first segment
    int* cacheArray = new int[firstSegment.length];
    for(int i=0;i<firstSegment.length;i++){
        cacheArray[i] = primaryArray[firstSegment.startPos + i];
    }
    arraySegment cacheSegment = {0,firstSegment.length-1,firstSegment.length};
    //initialize the resultSegment for indication
    arraySegment resultSegment = {firstSegment.startPos,firstSegment.startPos-1,0};

    while(true){
        //if one of the segments had ran out of elements,then push the rest into the resultSegment
        if(cacheSegment.length == 0){
            for(int i=0;i < secondSegment.length;i++){
                resultSegment.endPos++;
                resultSegment.length++;
                primaryArray[resultSegment.endPos] = primaryArray[secondSegment.startPos];
                secondSegment.startPos++;
            }
            delete cacheArray;
            return;
        }
        if(secondSegment.length == 0){
            for(int i=0;i < cacheSegment.length;i++){
                resultSegment.endPos++;
                resultSegment.length++;
                primaryArray[resultSegment.endPos] = cacheArray[cacheSegment.startPos];
                cacheSegment.startPos++;
            }
            delete cacheArray;
            return;
        }
        //compare,pick the smaller one into the result
        if(cacheArray[cacheSegment.startPos] <= primaryArray[secondSegment.startPos]){
            resultSegment.endPos++;
            resultSegment.length++;
            primaryArray[resultSegment.endPos] = cacheArray[cacheSegment.startPos];
            cacheSegment.startPos++;
            cacheSegment.length--;
        }else{
            resultSegment.endPos++;
            resultSegment.length++;
            primaryArray[resultSegment.endPos] = primaryArray[secondSegment.startPos];
            secondSegment.startPos++;
            secondSegment.length--;

        }
    }
}

/*
FUNCTION:arrayMergeSort
INPUT: pointer of the array,arraySegment for info about the array
OUTPUT: pointer of the sorted array;
*/
int* arrayMergeSort(int* primaryArray,arraySegment primarySegment){
    //check whether its the end of recursion
    if(primarySegment.length<=1){
        return primaryArray;
    }
    //setup the info needed for combine
    //split rule: start......end -> start(1)... length/2 - 1 + length/2 ... end
    arraySegment firstSubArray = {primarySegment.startPos,primarySegment.startPos + (primarySegment.length/2) - 1,primarySegment.length/2};
    arraySegment secondSubArray = {firstSubArray.endPos+1,primarySegment.endPos,(primarySegment.length/2)};
    if(primarySegment.length % 2){
        //if the length of the array is odd,then calibrate the length of the second part
        secondSubArray.length++;
    }
    //sort the contents

    arrayMergeSort(primaryArray,firstSubArray);
    arrayMergeSort(primaryArray,secondSubArray);
    arrayCombine(primaryArray,firstSubArray,secondSubArray);
    return primaryArray;

}
//package function,so the user only have to give length
int* mergeSort(int inputArray[],int length){
    arraySegment primarySegment = {0,length-1,length};
    return arrayMergeSort(inputArray,primarySegment);
}
