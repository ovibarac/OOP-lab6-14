//
// Created by ovi on 4/7/22.
//
#pragma once
#include "Film.h"
template <typename ElementT>
class IteratorVectorT;

typedef Film Element;
#define INITIAL_CAPACITY 5

template <typename ElementT>
class MyVector
{
public:
    /*
    Constructor default
    Alocam loc pentru 5 elemente
    */
    MyVector();

    /*
    Constructor de copiere
    */
    MyVector(const MyVector& ot); //rule of 3

    /*
    Eliberam memoria
    */
    ~MyVector();//rule of 3

    /*
    Operator assgnment
    elibereaza ce era in obiectul curent (this)
    aloca spatiu pentru elemente
    copieaza elementele din ot in this
    */
    MyVector& operator=(const MyVector& ot);//rule of 3


    /*
    Move constructor
    Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
    Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
    */
    MyVector(MyVector&& ot); //rule of 5 

    /*
    Move assignment
    Similar cu move constructor
    Folosit la assignment
    */
    MyVector& operator=(MyVector&& ot); //rule of 5 


    void add(const ElementT& el);

    void deleteFilm(string titlu);

    ElementT& get(int poz) const;

    void set(int poz, const ElementT& el);

    int size() const noexcept;

    friend class IteratorVectorT<ElementT>;
    //functii care creaza iteratori
    IteratorVectorT<ElementT> begin();
    IteratorVectorT<ElementT> end();

    void generalSort(bool(*maimicF)(const Film&, const Film&)){
        for(int i = 0; i< size(); i++){
            for(int j = i+1; j<size(); j++){
                if(!maimicF(elems[i], elems[j])){
                    Film aux = elems[i];
                    elems[i] = elems[j];
                    elems[j] = aux;
                }
            }
        }
    }


private:
    int lg;//numar elemente
    int cap;//capacitate
    ElementT* elems;//elemente

    void ensureCapacity();
};

template<typename ElementT>
void MyVector<ElementT>::deleteFilm(string titlu){
    MyVector<ElementT> rez;
    for(int i = 0; i< size(); i++) {
        if(elems[i].getTitlu() != titlu){
            rez.add(elems[i]);
        }
    }
    *this = rez;
}

/*
Constructor default
Alocam loc pentru 5 elemente
*/
template<typename ElementT>
MyVector<ElementT>::MyVector() :elems{ new Element[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {}

/*
Constructor de copiere
Obiectul current (this) acum se creaza
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
template<typename ElementT>
MyVector<ElementT>::MyVector(const MyVector<ElementT>& ot) {
    elems = new ElementT[ot.cap];
    //copiez elementele
    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];  //assignment din Pet
    }
    lg = ot.lg;
    cap = ot.cap;
}

/*
Operator assgnment
elibereaza ce era in obiectul curent (this)
aloca spatiu pentru elemente
copieaza elementele din ot in this
*/
template<typename ElementT>
MyVector<ElementT>& MyVector<ElementT>::operator=(const MyVector<ElementT>& ot) {
    if (this == &ot) {
        return *this;//s-a facut l=l;
    }
    delete[] elems;
    elems = new ElementT[ot.cap];
    //copiez elementele
    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];  //assignment din Pet
    }
    lg = ot.lg;
    cap = ot.cap;
    return *this;
}

/*
Eliberam memoria
*/
template<typename ElementT>
MyVector<ElementT>::~MyVector() {
    delete[] elems;
}


/*
Move constructor
Apelat daca construim un nou vector dintr-un r-value (ex temporary)
Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
*/
template<typename ElementT>
MyVector<ElementT>::MyVector(MyVector&& ot) {
    // Copy the data pointer from other
    elems = ot.elems;
    lg = ot.lg;
    cap = ot.cap;

    // Release the data pointer from the source object so that  
    // the destructor does not free the memory multiple times.  
    ot.elems = nullptr;
    ot.lg = 0;
    ot.cap = 0;
}

/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obiectul curent (this)
"fura" interiorul lui ot
pregateste ot pentru distrugere
*/
template<typename ElementT>
MyVector<ElementT>& MyVector<ElementT>::operator=(MyVector<ElementT>&& ot) {
    if (this == &ot) {
        return *this;
    }
    delete[] elems;
    // Copy the data pointer from other
    elems = ot.elems;
    lg = ot.lg;
    cap = ot.cap;

    // Release the data pointer from the source object so that  
    // the destructor does not free the memory multiple times.  
    ot.elems = nullptr;
    ot.lg = 0;
    ot.cap = 0;
    return *this;
}

template<typename ElementT>
void MyVector<ElementT>::add(const ElementT& el) {
    ensureCapacity();//daca e nevoie mai alocam memorie
    elems[lg++] = el;
}

template<typename ElementT>
ElementT& MyVector<ElementT>::get(int poz) const {
    return elems[poz];
}

template<typename ElementT>
void MyVector<ElementT>::set(int poz, const ElementT& el) {
    elems[poz] = el;
}

template<typename ElementT>
int MyVector<ElementT>::size() const noexcept {
    return lg;
}

template<typename ElementT>
void MyVector<ElementT>::ensureCapacity() {
    if (lg < cap) {
        return; //mai avem loc
    }
    cap *= 2;
    ElementT* aux = new ElementT[cap];
    for (int i = 0; i < lg; i++) {
        aux[i] = elems[i];
    }
    delete[] elems;
    elems = aux;
}

template<typename ElementT>
IteratorVectorT<ElementT> MyVector<ElementT>::begin()
{
    return IteratorVectorT<ElementT>(*this);
}

template<typename ElementT>
IteratorVectorT<ElementT> MyVector<ElementT>::end()
{
    return IteratorVectorT<ElementT>(*this, lg);
}

template<typename ElementT>
class IteratorVectorT {
private:
    const MyVector<ElementT>& v;
    int poz = 0;
public:
    IteratorVectorT(const MyVector<ElementT>& v) noexcept;
    IteratorVectorT(const MyVector<ElementT>& v, int poz)noexcept;
    bool valid()const;
    ElementT& element()const;
    void next();
    ElementT& operator*();
    IteratorVectorT& operator++();
    bool operator==(const IteratorVectorT& ot)noexcept;
    bool operator!=(const IteratorVectorT& ot)noexcept;
};

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const MyVector<ElementT>& v) noexcept:v{ v } {}

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const MyVector<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVectorT<ElementT>::valid()const {
    return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const{
    return v.elems[poz];
}

template<typename ElementT>
void IteratorVectorT<ElementT>::next() {
    poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() {
    return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() {
    next();
    return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
    return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot)noexcept {
    return !(*this == ot);
}
