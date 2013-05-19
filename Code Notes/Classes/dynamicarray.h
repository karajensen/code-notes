/****************************************************************
* Kara Jensen (KaraPeaceJensen@gmail.com) 2012
* Dynamic resizing array
*****************************************************************/

#include <malloc.h>

template<typename T>
class DynamicArray
{
public:
    
    DynamicArray() :
        m_start(nullptr)
    {}

    ~DynamicArray()
    {
        Delete();
    }

    /**
    * @return the number of elements in the array
    */
    unsigned int Size(){ return m_numberOfSeenElements; }

    /**
    * Create the array
    */
    void Create()
    {
        if(m_start != nullptr)
        {
            Delete();
        }

        m_numberOfReservedElements = sm_defaultAllocationSize;
        m_numberOfElements = 0;
        m_numberOfSeenElements = 0;

        m_start = new T[m_numberOfReservedElements];
    }
    
    /**
    * Delete the array
    */
    void Delete()
    {
        if(m_start != nullptr)
        {
            delete [] m_start;
            m_numberOfElements = 0;
            m_numberOfReservedElements = sm_defaultAllocationSize;
            m_start = nullptr;
        }
    }
    
    /**
    * Add to end of array
    */
    void Push_Back(T item)
    {
        if((m_numberOfSeenElements+1) >= m_numberOfReservedElements)
            Resize(Pow2RoundUp(m_numberOfReservedElements+1));

        m_start[m_numberOfSeenElements] = item;
        m_numberOfSeenElements++;
        m_numberOfElements++;
    }
    
    /**
    * Resize the array
    */
    void Resize(int size)
    {
        int newsize = size*sizeof(T);
        m_start = (T*)realloc(m_start,newsize);
        m_numberOfReservedElements = size;
    }
    
    /**
    * Add an element to middle of array
    */
    void Insert(unsigned int index, T item)
    {
        if(index >= m_numberOfSeenElements)
            return;

        if((m_numberOfElements+1) >= m_numberOfReservedElements)
            Resize(Pow2RoundUp(m_numberOfReservedElements+1));
        m_numberOfSeenElements++;
        m_numberOfElements++;

        T* Destination = &m_start[index+1];
        T* Start = &m_start[index];
        int size = ((m_numberOfSeenElements-1)-index)*sizeof(T);
        memmove(Destination,Start,size);
        m_start[index] = item;
    }

    /**
    * Remove element from end of array
    */
    void Pop_Back()
    {
        if(m_numberOfSeenElements < 1)
            return;
        m_numberOfSeenElements--;
    }
    
    /**
    * @return a particle element from the array
    */
    T & GetElement(unsigned int index)
    {
        if(index >= m_numberOfSeenElements)
            throw("Index out of bounds");
        return m_start[index];
    }
    T & operator[](unsigned int index)
    {
        if(index >= m_numberOfSeenElements)
            throw("Index out of bounds");
        return m_start[index];
    }
    T & GetLastElement()
    {
        if(m_numberOfSeenElements < 1)
            throw("No elements in array");
        return m_start[m_numberOfSeenElements-1];
    }
    
    /**
    * @param the input number
    * @return the next highest power of 2 number
    */
    int Pow2RoundUp(int x)
    {
        if(x < 0)
            return 0;
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x+1;
    }

private:

    T* m_start; ///< Pointer to the start of the array
    unsigned int m_numberOfReservedElements; ///< Number of elements in reserve
    unsigned int m_numberOfElements; ///< Number of elements in array
    unsigned int m_numberOfSeenElements; ///< Number of accessible elements
    unsigned static const int sm_defaultAllocationSize = 10; ///< initial reserve amount

    /**
    * Prevent copying
    */
    DynamicArray(const DynamicArray&){}
    void operator=(const DynamicArray&){}
};