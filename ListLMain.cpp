// File: ListL/ListLMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.

#include "Utilities.hpp" // promptIntBetween.
#include "ListL.hpp"
#include "ArrayT.hpp"
#include "ShapeFactoryB.hpp"
#include "ShapeFactoryA.hpp"

const int NUM_LISTS = 5;

typedef ListL<int> ListLInt;
typedef ArrayT<shared_ptr<ListLInt>> ArraySPListInt;

int main() {
    ArraySPListInt lists(NUM_LISTS);
    int value;
    int listNum, listNum2;
    for (int i = 0; i < NUM_LISTS; i++) {
        lists[i] = make_shared<ListLInt>();
    }
    char response;
    do {
        cout << "\nThere are [0.." << NUM_LISTS - 1 << "] mutable lists." << endl;
        cout << "(f)irst        s(e)tFirst  (p)repend     removeF(i)rst  cl(o)ne  (c)lear\n"
             << "conca(t)enate  (a)ppend    removeLa(s)t  remove(V)alue  (z)ip    (u)nzip\n"
             << "(r)everse      len(g)th    length(2)     (m)ax          max(3)   co(n)tains\n"
             << "equa(l)        (w)rite     write(4)      (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'F':
            listNum = promptIntBetween("First element of which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            }
            else {
                cout << "\nThe first element is " << lists[listNum]->first() << endl;
            }
            break;
        case 'E':
            cout << "Set first to what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Set first of which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            }
            else {
                lists[listNum]->setFirst(value);
            }
            break;
        case 'P':
            cout << "Prepend what integer value? ";
            cin >> value;
            lists[promptIntBetween("Prepend to which list? ", 0, NUM_LISTS - 1)]->prepend(value);
            break;
        case 'I':
            listNum = promptIntBetween("Remove first from which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            }
            else {
                cout << "\n" << lists[listNum]->remFirst() << " was removed." << endl;
            }
            break;
        case 'O':
            listNum = promptIntBetween("Clone which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Copy to which list? ", 0, NUM_LISTS - 1);
            *lists[listNum2] = *lists[listNum];
            break;
        case 'C':
            lists[promptIntBetween("Clear which list? ", 0, NUM_LISTS - 1)]->clear();
            break;
        case 'T':
            listNum = promptIntBetween("Concatenate which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Suffix list? ", 0, NUM_LISTS - 1);
            if (listNum == listNum2) {
                cout << "\nThe lists must be distinct." << endl;
            }
            else {
                lists[listNum]->concat(*lists[listNum2]);
            }
            break;
        case 'A':
            cout << "Append what integer value? ";
            cin >> value;
            lists[promptIntBetween("Append to which list? ", 0, NUM_LISTS - 1)]->append(value);
            break;
        case 'S':
            listNum = promptIntBetween("Remove last from which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            }
            else {
                cout << "\n" << lists[listNum]->remLast() << " was removed." << endl;
            }
            break;
        case 'V':
            cout << "Remove what integer value? ";
            cin >> value;
            lists[promptIntBetween("Remove from which list? ", 0, NUM_LISTS - 1)]->remove(value);
            break;
        case 'Z':
            listNum = promptIntBetween("Zip which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Combine with which list? ", 0, NUM_LISTS - 1);
            if (listNum == listNum2) {
                cout << "The lists must be distinct." << endl;
            }
            else {
                lists[listNum]->zip(*lists[listNum2]);
            }
            break;
        case 'U':
            listNum = promptIntBetween("Unzip which list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Split off to which list? ", 0, NUM_LISTS - 1);
            if (listNum == listNum2) {
                cout << "The lists must be distinct." << endl;
            }
            else {
                // delete lists[listNum2];
                lists[listNum2] = lists[listNum]->unZip();
            }
            break;
        case 'R':
            lists[promptIntBetween("Reverse which list? ", 0, NUM_LISTS - 1)]->reverse();
            break;
        case 'G':
            listNum = promptIntBetween("Length of which list? ", 0, NUM_LISTS - 1);
            cout << "\nThe length of the list is " << lists[listNum]->length() << endl;
            break;
        case '2':
            listNum = promptIntBetween("Length of which list? ", 0, NUM_LISTS - 1);
            cout << "\nThe length of the list is " << lists[listNum]->length2() << endl;
            break;
        case 'M':
            listNum = promptIntBetween("Maximum of which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            }
            else {
                cout << "\nThe maximum element is " << lists[listNum]->max() << endl;
            }
            break;
        case '3':
            listNum = promptIntBetween("Maximum of which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->isEmpty()) {
                cout << "\nThe list is empty." << endl;
            }
            else {
                cout << "\nThe maximum element is " << lists[listNum]->max3() << endl;
            }
            break;
        case 'N':
            cout << "Search for what integer value? ";
            cin >> value;
            listNum = promptIntBetween("Search which list? ", 0, NUM_LISTS - 1);
            if (lists[listNum]->contains(value)) {
                cout << "\nThe list contains " << value << "." << endl;
            }
            else {
                cout << "\nThe list does not contain " << value << "." << endl;
            }
            break;
        case 'L':
            listNum = promptIntBetween("First list? ", 0, NUM_LISTS - 1);
            listNum2 = promptIntBetween("Second list? ", 0, NUM_LISTS - 1);
            if (*lists[listNum] == *lists[listNum2]) {
                cout << "\nThe lists are equal." << endl;
            }
            else {
                cout << "\nThe lists are not equal." << endl;
            }
            break;
        case 'W':
            listNum = promptIntBetween("Write which list? ", 0, NUM_LISTS - 1);
            cout << "\n" << *lists[listNum] << endl;
            break;
        case '4':
            listNum = promptIntBetween("Write which list? ", 0, NUM_LISTS - 1);
            cout << "\n";
            lists[listNum]->toStream4(cout);
            cout << endl;
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    }
    while (toupper(response) != 'Q');
    return EXIT_SUCCESS;
}
