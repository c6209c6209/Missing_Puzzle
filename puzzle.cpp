#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char buf[8000000];

int counter = 1;

int* puzzle_init(int arr_size, int X, int Y);
void place_puzzle(int* arr, int total_arr_size, int temp_arr_size, int start_x, int start_y, int hole_x, int hole_y);
void print_puzzle(int* arr, int arr_size);

int main()
{
    int T, k, X, Y;

    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int *arr;
        int arr_size;

        scanf("%d %d %d", &k, &X, &Y);
        arr_size = (int)pow(2, k);

        arr = puzzle_init(arr_size, Y, X);
        place_puzzle(arr, arr_size, arr_size, 0, 0, Y, X);
        print_puzzle(arr, arr_size);

        if (i < T - 1)
            printf("\n");
        counter = 1;

        free(arr);
    }

    return 0;
}

int* puzzle_init(int arr_size, int X, int Y) {
    int *arr;

    arr = (int *)malloc(arr_size * arr_size * sizeof(int));
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < arr_size; j++) {
            arr[i*arr_size + j] = 0;
        }
    }
    arr[X*arr_size + Y] = -1;

    return arr;
}

void place_puzzle(int* arr, int total_arr_size, int temp_arr_size, int start_x, int start_y, int hole_x, int hole_y) {
    //int hole_x, hole_y;
    int middle_x, middle_y;
    int sub_arr_size;

    if (temp_arr_size == 2){
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if ((start_x+i) != hole_x || (start_y+j) != hole_y)
                    arr[(start_x+i)*total_arr_size + (start_y + j)] = counter;
            }
        }
        counter++;
        return;
    }

    /*for (int i = start_x; i < (start_x + temp_arr_size); i++) {
        for (int j = start_y; j < (start_y + temp_arr_size); j++) {
            if (arr[i*total_arr_size + j] != 0) {
                hole_x = i;
                hole_y = j;
            }
        }
    }*/

    middle_x = start_x + temp_arr_size/2;
    middle_y = start_y + temp_arr_size/2;

    sub_arr_size = temp_arr_size / 2;

    if (hole_y < middle_y) {    //hole is in left hand side
        if (hole_x < middle_x) {    //hole is in upper-left
            arr[middle_x*total_arr_size + middle_y] = counter;
            arr[middle_x*total_arr_size + (middle_y-1)] = counter;
            arr[(middle_x-1)*total_arr_size + middle_y] = counter;
            counter++;
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, start_y, hole_x, hole_y);
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, middle_y, middle_x-1, middle_y);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, start_y, middle_x, middle_y-1);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, middle_y, middle_x, middle_y);
        }
        else {  //hole is in lower-left
            arr[middle_x*total_arr_size + middle_y] = counter;
            arr[(middle_x-1)*total_arr_size + (middle_y-1)] = counter;
            arr[(middle_x-1)*total_arr_size + middle_y] = counter;
            counter++;
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, start_y, middle_x-1, middle_y-1);
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, middle_y, middle_x-1, middle_y);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, start_y, hole_x, hole_y);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, middle_y, middle_x, middle_y);
        }
    }
    else {  //hole is in right hand side
        if (hole_x < middle_x) {    //hole is in upper-right
            arr[middle_x*total_arr_size + middle_y] = counter;
            arr[(middle_x-1)*total_arr_size + (middle_y-1)] = counter;
            arr[middle_x*total_arr_size + (middle_y-1)] = counter;
            counter++;
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, start_y, middle_x-1, middle_y-1);
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, middle_y, hole_x, hole_y);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, start_y, middle_x, middle_y-1);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, middle_y, middle_x, middle_y);
        }
        else {  //hole is in lower-right
            arr[(middle_x-1)*total_arr_size + middle_y] = counter;
            arr[(middle_x-1)*total_arr_size + (middle_y-1)] = counter;
            arr[middle_x*total_arr_size + (middle_y-1)] = counter;
            counter++;
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, start_y, middle_x-1, middle_y-1);
            place_puzzle(arr, total_arr_size, sub_arr_size, start_x, middle_y, middle_x-1, middle_y);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, start_y, middle_x, middle_y-1);
            place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, middle_y, hole_x, hole_y);
        }
    }

    /*int sub_arr_size = temp_arr_size / 2;
    place_puzzle(arr, total_arr_size, sub_arr_size, start_x, start_y);
    place_puzzle(arr, total_arr_size, sub_arr_size, start_x, middle_y);
    place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, start_y);
    place_puzzle(arr, total_arr_size, sub_arr_size, middle_x, middle_y);*/
}

void print_puzzle(int *arr, int arr_size) {
    setvbuf(stdout, buf, _IOFBF, sizeof(buf));
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < arr_size - 1; j++) {
            printf("%d ", arr[i*arr_size + j]);
        }
        printf("%d\n", arr[i*arr_size + (arr_size-1)]);
    }
}
