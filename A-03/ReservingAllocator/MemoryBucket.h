
class MemoryBucket
{

public:

    MemoryBucket() = default;
    MemoryBucket(const MemoryBucket& rhs) = default;
    MemoryBucket(void* InAllocatedMemory) : MemoryStorageStartPtr{InAllocatedMemory} {}
    
    ~MemoryBucket()
    {
        std::free(MemoryStorageStartPtr);
        MemoryStorageStartPtr = nullptr;
    }

    void* MemoryStorageStartPtr {nullptr};
    MemoryBucket* PreviousBucket {nullptr};
};