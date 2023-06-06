#include "MagicalContainer.hpp"

using namespace std;

namespace ariel
{
    MagicalContainer::MagicalContainer() // defult constractor -> sort
    {
        sort(numbers.begin(), numbers.end());
    }
    MagicalContainer::MagicalContainer(MagicalContainer &other) // copy constractor
    {
        numbers = other.numbers;
    }
    MagicalContainer::~MagicalContainer() // destructor
    {
    }

    void MagicalContainer::addElement(int num)
    {
        numbers.push_back(num);
        sort(numbers.begin(), numbers.end()); // we need to sort the array again
        PrimeIterIndex.clear();               // and to point prime number again to check
        primeIndex = 0;
        for (auto i = 0; i < numbers.size(); i++)
        {
            if (MagicalContainer::PrimeIterator::isPrime((numbers[(size_t)i]))) // check who prime and point at him
            {

                PrimeIterIndex.push_back(static_cast<vector<int>::value_type>(i)); // redefinition of default argument
            }
            primeIndex++;
        }
    }

    void MagicalContainer::removeElement(int num)
    {
        for (auto iter = numbers.begin(); iter != numbers.end(); ++iter)
        {
            if (*iter == num)
            {
                numbers.erase(iter); // delete from the last place in the vector
                break;
            }
            if (iter == numbers.end() || *iter != num)
                __throw_runtime_error("num is not found");
        }
        // sort(container.begin(), container.end());
    }
    size_t MagicalContainer::size() const
    {
        return this->numbers.size();
    }
    // ************ AscendingIterator *************

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container, size_t index) : container(container), index(0) {}
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container), index(other.index)
    {
    }
    int MagicalContainer::AscendingIterator::operator*() const
    {
        return container.numbers[index];
    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const 
    {
        AscendingIterator biter(this->container, 0);
        biter.index = 0;
        return biter;
    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const 
    {   
        AscendingIterator eiter(this->container);
        eiter.index = container.numbers.size();
        return eiter;
    }
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return index > other.index;
    }
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return index < other.index;
    }
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
    {
        return index == other.index;
    }
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        return *this = other;
    }
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (this->index >= container.numbers.size())
        {
            __throw_runtime_error("cross the limit");
        }
        ++index;
        return *this;
    }
    
    // ************ SideCrossIterator *************

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container, size_t forward, size_t backward) : container(container), forwardIndex(0), backwardIndex(container.numbers.size()) {}
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container), forwardIndex(other.forwardIndex), backwardIndex(other.backwardIndex) {}
    int MagicalContainer::SideCrossIterator::operator*() const 
    {
        if (backwardIndex >= forwardIndex)
            return container.numbers[forwardIndex];
        else
            return container.numbers[backwardIndex];
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
    {
        return SideCrossIterator(*this);
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
    {
        SideCrossIterator eiter(*this);
        eiter.forwardIndex = container.numbers.size();
        eiter.backwardIndex = container.numbers.size() - 1;
        return eiter;
    }
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        bool checkGT = (this->backwardIndex > other.backwardIndex || this->forwardIndex > other.forwardIndex);
        return checkGT;
    }
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return !(*this > other);
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
    {
        bool equal = (this->backwardIndex == other.backwardIndex && this->forwardIndex == other.forwardIndex && &container == &other.container);
        return equal;
    }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) // not
    {
        if (&this->container != &other.container)
            throw runtime_error("They are diffrent!");
        if (this != &other)
        {
            forwardIndex = other.forwardIndex;
            backwardIndex = other.backwardIndex;
        }
        return *this;
    }
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() 
    {

        for(auto i = 0; i < container.size(); i++)
        {
            if(forwardIndex > backwardIndex)
                    __throw_runtime_error("Illegal");
            if (i % 2 == 0)
            {
                
                forwardIndex++;
            }
            else 
            {   
                backwardIndex--;
            }
           
        }
         return *this;

    }
    // ************ PrimeIterator *************

    bool MagicalContainer::PrimeIterator::isPrime(int number) // returm if the number is prime
    {
        if (number < 2)
            return false;
        for (int i = 2; i <= sqrt(number); ++i)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container) : container(container), index(0)
    {
        // while (index < container.numbers.size() && !isPrime(container.numbers[index]))
        // {
        //     ++index;
        // }
    }
   
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container), index(other.index)
    {
    }
    int MagicalContainer::PrimeIterator::operator*() const // not sure
    {
        vector<int>::size_type indexPrime = static_cast<vector<int>::size_type>(container.PrimeIterIndex[index]);
        return container.numbers[indexPrime];
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
    {
        PrimeIterator biter(container);
        return biter;
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
    {
        PrimeIterator eiter(container);
        eiter.index = container.PrimeIterIndex.size();
        return eiter;
    }
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return index > other.index;
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return index < other.index;
    }
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
    {
        return index == other.index;
    }
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) // not sure
    {
        if (&this->container != &other.container)
            throw runtime_error("They are diffrent!");
        if (this != &other)
        {
            index = other.index;
        }
        return *this;
    }
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (this->index >= container.PrimeIterIndex.size())
        {
            __throw_runtime_error("The vecPrime is full!");
        }
        else {
            ++index;}
        return *this;
    }
}