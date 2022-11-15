#include <iostream>
#include <fstream>
#include "lab7.h"

using namespace std;
void swapRecord(Customer *customer[], int i, int j)
{
    Customer *cus;

    cus = customer[i];
    customer[i] = customer[j];
    customer[j] = cus;
}

void sortWithRange(Customer *customer[], int lowB, int upB)
{
    for (int i = lowB; i < upB; i++)
    {
        for (int j = i; j < upB - 1; j++)
        {
            if (customer[j]->id > customer[j + 1]->id)
            {
                swapRecord(customer, j, j + 1);
            }
        }
    }
}
// TODO1: Reorder the linked list so that VIP customers come first
// Your would need to reorder the entries in the given array, with VIP customers comes first
//      Both the VIP customers and the normal customers would be then ordered by their ID repectively
//      Example: ID0_VIP, ID1_Non_VIP, ID2_VIP => ID0_VIP, ID2_VIP, ID1_Non_VIP
void reorder_customer(Customer *queue[], int num_customer)
{

    int idx = 0;
    // swap all vip to the top of the list
    for (int i = 0; i < num_customer; i++)
    {
        if (queue[i]->vip)
        {
            swapRecord(queue, i, idx++);
        }
    }
    // sort for vip
    sortWithRange(queue, 0, idx);
    // sort for normal
    sortWithRange(queue, idx, num_customer);
    return;
}

// TODO2: Let customers check out from the store, and get the money
// Customers comes in the ordered of the array
// For each of the customers' needs, if the store can satisfy it, sell the corresponding amount and get the paid money, otherwise skip this need (sell nothing and earn nothing)
//      Example: If a customer need 5 Apples and 5 Bananas and the store have 10 Apples and 2 Bananas left, then sell 5 Apples (and 0 Bananas) to the customer
// You don't need to delete the pointers to customers in this TODO
int check_out(Fruit fruits[], const Customer *const queue[], int num_fruit, int num_customer)
{
    int rev = 0;
    for (int j = 0; j < num_customer; j++)
    {
        for (int i = 0; i < num_fruit; i++)
        {
            if (queue[j]->need[i] <= fruits[i].total_count-fruits[i].sold_count){
                fruits[i].sold_count += queue[j]->need[i];
            }
        }
    }
    for (int i = 0; i < num_fruit; i++){
        rev += fruits[i].sold_count * fruits[i].unit_price;
    }
    return rev;
}









