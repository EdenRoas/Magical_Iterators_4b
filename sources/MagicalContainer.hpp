#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#pragma once
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        //vector<std::vector<size_t>::size_type> numbers;
        vector<int> numbers;
        vector<int> PrimeIterIndex;
        std::vector<int>::size_type primeIndex; // replace frome size_t to this because the compailer

    public:
        MagicalContainer();                        // defult constractor
        MagicalContainer(MagicalContainer &other); // copy constractor
        ~MagicalContainer();                       // destructor

        void addElement(int num);
        void removeElement(int num);
        size_t size() const;
    
    // This Class return the numbers in ascending order
        class AscendingIterator //: public iterator
        {
        private:
            const MagicalContainer &container;
            size_t index;

        public:
            AscendingIterator(const MagicalContainer &container ,size_t index = 0);
            AscendingIterator(const AscendingIterator &other);
            int operator*() const;
            AscendingIterator begin() const;
            AscendingIterator end() const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator++();
            //void swap(int& a, int& b);
        };
        class SideCrossIterator
        {
        private:
            const MagicalContainer &container;
            size_t forwardIndex;
            size_t backwardIndex;
            int counter = 0;
            size_t currentIndex = 0;

        public:
            SideCrossIterator(const MagicalContainer &container,size_t forward = 0,size_t backward = 0);
            SideCrossIterator(const SideCrossIterator &other);
            int operator*() const;
            SideCrossIterator begin() const;
            SideCrossIterator end() const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            SideCrossIterator &operator++();
        };
        class PrimeIterator
        {
        private:
            const MagicalContainer &container;
            size_t index;
            

        public:
            PrimeIterator(const MagicalContainer &container);
            PrimeIterator(const PrimeIterator &other);
            static bool isPrime(int number);
            int operator*() const;
            PrimeIterator begin() const;
            PrimeIterator end() const;
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            PrimeIterator &operator=(const PrimeIterator& other);
            PrimeIterator &operator++();
            
        };
    };

}