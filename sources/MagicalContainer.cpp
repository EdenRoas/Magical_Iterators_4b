#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {
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

    void MagicalContainer::addElement(int num) {
        numbers.push_back(num);
        sort(numbers.begin(), numbers.end()); // we need to sort the array again
        PrimeIterIndex.clear();               // and to point prime number again to check
        primeIndex = 0;
        for (int i = 0; i < numbers.size(); i++) {
            if (MagicalContainer::PrimeIterator::isPrime((numbers[(size_t) i]))) // check who prime and point at him
            {

                PrimeIterIndex.push_back(static_cast<vector<int>::value_type>(i)); // redefinition of default argument
            }
            primeIndex++;
        }
    }

    void MagicalContainer::removeElement(int num) {
        for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
            if (*iter == num) {
                numbers.erase(iter); // delete from the last place in the vector
                return;
            }
        }
        __throw_runtime_error("num is not found");
        // sort(container.begin(), container.end());
    }

    size_t MagicalContainer::size() const {
        return this->numbers.size();
    }
    // ************ AscendingIterator *************

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container, size_t index) : container(
            container), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container),
                                                                                             index(other.index) {
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        return container.numbers[index];
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
        AscendingIterator biter(this->container, 0);
        biter.index = 0;
        return biter;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
        AscendingIterator eiter(this->container);
        eiter.index = container.numbers.size();
        return eiter;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
        return index > other.index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
        return index < other.index;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
        return index == other.index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
        return !(*this == other);
    }

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
        if (&this->container != &other.container)
            throw runtime_error("They are diffrent containers!");
        else
            return *this = other;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (this->index >= container.numbers.size()) {
            __throw_runtime_error("cross the limit");
        }
        ++index;
        return *this;
    }

    // ************ SideCrossIterator *************

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container, size_t forward,
                                                           size_t backward, size_t curr) : container(container),
                                                                              forwardIndex(forward),
                                                                              backwardIndex(backward), currentIndex(curr) {
        if (backward == 0) {
            backwardIndex = container.size()-1;
        }
        currentIndex = forward;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container),
                                                                                             forwardIndex(
                                                                                                     other.forwardIndex),
                                                                                             backwardIndex(
                                                                                                     other.backwardIndex), currentIndex(other.currentIndex){}

    int MagicalContainer::SideCrossIterator::operator*() const {
        return container.numbers[this->currentIndex];
    }

    MagicalContainer::SideCrossIterator
    MagicalContainer::SideCrossIterator::begin() const // Return a copy of the current iterator
    {
        return SideCrossIterator(container, 0, container.size() - 1, currentIndex);
    }

    MagicalContainer::SideCrossIterator
    MagicalContainer::SideCrossIterator::end() const // Return an iterator pointing to the end position
    {
        size_t endIndex = container.size() / 2;
        if (container.size() % 2 != 0)
            return SideCrossIterator(this->container, endIndex+1, endIndex, forwardIndex); // when size container is odd

        return SideCrossIterator(this->container, endIndex, endIndex-1, backwardIndex);// when size container is even
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
        return (this->backwardIndex > other.backwardIndex || this->forwardIndex > other.forwardIndex);

    }

    // void MagicalContainer::SideCrossIterator::print() {
    //     cout << this->backwardIndex << "," << endl;
    // }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
        return !(*this > other) && !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
        return (this->backwardIndex == other.backwardIndex && this->forwardIndex == other.forwardIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
        return !(*this == other);
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(
            const SideCrossIterator &other) // check if they are not diff contauners copy the data to the new containers
    {
        if (&this->container != &other.container)
            throw runtime_error("They are diffrent containers!");
        else {
            forwardIndex = other.forwardIndex;
            backwardIndex = other.backwardIndex;
            //*this = other;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (*this == end())
            __throw_runtime_error("out of bound!");
//        if (forwardIndex == backwardIndex) {
//            //counter = 0;
//            return *this;
//        }
        if (counter == container.size())
            __throw_runtime_error("Illegal");
        counter++;
        if (counter % 2 == 0) {
            this->currentIndex = forwardIndex;
            --backwardIndex;
        } else {
            this->currentIndex = backwardIndex;
            ++forwardIndex;
        }



        return *this;
    }
    // ************ PrimeIterator *************

    bool MagicalContainer::PrimeIterator::isPrime(int number) // returm if the number is prime
    {
        if (number < 2)
            return false;
        for (int i = 2; i <= sqrt(number); ++i) {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container) : container(container), index(0) {
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container),
                                                                                 index(other.index) {
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        vector<int>::size_type indexPrime = static_cast<vector<int>::size_type>(container.PrimeIterIndex[index]);
        return container.numbers[indexPrime];
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
        PrimeIterator biter(container);
        return biter;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
        PrimeIterator eiter(container);
        eiter.index = container.PrimeIterIndex.size();
        return eiter;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
        return index > other.index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
        return index < other.index;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
        return index == other.index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
        return !(*this == other);
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) // not sure
    {
        if (&this->container != &other.container)
            throw runtime_error("They are diffrent!");
        if (this != &other) {
            index = other.index;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (this->index >= container.PrimeIterIndex.size()) {
            __throw_runtime_error("The vecPrime is full!");
        } else {
            ++index;
        }
        return *this;
    }
}